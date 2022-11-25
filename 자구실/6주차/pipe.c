#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int num = 0;
    pid_t pid;
    int pipefd[2] = {
        0,
    };
    // 시간을 기반으로 rand함수 사용
    srand(time(NULL));

    // 리눅스에서 pipe 4KB
    // 파이프 사이즈보다 작은 값을 write하면 잘 작동되고
    // 파이프 사이즈보다 큰 값을 write하면 write를 잘라서 보낸다
    if (pipe(pipefd) == -1) {
        perror("pipe() error!");
        return -1;
    }
    pid = fork();
    if (pid == -1) {
        perror("fork() error!");
    } else if (pid == 0) { // Child
        close(pipefd[0]);  // close unused read end
        num = rand() % 10;
        write(pipefd[1], (int *)&num, sizeof(int));
        close(pipefd[1]);
    } else {              // Parent
        close(pipefd[1]); // close unused write end
        while (read(pipefd[0], (int *)&num, sizeof(int)) < 0) {
            ;
        }
        printf("Num: %d\n", num);
        close(pipefd[0]);
        wait(&pid);
    }
    return 0;
}
