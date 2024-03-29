#ifndef __MYSHM_H__
#define __MYSHM_H__

#define SHM_MAX_SIZE 512
#define SHM_PERMS 0600

#define MY_SHM_KEY 1234

// 공유메모리 생성
int creatShm(int key);
// 공유메모리 open
int openShm(int key);
// 공유메모리 닫기
int closeShm(int shmid);

#endif // !__MYSHM_H__
