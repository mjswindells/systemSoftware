#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void myError(const char *msg);
void get_fileInfo(const char *pathname);
void mytree(char *pathname, int depth, bool shape);
void concat_path(char *dest, char *src1, char *src2);

int dcnt = 0;
int fcnt = 0;
char treeshape[256] = "";

int main() {
    char path[256];
    getcwd(path, 256);
    mytree(path, 0, false);
    printf("\n%d directories, %d files\n", dcnt, fcnt);
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
        myError("stat_get() error! ");
    }
    userInfo = getpwuid(fileInfo.st_uid);

    char str[256];
    strcpy(str, pathname);
    char *temp = strtok(str, "/");
    char *path;
    while (temp != NULL) {
        path = temp;
        temp = strtok(NULL, "/");
    }

    printf(" [");
    // inode number
    printf("%7ld ", fileInfo.st_ino);
    // device number
    printf("%-2ld ", fileInfo.st_dev);
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
    printf("%s", userInfo->pw_name);
    // file size
    int size = fileInfo.st_size;
    if (size < 1000) {
        printf("%9d]", size);
    } else {
        double ssize = size;
        ssize /= 1000;
        printf("%8.1fK]", ssize);
    }
    // 파일 이름
    printf("  %s\n", path);
}

void concat_path(char *dest, char *src1, char *src2) {
    strcpy(dest, src1);
    strcat(dest, "/");
    strcat(dest, src2);
}

int cntDIR(DIR *dirp) {
    struct dirent *dirInfo;
    int cnt = 0;
    while ((dirInfo = readdir(dirp)) != NULL) {
        char *dname = dirInfo->d_name;
        if (strncmp(dname, ".", 1) == 0)
            continue;
        cnt++;
    }
    return cnt;
}

void cutstr(void) {
    int l = strlen(treeshape);
    treeshape[l - 1] = '\0';
}

void draw(void) {
    int l = strlen(treeshape);
    for (int i = 0; i < l; i++) {
        if (treeshape[i] == '1') {
            printf("│   ");
        } else {
            printf("    ");
        }
    }
}

void mytree(char *pathname, int depth, bool shape) {
    DIR *dirp = opendir(pathname);
    struct dirent *dirInfo;
    int a = 0;

    if (depth == 0) {
        printf(".\n");
        int cnt = cntDIR(dirp);
        dirp = opendir(pathname);

        while ((dirInfo = readdir(dirp)) != NULL) {
            char *dname = dirInfo->d_name;

            if (strncmp(dname, ".", 1) == 0)
                continue;
            if (++a == cnt) {
                char full_path[256];
                concat_path(full_path, pathname, dname);
                mytree(full_path, depth + 1, true);
            } else {
                char full_path[256];
                concat_path(full_path, pathname, dname);
                mytree(full_path, depth + 1, false);
            }
        }
    } else {
        struct stat fileInfo;
        if (stat(pathname, &fileInfo) == -1) {
            myError("stat_mytree() error! ");
        }
        if (S_ISDIR(fileInfo.st_mode)) {
            dcnt++;
            draw();
            if (shape) {
                strcat(treeshape, "0");
                printf("└──");
            } else {
                strcat(treeshape, "1");
                printf("├──");
            }

            int cnt = cntDIR(dirp);
            dirp = opendir(pathname);
            get_fileInfo(pathname);

            while ((dirInfo = readdir(dirp)) != NULL) {
                char *dname = dirInfo->d_name;
                if (strncmp(dname, ".", 1) == 0)
                    continue;
                if (++a == cnt) {
                    char full_path[256];
                    concat_path(full_path, pathname, dname);
                    mytree(full_path, depth + 1, true);
                } else {
                    char full_path[256];
                    concat_path(full_path, pathname, dname);
                    mytree(full_path, depth + 1, false);
                }
            }
            cutstr();
        } else if (S_ISREG(fileInfo.st_mode)) {
            fcnt++;
            draw();
            if (shape) {
                cutstr();
                strcat(treeshape, "0");
                printf("└──");
            } else {
                printf("├──");
            }
            get_fileInfo(pathname);
        } else {
            return;
        }
    }
    closedir(dirp);
}
