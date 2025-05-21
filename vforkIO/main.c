

#include <stdio.h>

#include <stdlib.h>


int globvar = 6; /* external variable in initialized data */


int main(void)

{

    int var; /* automatic variable on the stack */

    int ret;

    pid_t pid;


    var = 88;

    printf("before vfork\n");


    if ((pid = vfork()) < 0) {

        printf("vfork error");

    }

    else if (pid == 0) {

        globvar++; var++;

        /* we don’t flush stdio */

        /* child */

        /* modify parent’s variables */

        //_exit(0); /* child terminates */

        // exit(0);

    }

    else if (pid>0)

        sleep(3);

    /* parent continues here */

    ret = printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,var);

    printf("ret: %d:\n", ret);


    exit(0);

}


