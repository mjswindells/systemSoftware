#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PERMS 0644
#define MAX_BUF_SIZE 1024
int main(void) {
    int fd = 0;
    char *pathname = "./mymsg.txt";
    char buf[MAX_BUF_SIZE + 1] = {
        '\0',
    };
    ssize_t rsize = 0;
    ssize_t tsize = 0;
    fd = open(pathname, O_RDONLY, PERMS);
    if (fd == -1) {
        perror("open() error!");
        exit(-1);
    }
    do {
        memset(buf, '\0', MAX_BUF_SIZE + 1);
        rsize = read(fd, buf, MAX_BUF_SIZE);
        if (rsize == -1) {
            perror("read() error!");
            exit(-2);
        }
        printf("%s", buf);
        tsize += rsize;
    } while (rsize > 0);
    // 파일을 반복하여 읽으며, 끝까지 읽음.
    printf("fd: %d, total rsize: %ld \n", fd, tsize);
    close(fd);
    return 0;
}
