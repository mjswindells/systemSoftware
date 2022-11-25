#ifndef __MYMSG_H__
#define __MYMSG_H__

// 메세지 큐에서 첫번째 long형 메세지 타입에 올 것들 define
#define MSG_TYPE_CALC 1 // 숫자 및 연산자
#define MSG_TYPE_RSLT 2 // 결과 메시지

// 메세지 크기
#define MSG_SIZE_CALC (sizeof(MsgCalc) - sizeof(long))
#define MSG_SIZE_RSLT (sizeof(MsgRslt) - sizeof(long))

struct __Calc {
    int x;
    int y;
    char op;
};
typedef struct __Calc Calc;

// 숫자 및 연산자를 담는 구조체
struct __MsgCalc {
    long mtype;
    struct __Calc calc;
};
typedef struct __MsgCalc MsgCalc;

// 결과를 담는 구조체
struct __MsgRslt {
    long mtype;
    int rslt;
};
typedef struct __MsgRslt MsgRslt;

#endif //!__MYMSG_H__
