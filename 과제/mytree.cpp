#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void myError(const char *msg);
void get_fileInfo(const char *pathname);

int main() {
    char path[200];
    getcwd(path, 200);
    DIR *dirp = opendir(path);
    struct dirent *dirInfo;

    // mytree 함수 만들기 이 때 . 하고 ..은 다 무시
    while ((dirInfo = readdir(dirp)) != NULL) {
        char *dname = dirInfo->d_name;
        get_fileInfo(dname);
    }

    get_fileInfo("./..");
    return 0;
}
void myError(const char *msg) {
    perror(msg);
    exit(-1);
}
void get_fileInfo(const char *pathname) {
    struct stat fileInfo;
    struct passwd *userInfo;
    if (stat(pathname, &fileInfo) == -1) {
        myError("stat() error! ");
    }

    userInfo = getpwuid(fileInfo.st_uid);

    printf("  [");
    // inode number
    printf("%ld ", fileInfo.st_ino);
    // device number
    printf("%ld ", fileInfo.st_dev);
    // file type
    if (S_ISREG(fileInfo.st_mode)) {
        printf("-");
    } else if (S_ISDIR(fileInfo.st_mode)) {
        printf("d");
    } else if (S_ISLNK(fileInfo.st_mode)) {
        printf("l");
    } else if (S_ISSOCK(fileInfo.st_mode)) {
        printf("s");
    } else if (S_ISFIFO(fileInfo.st_mode)) {
        printf("p");
    } else if (S_ISCHR(fileInfo.st_mode)) {
        printf("c");
    } else if (S_ISBLK(fileInfo.st_mode)) {
        printf("b");
    }
    // User
    if (S_IRUSR & fileInfo.st_mode) {
        printf("r");
    } else {
        printf("-");
    }
    if (S_IWUSR & fileInfo.st_mode) {
        printf("w");
    } else {
        printf("-");
    }
    if (S_IXUSR & fileInfo.st_mode) {
        printf("x");
    } else {
        printf("-");
    }
    // Group
    if (S_IRGRP & fileInfo.st_mode) {
        printf("r");
    } else {
        printf("-");
    }
    if (S_IWGRP & fileInfo.st_mode) {
        printf("w");
    } else {
        printf("-");
    }
    if (S_IXGRP & fileInfo.st_mode) {
        printf("x");
    } else {
        printf("-");
    }
    // Others
    if (S_IROTH & fileInfo.st_mode) {
        printf("r");
    } else {
        printf("-");
    }
    if (S_IWOTH & fileInfo.st_mode) {
        printf("w");
    } else {
        printf("-");
    }
    if (S_IXOTH & fileInfo.st_mode) {
        printf("x");
    } else {
        printf("-");
    }
    printf(" ");

    // 소유자
    printf("%s\t", userInfo->pw_name);
    // file size
    int size = fileInfo.st_size;
    if (size < 1000) {
        printf("  %d]", size);
    } else {
        double ssize = size;
        ssize /= 1000;
        printf("%0.1f%s]", ssize, "K");
    }
    // 파일 이름
    printf("    %s\n", pathname);
}
