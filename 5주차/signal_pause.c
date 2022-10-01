#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void mySigHandler(int signum);

int main(int argc, char const *argv[]) {
    // 시그널 핸들러 재정의
    if (signal(SIGINT, mySigHandler) == SIG_ERR) {
        perror("signal() error!");
    }
    if (signal(SIGUSR1, mySigHandler) == SIG_ERR) {
        perror("signal() error!");
    }
    printf("Hello. My PID is : %d\n", getpid());
    while (1) {
        puts("Pause ...");
        // 프로세스가 시그널을 수신할 떄까지 동작을 중지함
        pause();
    }
    return 0;
}
void mySigHandler(int signum) {
    if (signum == SIGINT) {
        printf("Hello! SIGINT.\n");
    } else if (signum == SIGUSR1) {
        printf("Hello! SIGUSR1.\n");
    }
}
