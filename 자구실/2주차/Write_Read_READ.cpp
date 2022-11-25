#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PERMS 0644
#define MAX_NAME_SIZE 32

struct __User {
    char name[MAX_NAME_SIZE + 1];
    int age;
};

typedef struct __User User;

int main(void) {
    int fd = 0;
    char *pathName = "./user.dat";
    ssize_t rSize = 0;
    // 사용자 정보를 담기 위한 구조체
    User *user = (User *)malloc(sizeof(User));
    memset(user->name, '\0', MAX_NAME_SIZE + 1);
    user->age = 0;
    // 사용자 정보를 담기 위한 파일 생성
    fd = open(pathName, O_RDONLY, PERMS);
    if (fd == -1) {
        perror("open() error!");
        exit(-1);
    }
    // 사용자 정보를 파일에서 읽기
    rSize = read(fd, (User *)user, sizeof(User));
    if (rSize == -1) {
        perror("read() error!");
        exit(-2);
    }
    printf("fd: %d, rSize: %ld \n", fd, rSize);
    printf("User Name: %s, Age: %d \n", user->name, user->age);
    close(fd);
    free(user);
    return 0;
}
