#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {

    int r = 0;
    char *pathname = "/usr/bin/vim";
    struct stat buf1;
    struct stat buf2;

    // stat 구조체를 얻어주는 시스템 함수 : 구조체 내부의 변수들 사용 가능
    r = stat(pathname, &buf1);
    if (r == -1) {
        perror("stat() error!");
        exit(-1);
    }
    // 심볼릭 링크 파일이면 링크파일 자체에 대한 정보를 얻는다.
    r = lstat(pathname, &buf2);
    if (r == -1) {
        perror("lstat() error!");
        exit(-1);
    }
    printf("Original file size: %ld\n", buf1.st_size);
    printf("Symbolic link file size: %ld\n", buf2.st_size);
    return 0;
}
