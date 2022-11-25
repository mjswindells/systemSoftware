#include <pthread.h>
#include <stdio.h>
void *myThread1(void *arg);
void *myThread2(void *arg);
void cleanupHandler(void *arg);
pthread_mutex_t mutex;
int sharedNum = 0;
int main(int argc, char const *argv[]) {
    pthread_t tid1 = 0;
    pthread_t tid2 = 0;
    int *status;
    // pthread_mutex_init(&mutex, NULL)
    // mutex를 초기화함
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&tid1, NULL, myThread1, NULL)) {
        perror("pthread_create() error!");
        // 실패시 END로 감
        goto END;
    }
    if (pthread_create(&tid2, NULL, myThread2, NULL)) {
        perror("pthread_create() error!");
        // 실패시 END로 감
        goto END;
    }
    // tid1이 종료할때까지 대기
    pthread_join(tid1, (void **)&status);
    // tid2이 종료할때까지 대기
    pthread_join(tid2, (void **)&status);
END:
    // 뮤텍스를 제거함
    pthread_mutex_destroy(&mutex);
    return 0;
}
void *myThread1(void *arg) {
    int i = 0;
    int status = 0;
    // cleanup 핸들러 스택에 저장
    pthread_cleanup_push(cleanupHandler, "Thread 1");
    // 뮤텍스를 잠금 현재 스레드가 다 실행된 후 다음 스레드가 실행함
    pthread_mutex_lock(&mutex);
    puts("Thread 1");
    for (i = 0; i < 5; ++i) {
        sharedNum += i;
        printf("%d ", sharedNum);
    }
    puts("");
    // 위에서 지정한 cleanup 핸들러 실행 후 삭제
    pthread_cleanup_pop(1);
    pthread_exit((void *)&status);
}
void *myThread2(void *arg) {
    int i = 0;
    int status = 0;
    pthread_cleanup_push(cleanupHandler, "Thread 2");
    pthread_mutex_lock(&mutex);
    puts("Thread 2");
    for (i = 0; i < 5; ++i) {
        sharedNum -= i;
        printf("%d ", sharedNum);
    }
    puts("");
    pthread_cleanup_pop(1);
    pthread_exit((void *)&status);
}
void cleanupHandler(void *arg) {
    pthread_mutex_unlock(&mutex);
    printf("Cleanup: %s\n", (char *)arg);
}
