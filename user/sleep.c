#include "user/user.h"


int atoi(const char *s);
int main(int argc, char *argv[])
{
    if (argc < 2) exit(1);

    int time = atoi(argv[1]);
    sleep(time);
    exit(0);
}