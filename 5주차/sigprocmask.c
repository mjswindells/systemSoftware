#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void mySigHandler(int signum);

int main(int argc, char const *argv[]) {
    int cnt = 10;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    // 시그널을 블록상태로 설정하거나 해제가능
    // unblock 시키거나 해당 시그널에 대한 action을 ignore로 변경전가지 실행이
    // 안됨
    sigprocmask(SIG_BLOCK, &set, NULL); // SIGUSR1 시그널을 블록
    signal(SIGUSR1, mySigHandler);
    printf("My PID is : %d\n", getpid());
    while (cnt > 0) {
        printf("%d\n", cnt);
        fflush(stdout);
        cnt -= 1;
        sleep(1);
    }
    return 0;
}
void mySigHandler(int signum) {
    if (signum == SIGUSR1) {
        puts("Hello!");
    }
}
