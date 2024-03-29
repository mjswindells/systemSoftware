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
    union semun semunBuf;

    shmid = creatShm(MY_SHM_KEY);
    shmaddr = shmat(shmid, NULL, 0);
    semidServ = creatSem(MY_SEM_SERV_KEY);
    semunBuf.val = 0;

    semctl(semidServ, 0, SETVAL, semunBuf);

    semidClnt = creatSem(MY_SEM_CLNT_KEY);
    semunBuf.val = 1;

    semctl(semidClnt, 0, SETVAL, semunBuf);
    signal(SIGINT, signalHandler);

    while (1) {
        puts("Wait ...");
        // 락 걸어서 다른 서버 못열게?
        lockSem(semidServ);
        // 클라이언트에게 숫자 받기
        memcpy(&req, shmaddr, sizeof(int));

        res = req + 1;
        // 1더한 정보를 공유메모리에 저장
        memcpy(shmaddr, &res, sizeof(int));

        // 클라이언트에 lock 풀어서 다음 클라이언트가 숫자 넘겨 줄 수 있게
        unlockSem(semidClnt);

        printf("Request: %d\n", req);
        printf("Response: %d\n", res);
        fflush(stdout);
    }
    return 0;
}
void signalHandler(int signum) {
    if (signum == SIGINT) {
        closeSem(semidClnt);
        closeSem(semidServ);
        shmdt(shmaddr);
        closeShm(shmid);
        exit(0);
    }
}
