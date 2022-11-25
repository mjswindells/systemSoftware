#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUF_SIZE 16
#define PERMS 0644

void myError(const char *msg);

int main(void) {
    int fd1 = 0;
    char *pathname1 = "./original.txt";
    struct stat fileInfo;
    char *text;

    int fd2 = 0;
    char *pathname2 = "./copy.txt";

    fd1 = open(pathname1, O_RDONLY);
    if (fd1 == -1)
        myError("open() error!");

    // 오픈한 파일에 대해서만 열음
    if (fstat(fd1, &fileInfo) == -1)
        myError("fstat() error!");

    text = (char *)malloc(fileInfo.st_size);
    memset(text, 0x00, fileInfo.st_size);

    if (read(fd1, (char *)text, fileInfo.st_size) == -1)
        myError("read() error!");

    fd2 = open(pathname2, O_CREAT | O_WRONLY, PERMS);
    if (fd2 == -1)
        myError("open() error!");

    if (write(fd2, text, fileInfo.st_size) == -1)
        myError("write() error!");

    free(text);
    close(fd2);
    close(fd1);
    return 0;
}
void myError(const char *msg) {
    perror(msg);
    exit(-1);
}
