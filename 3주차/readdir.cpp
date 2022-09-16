#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
    struct stat fileInfo;
    DIR *dirp;
    struct dirent *dirInfo;
    if (argc != 2) {
        printf("Usage: %s [pathname]\n", argv[0]);
        exit(-1);
    }
    if (stat(argv[1], &fileInfo) == -1) {
        perror("stat() error!");
        exit(-1);
    }
    if (!S_ISDIR(fileInfo.st_mode)) {
        fprintf(stderr, "%s is not directory!\n", argv[1]);
        exit(-1);
    }
    dirp = opendir(argv[1]);
    while ((dirInfo = readdir(dirp)) != NULL) {
        printf("inode No.: %lld, Name: %s\n", dirInfo->d_ino, dirInfo->d_name);
    }
    closedir(dirp);
    return 0;
}
