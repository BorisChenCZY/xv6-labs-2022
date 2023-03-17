#include "user/user.h"
#include "common.h"

int
main()
{
    int pid;
    int ret;
    int parent_to_child_fd[2];
    int child_to_parent_fd[2];
    char buffer[2];

    pipe(parent_to_child_fd);
    pipe(child_to_parent_fd);

    int id = fork();
    if (id == 0) // child
    {
        pid = getpid();
        ret = read(parent_to_child_fd[0], buffer, sizeof(buffer));
        CHECK_RET(ret);

        printf("%d: received ping\n", pid);

        ret = write(child_to_parent_fd[1], buffer, sizeof(buffer));
        CHECK_RET(ret);
    }
    else
    {            // parent
        pid = getpid();
        ret = write(parent_to_child_fd[1], " ", 1);
        CHECK_RET(ret);

        ret = read(child_to_parent_fd[0], buffer, 1);
        CHECK_RET(ret);
        printf("%d: received pong\n", pid);
    }
    exit(0);
}