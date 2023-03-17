#include "user/user.h"

int 
main()
{
    int main_to_child_fd[2]
    char buffer[10];
    int ret;

    ret = pipe(main_to_child_fd);
    CHECK_RET(ret);

    int pid = fork();
    if (pid != 0) { // main process
        for (int n = 2; n <= 35; n++)
        {

        }
    }
    else { // child
        while (read(main_to_child_fd[0], buffer, sizeof(buffer)) != 0)
        {
            int p = 0;
            if (p == 0) {
                p = atoi(buffer);
                printf("prime %d", p);
            }
            else {
                int n = atoi(buffer);
                if (n % p == 0) continue;
                {
                    // pass to a new child
                }
            }
        }
    }
    exit(0);
}