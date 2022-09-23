#include <iostream>
#include <stdio.h>
#include <unistd.h>

void fork2() {
    int x = 1;
    printf("L0%d\n", ++x);
    fork();
    printf("L1%d\n", ++x);
    fork();
    printf("Bye%d\n", ++x);
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
int main() {
    fork2();
    // printf("\n");

    // fork5();
}
