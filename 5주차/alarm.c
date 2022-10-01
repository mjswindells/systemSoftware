#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void myAlrmHandler(int signum);

int main(int argc, char const *argv[]) {
    if (signal(SIGALRM, myAlrmHandler) == SIG_ERR) {
        perror("signal() error!");
    }
    // 몇 초 후에 시그널을 전송할 것인지 지정
    alarm(5);
    puts("Sleep ... ");
    sleep(100);
    return 0;
}
void myAlrmHandler(int signum) { puts("Hello! I'm wake!"); }
