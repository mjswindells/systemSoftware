#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    sigset_t set;
    // 시그널 집합(set)의 모든 비트를 0으로 설정
    // sigfillset은 모든 비트를 1로 설정
    sigemptyset(&set);
    // 시그널 집합에서 지정한 시그널의 비트를 1로 설정
    // sigdelset은 지정한 비트를 0으로 설정
    sigaddset(&set, SIGUSR1);
    // sigismember : 지정한 시그널의 설정확인
    //  설정 : 1        설정x : 0
    printf("SIGUSR1 : %d\n", sigismember(&set, SIGUSR1));
    printf("SIGUSR2 : %d\n", sigismember(&set, SIGUSR2));
    return 0;
}
