#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_PATH_LEN 1024

int main(int argc, char const *argv[]) {
    char cwd[MAX_PATH_LEN + 1] = {
        '\0',
    };
    if (getcwd(cwd, MAX_PATH_LEN) == NULL) {
        perror("getcwd() error!");
        exit(-1);
    }
    printf("Current work directory: %s\n", cwd);
    if (chdir("..") == -1) {
        perror("chdir() error!");
        exit(-1);
    }
    puts("Move to ..");
    if (getcwd(cwd, MAX_PATH_LEN) == NULL) {
        perror("getcwd() error!");
        exit(-1);
    }
    printf("Current work directory: %s\n", cwd);
    return 0;
}
