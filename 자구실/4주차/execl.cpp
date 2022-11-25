#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    pid_t pid = 0;
    int status = 0;

    pid = fork();
    switch (pid) {
    case -1:
        perror("fork() error!");
        exit(-1);
    case 0:
        execl("/bin/ls", "ls", "-a", "-l", NULL);
        break;
    }
    if (pid > 0) {
        wait(&status);
    }
    return 0;
}
