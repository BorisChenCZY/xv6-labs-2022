//
// Created by boris on 17/3/23.
//

#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/stat.h"

void find(char* path, char* target_file)
{
    int fd;
    struct stat st;
    struct dirent de;
    char buf[512];
    char *p;

    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: failed to open %s. len: %d\n", path, strlen(path));
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        exit(1);
    }

    if (st.type != T_DIR)
    {
        close(fd);
        return;
    }

    strcpy(buf, path);
    p = buf + strlen(path);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
        if (de.inum <= 2) continue;
        if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) continue;
        strcpy(p, de.name);
        p[DIRSIZ] = 0;

        if (strcmp(de.name, target_file) == 0) fprintf(1, "%s\n", buf);
        find(buf, target_file);
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        exit(1);
    }

    char* path = argv[1];
    char* target = argv[2];
    find(path, target);

    exit(0);
}