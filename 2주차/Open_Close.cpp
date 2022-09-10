#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PERMS 0644

int main(void) {

    int fd = 0;

    char *pathname = "./newfile.txt";

    // fd = creat(pathname, PERMS);
    fd = open(pathname, O_CREAT | O_RDWR, PERMS);

    if (fd == -1) {
        perror("open() error!");
        exit(-1);
    }

    printf("fd of %s is : %d", pathname, fd);
    close(fd);
    return 0;
}
