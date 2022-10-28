#include "MySem.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

int creatSem(int key) {
    int semid = semget((key_t)key, SEM_MAX_NUM, IPC_CREAT | SEM_ERMS);
    if (semid == -1) {
        perror("creatSem() error!");
        exit(-1);
    }
    return semid;
}

int openSem(int key) {
    int semid = semget((key_t)key, 0, IPC_CREAT);
    return semid;
}

// 세마포어 카운트 1 감소
int lockSem(int semid) {
    // sembuf( sem_num, sem_op, sem_flg )
    // sem_num : 세마포어 집합의 인덱스 사이즈 보통 0
    // sem_op  : 세마포어 연산동작 양의 정수인 경우 세마포어 값을 증가
    //           음수인 경우 정수의 값만큼 감소시킴
    // sem_flg : SEM_UNDO : 프로세스가 세마포어를 반환하지 않고 종료하는 경우에
    //                      커널에서 스스로 세마포어 값을 증가시킴
    struct sembuf buf = {0, -1, SEM_UNDO};
    // semop( semid , sembuf * buf , nsops )
    // buf : 연산을 저장한 메모리 영역의 주소
    // nsops : 변경하고자 하는 세마포어의 개수
    return semop(semid, &buf, SEM_MAX_NUM);
}

// 세마포어 카운트 1 증가
int unlockSem(int semid) {
    struct sembuf buf = {0, 1, SEM_UNDO};
    return semop(semid, &buf, SEM_MAX_NUM);
}

int closeSem(int semid) { return semctl(semid, 0, IPC_RMID, 0); }
