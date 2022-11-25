#include "MySem.h"
#include "MyShm.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>

void signalHandler(int signum);

int shmid = 0;
int *shmaddr = NULL;
int semidServ = 0;
int semidClnt = 0;

int main(int argc, char const *argv[]) {
    int req = 0;
    int res = 0;

    shmid = openShm(MY_SHM_KEY);
    shmaddr = shmat(shmid, NULL, 0);
    semidServ = openSem(MY_SEM_SERV_KEY);
    semidClnt = openSem(MY_SEM_CLNT_KEY);

    signal(SIGINT, signalHandler);

    while (1) {
        printf("<< ");
        scanf("%d", &req);
        fflush(stdout);
        fflush(stdin);

        // lockSem으로 못들어오게 막는다
        lockSem(semidClnt);
        // 받은 숫자 정보를 memcpy
        memcpy(shmaddr, &req, sizeof(int));
        // 서버를 unlock하여 서버에게 정보를 받음
        unlockSem(semidServ);
        // 클라이언트 닫기
        lockSem(semidClnt);
        // 서버에게 정보 받기
        memcpy(&res, shmaddr, sizeof(int));
        unlockSem(semidClnt);
        printf(">> %d\n", res);
    }
    return 0;
}
void signalHandler(int signum) {
    if (signum == SIGINT) {
        shmdt(shmaddr);
        exit(0);
    }
}
