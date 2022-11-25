#include <pthread.h>
#include <stdio.h>

// gcc pthread_cread.c pthread_creat.out -lpthread
void *myThread(void *arg);

int main(int argc, char const *argv[]) {
    pthread_t tid = 0;
    int count = 5;
    int *status;
    // pthread_self() : 현재 스레드의 TID 반환
    //
    // pthread_create(TID저장할 포인터 , NULL,
    // 스레드 실행할 함수 포인터 , 인자);
    printf("Hello. I'm main thread: %ld\n", pthread_self());
    if (pthread_create(&tid, NULL, myThread, (void *)&count)) {
        perror("pthread_create() error!");
        return -1;
    }
    // pthread_join : 스레드가 종료할 때가지 대기함
    pthread_join(tid, (void **)&status);
    printf("Thread %ld exit\n", tid);
    return 0;
}
void *myThread(void *arg) {
    int i = 0;
    // 인자를 int형으로 형변환
    int count = *(int *)arg;
    int status = 0;
    printf("Hello. I\'m new thread: %ld\n", pthread_self());
    for (i = count; i > 0; --i) {
        printf("%d ...\n", i);
    }
    // 현재 스레드 종료
    pthread_exit((void *)&status);
}
