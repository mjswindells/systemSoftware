#include <dirent.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h> 
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h> 
#include <pwd.h> 

#define MAX_PATH_LEN 1024

// 해당 파일의 mode를 출력해준다.
void fileMode(const struct stat *fileInfo);
// File Type을 확인하고 출력해준다.
void fileType(const struct stat *fileInfo);
// File Size를 출력해준다.
void fileSize(const struct stat *fileInfo);
// 재귀 함수
int mytree(int* num, int line);



int main(void) {
    int* num = malloc(sizeof(int) * 2);
    num[0] = 0; num[1] = 0;

    printf(".\n");
    mytree(num, 1);

    // 마지막 결과 출력
    // directories : num[0]
    // files : num[1]
    printf("\n%d directories, %d files\n", num[0], num[1]);
    return 0;
}




int mytree(int* num, int line) {
    // 파일 정보 구조체
    struct stat fileInfo;
    // 시스템 정보 구조체 (포인터)
    struct passwd * userInfo;
    // Directory 구조체 (포인터)
    DIR * dirp;
    // Directory Entry (포인터)
    struct dirent * dirInfo;


    // 현재 디렉토리 위치
    char cwd[MAX_PATH_LEN + 1];
    memset(cwd, '\0', 1);

    // 현재 작업 디렉토리의 경로를 얻고, 이를 메모리 공간에 저장
    if (getcwd(cwd, MAX_PATH_LEN) == NULL) {
        perror("getcwd() error!");
        exit(-1);
    }

    
    // 현재 디렉토리의 entry 갯수
    int numOfDirent = 0;

    // Directory Entry 갯수 확인
    dirp = opendir(cwd);
    while ((dirInfo = readdir(dirp)) != NULL) {
        // 숨김파일 생략
        if (strncmp(&dirInfo->d_name[0], ".", 1) == 0) continue;
        // 숨김파일이 아닐 경우, directory entry의 갯수 1 증가
        else { numOfDirent++; }
    }


    // 중간 확인
    // printf("Current work directory: %s\n", cwd);
    // printf("numOfDirent: %d\n", numOfDirent);


    // 현재 경로에서 directory pointer 뽑아오기
    dirp = opendir(cwd);
    while ((dirInfo = readdir(dirp)) != NULL) {
        // 숨긴 파일 생략
        if (strncmp(&dirInfo->d_name[0], ".", 1) == 0) continue;

        // while문 돌아갈 때마다 초기화
        int lineCheck = line;
        // 하위 디렉토리 때문에 설정 
        int step = 2;
        // 몇 개의 directory entry가 남았는지...
        numOfDirent--;

        // 출력 전 나무 그리기
        while (lineCheck != 1) {
            // 6칸
            if (lineCheck % 2 == 1) { printf("│     "); }
            else { printf("      "); }
            lineCheck /= 2;
            step *= 2;
        }

        // fileInfo를 가져오기 위한 설정
        int r = 0;
        char tmp[MAX_PATH_LEN + 1];
        memcpy(tmp, cwd, sizeof(cwd));
        strcat(tmp, "/");
        strcat(tmp, dirInfo->d_name);
        r = stat(tmp, &fileInfo);
        if (r == -1) {
            perror("stat() error!");
            exit(-1);
        }

        // passwd 구조체에 불러오기
        userInfo = getpwuid(fileInfo.st_uid);



        // 1. 나무 그리기
        // 6칸
        if (numOfDirent != 0) { printf("┝━━━  "); }
        else { printf("┕━━━  "); }
        
        // 2. Inode 넘버
        printf("[%8llu ", dirInfo->d_ino);

        // 3. 디바이스 넘버
        printf("%6d ", fileInfo.st_dev);

        // 4. Directory(d) or Regular File(-)
        fileType(&fileInfo);

        // 4. 권한
        fileMode(&fileInfo);

        // 5. 소유자
        printf(" %s", userInfo->pw_name);

        // 6. 파일 사이즈
        fileSize(&fileInfo);

        // 7. 파일 이름
        printf("%s\n", dirInfo->d_name);



        // Directory File 확인 !
        if (S_ISDIR(fileInfo.st_mode)) {
            num[0]++;

            // 하위 디렉토리로 이동
            if (chdir(tmp) == -1) { 
                perror("chdir() error!"); 
                exit(-1);
            }

            if (numOfDirent != 0) { mytree(num, line + step); }
            else { mytree(num, line + step - step / 2); }
        }
        // Regular File 확인 !
        else if (S_ISREG(fileInfo.st_mode)) { num[1]++; }
        else { perror("directory X && regular X"); exit(-1); }
    }


    // 해당 경로의 directory를 닫아준다.
    closedir(dirp);
    return 0;
}








