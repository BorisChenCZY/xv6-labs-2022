//
// Created by boris on 17/3/23.
//

#include "user/user.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(2, "Not command to execute");
        exit(1);
    }

    char* command = argv[1];
    char buffer[256];

    char tmp[2];
    char* p = buffer;
    char* buf_args[argc + 1];
    for (int i = 0; i < argc - 1; i++)
    {
         buf_args[i] = argv[i + 1];
    }
    while (read(0, tmp, 1))
    {
        if (tmp[0] != '\n')
        {
            *p++ = tmp[0];
        }
        else {
            buf_args[argc - 1] = buffer;
            buf_args[argc] = 0;
            if (fork() == 0) exec(command, buf_args);

            memset(buffer, 0, sizeof(buffer));
            p = buffer;
        }
    }


    exit(0);
}