#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_SHM_SIZE 512

void signalHandler(int signum);
void myfunc(void);

key_t mykey = 0;
int shmid = 0;
int *shmaddr = NULL;

int main(int argc, char const *argv[]) {
    mykey = ftok("myshmkey", 2);
    // 공유메모리 생성
    // ( 키 값 , 크기 , 플래그)
    shmid = shmget(mykey, MAX_SHM_SIZE, IPC_CREAT | 0600);
    // 프로세스가 공유 메모리를 사용할 수 있도록 연결함
    // ( 식별자 ,DRAM주소 보통 NULL, 플래그)
    shmaddr = shmat(shmid, NULL, 0);
    signal(SIGINT, signalHandler);
    signal(SIGUSR1, signalHandler);
    while (1) {
        puts("Wait ...");
        pause();
    }
    return 0;
}
void signalHandler(int signum) {
    struct shmid_ds buf;
    if (signum == SIGINT) {
        // 공유 메모리를 현재 프로세스로부터 분리 ( 공유메모리의 주소)
        shmdt(shmaddr);
        // 공유 메모리 제어 IPC_RMID : 제거
        shmctl(shmid, IPC_RMID, NULL);
        exit(0);
    } else if (signum == SIGUSR1) {
        myfunc();
    }
}
void myfunc(void) {
    struct shmid_ds buf;
    int data = 0;
    memcpy(&data, shmaddr, sizeof(int));
    printf("Receive: %d\n", data);
    data += 1;
    // 받은 값보다 1 큰 값을 저장하기 위함
    memcpy(shmaddr, &data, sizeof(int));
    printf("Send: %d\n", data);
    // IPC_STAT : 지정한 메모리공간에 저장
    shmctl(shmid, IPC_STAT, &buf);
    // 마지막으로 작동한 pid 에 보낸다
    kill(buf.shm_lpid, SIGUSR1);
}
