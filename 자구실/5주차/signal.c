#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void mySigHandler(int signum);

int Cnt = 0;

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [count]", argv[0]);
        exit(0);
    }
    // 시그널 핸들러 재정의
    // SIG_ERR : 시그널이 에러남
    // sighandler_t signal(int signum, sighandler_t handler);
    if (signal(SIGUSR1, mySigHandler) == SIG_ERR) {
        perror("signal() error!");
    }
    printf("Hello. My PID is : %d\n", getpid());

    // atoi : string to int
    Cnt = atoi(argv[1]);

    while (Cnt > 0) {
        printf("%d ... ", Cnt);
        // 버퍼 비우기
        fflush(stdout);
        Cnt -= 1;
        sleep(1);
    }
    return 0;
}
void mySigHandler(int signum) {
    if (signum == SIGUSR1) {
        Cnt = 3;
    }
}
