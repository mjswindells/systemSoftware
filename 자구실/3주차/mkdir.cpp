#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PERMS 0755
#define MAX_PATH_LEN 1024

int main(int argc, char const *argv[]) {

    if (argc != 2) {
        printf("Usage: %s [pathname] n ", argv[0]);
        exit(-1);
    }

    if (mkdir(argv[1], PERMS) == -1) {
        perror("mkdir() error!");
        exit(-2);
    }

    return 0;
}
