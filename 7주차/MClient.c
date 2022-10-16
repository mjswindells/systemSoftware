#include "MyMsg.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
    // ftok : IPC에서 사용할 키를 생성
    key_t mykey = ftok("mymsgkey", 1);
    // msgget : 키값에 해당하는 메세지 큐를 생성
    int msqid = msgget(mykey, IPC_CREAT);
    int x = 0;
    int y = 0;
    char op = 0;
    MsgCalc msgCalc;
    MsgRslt msgRslt;
    puts("Input: [x] [op] [y]");
    while (1) {
        printf("<<< ");
        // 사용자에게 x op y 를 받는다
        scanf("%d %c %d", &x, &op, &y);
        // 버퍼를 비워준다
        fflush(stdout);
        fflush(stdin);
        // 구조체 초기화
        memset(&msgCalc, 0x00, sizeof(MsgCalc));
        // 메세지 유형을 담는 long 자료형
        msgCalc.mtype = MSG_TYPE_CALC;
        msgCalc.calc.x = x;
        msgCalc.calc.y = y;
        msgCalc.calc.op = op;
        // 메세지 큐에 데이터 전송
        // (식별자 , 전송데이터의 포인터, 크기, 0 )
        msgsnd(msqid, &msgCalc, MSG_SIZE_CALC, 0);
        memset(&msgRslt, 0x00, sizeof(MsgRslt));
        // 메세지 큐 데이터 수신
        // ( 식별자, 저장할 공간의 포인터, 크기, 유형, 0)
        msgrcv(msqid, &msgRslt, MSG_SIZE_RSLT, MSG_TYPE_RSLT, 0);
        printf(">>> %d\n", msgRslt.rslt);
    }
    return 0;
}
