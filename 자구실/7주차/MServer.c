#include "MyMsg.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

void signalHandler(int signum);
int calculate(Calc calc);

key_t mykey = 0;
int msqid = 0;

int main(int argc, char const *argv[]) {
    MsgCalc msgCalc;
    MsgRslt msgRslt;
    mykey = ftok("mymsgkey", 1);             // 키 생성
    msqid = msgget(mykey, IPC_CREAT | 0600); // 메시지 큐 생성

    // SIGINT가 발생했을 때의 시그널 생성
    signal(SIGINT, signalHandler);

    while (1) {
        puts("Wait ...");
        memset(&msgCalc, 0x00, sizeof(MsgCalc));
        msgrcv(msqid, &msgCalc, MSG_SIZE_CALC, MSG_TYPE_CALC, 0);
        printf("Receive: %d %c %d\n", msgCalc.calc.x, msgCalc.calc.op,
               msgCalc.calc.y);
        memset(&msgRslt, 0x00, sizeof(MsgRslt));
        msgRslt.mtype = MSG_TYPE_RSLT;
        msgRslt.rslt = calculate(msgCalc.calc);
        // 클라이언트에게서 받은 정보를 계산하여 클라이언트에게 보내줌
        msgsnd(msqid, &msgRslt, MSG_SIZE_RSLT, 0);
        printf("Send: %d\n", msgRslt.rslt);
        fflush(stdout);
    }
    return 0;
}
// 핸들러를 정의하여 SIGINT가 발생했을 때 메세지큐를 닫아주는 역할을 함
void signalHandler(int signum) {
    if (signum == SIGINT) {
        msgctl(msqid, IPC_RMID, NULL);
        exit(0);
    }
}
int calculate(Calc calc) {
    switch (calc.op) {
    case '+':
        return calc.x + calc.y;
    case '-':
        return calc.x - calc.y;
    case '*':
        return calc.x * calc.y;
    case '/':
        return (int)(calc.x / calc.y);
    default:
        return 0;
    }
}
