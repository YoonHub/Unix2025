

#include <stdio.h>

#include <setjmp.h>

#include <time.h>

#include <signal.h>

#include <stdlib.h>

#include <errno.h>


static voidsig_usr1(int);

static voidsig_alrm(int);

static sigjmp_bufjmpbuf;

static volatile sig_atomic_tcanjump;


void pr_mask(const char *str)

{

    sigset_t    sigset;

    int         errno_save;

    errno_save = errno;     /* we can be called by signal handlers */

    if (sigprocmask(0, NULL, &sigset) < 0)

        printf("sigprocmask error");

    printf("%s", str);

    if (sigismember(&sigset, SIGINT))   printf("SIGINT ");

    if (sigismember(&sigset, SIGQUIT))  printf("SIGQUIT ");

    if (sigismember(&sigset, SIGUSR1))  printf("SIGUSR1 ");

    if (sigismember(&sigset, SIGALRM))  printf("SIGALRM ");

    /* remaining signals can go here */

    printf("\n");

    errno = errno_save;

}


int main(void){

    if (signal(SIGUSR1, sig_usr1) == SIG_ERR)

    printf("signal(SIGUSR1) error");

    if (signal(SIGALRM, sig_alrm) == SIG_ERR)

    printf("signal(SIGALRM) error");


    pr_mask("starting main: ");/* {Prog prmask} */


    if (sigsetjmp(jmpbuf, 1)) {


    pr_mask("ending main: ");


    exit(0);

    }


}


static void

sig_usr1(int signo)

{

time_tstarttime;


if (canjump == 0)

return;/* unexpected signal, ignore */


pr_mask("starting sig_usr1: ");


alarm(3);/* SIGALRM in 3 seconds */

starttime = time(NULL);

for ( ; ; )/* busy wait for 5 seconds */

if (time(NULL) > starttime + 5)

break;


pr_mask("finishing sig_usr1: ");


canjump = 0;

siglongjmp(jmpbuf, 1);/* jump back to main, don't return */

//longjmp(jmpbuf, 1);

}


static void

sig_alrm(int signo)

{

pr_mask("in sig_alrm: ");

}


