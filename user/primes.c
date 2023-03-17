#include "user/user.h"

#define setup_child() \
close(0);             \
dup(fd[0]);\
close(fd[0]);\
close(fd[1]);\
is_worker = 1;\
has_child = 0;        \


int
main() {
    int fd[2];
    int p;
    int has_child = 0;
    int is_worker = 0;
    char buffer[4];

    pipe(fd);
    for (int i = 2; i <= 35; i++) {
        if (!has_child) {
            if ((has_child = fork()) == 0)  // child
            {
                setup_child();
                p = i;
                break;
            } else {
                close(fd[0]);
            }
        }
        write(fd[1], &i, 4);
    }

    WORKER:
    if (is_worker) {
        fprintf(1, "prime %d\n", p);
        while (read(0, buffer, sizeof(buffer))) {
            int n = (int) (*buffer);
            if (n % p != 0) {
                // pass
                if (!has_child) {
                    pipe(fd);
                    if ((has_child = fork()) == 0) // child
                    {
                        setup_child();
                        p = n;
                        goto WORKER;
                    } else {
                        close(fd[0]);
                    }
                } else {
                    write(fd[1], &n, 4);
                }
            }
        }
    }

    close(fd[1]);

    wait(0);
    exit(0);
}