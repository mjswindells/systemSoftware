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
    ssize_t wSize = 0;
    char userName[MAX_NAME_SIZE + 1] = {
        '\0',
    };
    int userAge = 0;
    // 사용자 정보를 담기 위한 구조체 생성 및 초기화
    User *user = (User *)malloc(sizeof(User));
    memset(user->name, '\0', MAX_NAME_SIZE + 1);
    user->age = 0;
    printf("Name: ");
    scanf("%[^\n]", userName);
    strcpy(user->name, userName);
    printf("Age: ");
    scanf("%d", &userAge);
    user->age = userAge;
    // 사용자 정보를 담기 위한 파일 생성
    fd = open(pathName, O_CREAT | O_TRUNC | O_RDWR, PERMS);
    if (fd == -1) {
        perror("open() error!");
        exit(-1);
    }
    // 사용자 정보를 파일에 쓰기
    wSize = write(fd, (User *)user, sizeof(User));
    if (wSize == -1) {
        perror("write() error!");
        exit(-2);
    }
    printf("fd: %d, wSize: %ld \n", fd, wSize);
    close(fd);
    free(user);
    return 0;
}
