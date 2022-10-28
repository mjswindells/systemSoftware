#include "MyShm.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

// key값을 가지고 공유메모리 생성
int creatShm(int key) {
    int shmid =
        shmget((key_t)key, SHM_MAX_SIZE, IPC_CREAT | IPC_EXCL | SHM_PERMS);
    if (shmid == -1) {
        perror("creatShm() error!");
        exit(-1);
    }
    return shmid;
}

// 공유메모리 열기
int openShm(int key) {
    int shmid = shmget((key_t)key, SHM_MAX_SIZE, IPC_CREAT);
    return shmid;
}

int closeShm(int shmid) { return shmctl(shmid, IPC_RMID, 0); }
