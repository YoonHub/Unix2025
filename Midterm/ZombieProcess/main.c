#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <wait.h>


int main(int argc, char ** argv)

{

    pid_t   pid, waitPID;

    int     status, data = 10;


    printf("parent process id: %d\n", getpid());


    if ((pid = fork()) < 0)

        perror("fork error");


    if (pid == 0) { //child

        printf("child process id: %d\n", getpid());

        data = data + 10;

        exit(7);

    } else {

        data = data - 10;

        sleep(20);

    }


    waitPID = wait(&status);


    if (waitPID != pid) // wait for child

        perror("Wait error");


    printf("\nwaitPID: %d\n", waitPID);


    printf("data: %d \n", data);


    return 0;

}
