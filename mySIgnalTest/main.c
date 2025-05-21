#include <stdio.h>

#define MY_SIGNAL  2

#define MAX_SIGNAL 32

typedef void Sigfunc (int);

Sigfunc *signal_tak (int, Sigfunc *);


void sig_usr (int);


#define SIG_DDD_X (void (*) ()) -1

#define SIG_DDD_Y (void (*) ())  0

#define SIG_DDD_Z (void (*) ())  1


struct {

    int signo;

    Sigfunc *signal_handler;

} sigtab[MAX_SIGNAL];


int main(void)

{

    int signo;

    if (signal_tak (MY_SIGNAL, sig_usr) == SIG_DDD_Z)

    // 이렇게 해도 됩니다.

    // if (signal_tak (1, sig_usr) == 1)

        printf("Return 1\n");


    // 시그널이 여기에서 발생한다고 가정하면

    // 해당 시그널에 대한 핸들러가 실행됩니다.

    signo = MY_SIGNAL;

    sigtab[MY_SIGNAL].signal_handler(signo);


    return 0;

}