void fileSize(const struct stat *fileInfo) {
    int size = fileInfo->st_size;

    if (size < 1000) {
        printf("%8d]  ", size);
    } 
    else {
        double ssize = size;
        ssize /= 1000;
        printf("%7.1fK]  ", ssize);
    }
}



void fileType(const struct stat *fileInfo) { 
    if (S_ISREG(fileInfo->st_mode)) {
        printf("-");
    } 
    else if (S_ISDIR(fileInfo->st_mode)) {
        printf("d");
    } 
    else if (S_ISLNK(fileInfo->st_mode)) {
        printf("l");
    } 
    else if (S_ISSOCK(fileInfo->st_mode)) {
        printf("s");
    } 
    else if (S_ISFIFO(fileInfo->st_mode)) {
        printf("p");
    } 
    else if (S_ISCHR(fileInfo->st_mode)) {
        printf("c");
    } 
    else if (S_ISBLK(fileInfo->st_mode)) {
        printf("b");
    }
    else if (S_TYPEISMQ(fileInfo)) {
        printf("");
    } 
    else if (S_TYPEISSEM(fileInfo)) {
        printf("");
    } 
    else if (S_TYPEISSHM(fileInfo)) {
        printf("");
    }
    else { 
        perror("Directory X && Regular X"); 
        exit(-1); 
    }
}






void fileMode(const struct stat *fileInfo)
{
    // User
    if (S_IRUSR & fileInfo->st_mode) { 
        // printf("%d", S_IRUSR & fileInfo->st_mode);
        printf("r"); 
    } 
    else { 
        // printf("%d", S_IRUSR & fileInfo->st_mode);
        printf("-"); 
    }

    if (S_IWUSR & fileInfo->st_mode) { 
        // printf("%d", S_IWUSR & fileInfo->st_mode);
        printf("w"); 
    } 
    else { 
        // printf("%d", S_IWUSR & fileInfo->st_mode);
        printf("-"); 
    }

    if (S_IXUSR & fileInfo->st_mode) { 
        // printf("%d", S_IXUSR & fileInfo->st_mode);
        printf("x"); 
    }
    else { printf("-"); }

    // Group
    if (S_IRGRP & fileInfo->st_mode) {
        // printf("%d", S_IRGRP & fileInfo->st_mode);
        printf("r"); 
    } 
    else { 
        // printf("%d", S_IRGRP & fileInfo->st_mode);
        printf("-"); 
    }

    if (S_IWGRP & fileInfo->st_mode) { 
        // printf("%d", S_IWGRP & fileInfo->st_mode);
        printf("w" ); 
    }
    else { 
        // printf("%d", S_IWGRP & fileInfo->st_mode);
        printf("-"); 
    }

    if (S_IXGRP & fileInfo->st_mode) { 
        // printf("%d", S_IXGRP & fileInfo->st_mode);
        printf("x"); 
    }
    else { 
        // printf("%d", S_IXGRP & fileInfo->st_mode);
        printf("-"); 
    }

    // Others
    if (S_IROTH & fileInfo->st_mode) { 
        // printf("%d", S_IROTH & fileInfo->st_mode);
        printf("r"); 
    } 
    else { 
        // printf("%d", S_IROTH & fileInfo->st_mode);
        printf("-"); 
    }

    if (S_IWOTH & fileInfo->st_mode) { 
        // printf("%d", S_IWOTH & fileInfo->st_mode);
        printf("w"); 
    }
    else { 
        // printf("%d", S_IWOTH & fileInfo->st_mode);
        printf("-"); 
    }

    if (S_IXOTH & fileInfo->st_mode) { 
        // printf("%d", S_IXOTH & fileInfo->st_mode);
        printf("x"); 
    } 
    else { 
        // printf("%d", S_IXOTH & fileInfo->st_mode);
        printf("-"); 
    }
}
