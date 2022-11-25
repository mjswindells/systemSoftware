#ifndef __MYSEM_H__
#define __MYSEM_H__

#define SEM_MAX_NUM 1
#define SEM_ERMS 0600

#define MY_SEM_SERV_KEY 1357
#define MY_SEM_CLNT_KEY 2468

// 유니온은 자원들을 효율적으로 관리해 통신에 유리하다
// 구조체와 다른 점은 하나의 큰 메모리 영역에서
// 내부 자원들이 다 같이 사용하는 느낌
// 구조체는 각 자원마다 자리가 있다
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
};

int creatSem(int key);
int openSem(int key);
int lockSem(int semid);
int unlockSem(int semid);
int closeSem(int semid);

#endif // !__MYSEM_H__
