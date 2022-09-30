#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

void fork2() {
    int x = 1;
    printf("L0%d\n", ++x);
    pid_t pid = fork();
    printf("L1%d %d\n", ++x, pid);
    pid_t pid2 = fork();
    printf("Bye%d %d %d\n", ++x, pid, pid2);
}
void fork5() {
    printf("L0\n");
    if (fork() == 0) {
        printf("L1\n");
        if (fork() == 0) {
            printf("L2\n");
            fork();
        }
    }
    printf("Bye\n");
}
int fork10() {
    int N = 100;
    pid_t pid[N];
    int i;
    int child_status;
    for (i = 0; i < N; i++)
        if ((pid[i] = fork()) == 0) {
            if (i == 30) {
                printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
            }
            if (i == 99) {
                printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
            }
            // exit(n) : 뒤에 wait(k)에서 k에 n의 값이 오게된다
            exit(100 + i); /* Child */
        }
    for (i = 0; i < N; i++) {
        // child_status는 wait함수가 돌아가면서 알아서 할당된다
        // exit(i)으로 종료된 프로세스의 i*256의 값이 저장되고
        // wait의 return값은 해당 프로세스의 pid이다
        pid_t wpid = wait(&child_status);
        if (WIFEXITED(child_status))
            printf("Child %d terminated with exit status %d\n", wpid,
                   WEXITSTATUS(child_status)); // status >> 8;
        else
            printf("Child %d terminate abnormally\n", wpid);
    }
    return 0;
}
int main() {
    int a = 0;
    a = fork10();
    // fork2();
    // printf("\n");
    // fork5();
}
