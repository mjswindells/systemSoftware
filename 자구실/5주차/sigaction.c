#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void mySigHandler(int signum);

int main(int argc, char const *argv[]) {
    sigset_t set;
    struct sigaction action;

    sigemptyset(&set);
    sigaddset(&set, SIGUSR2);

    // 시그널이 처리되는 동안 유닉스 커널에서
    // 해당 시그널을 블록하지 못하게 하는 플래그
    action.sa_flags = SA_NODEFER;
    action.sa_handler = mySigHandler;
    action.sa_mask = set;
    // 시그널 핸들러 재정의
    // SIGUSR1이 처리되는 동안에, SIGUSR2는 블록됨.
    sigaction(SIGUSR1, &action, NULL);
    signal(SIGUSR2, mySigHandler);
    printf("My PID is : %d\n", getpid());
    while (1) {
        pause();
    }
    return 0;
}
void mySigHandler(int signum) {
    int i = 0;
    if (signum == SIGUSR1) {
        puts("SIGUSR1 handling start");
        for (i = 5; i > 0; --i) {
            printf("%d .. ", i);
            fflush(stdout);
            sleep(1);
        }
        puts("SIGUSR1 handled!");
    } else if (signum == SIGUSR2) {
        puts("SIGUSR2 handled!");
    }
}
