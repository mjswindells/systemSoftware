#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PERMS 0644
#define MAX_BUF_SIZE 32

int main(void) {
    int fd = 0;
    char *pathName = "./mymsg.txt";
    ssize_t wSize = 0;
    char msg[MAX_BUF_SIZE + 1] = "Bonjour!";
    fd = open(pathName, O_RDWR);
    if (fd == -1) {
        perror("open() error!");
        exit(-1);
    }
    lseek(fd, (off_t)0, SEEK_END);
    wSize = write(fd, (char *)msg, strlen(msg));
    if (wSize == -1) {
        perror("write() error!");
        exit(-2);
    }
    printf("fd: %d, wSize: %ld \n", fd, wSize);
    close(fd);
    return 0;
}
