#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <errno.h>

#include <pthread.h>

#include <sys/types.h>

#include <arpa/inet.h>

#include <netinet/in.h>

#include <sys/socket.h>


void *threadFunc(void *arg)

{

    int count = 0;

    printf("new thread started ....\n");

    int retval;


    while(1)

    {

    printf("count = %d \n", count++);

    sleep(1);

    //pthread_testcancel();

    }


    pthread_exit((void *) &count);

}


int main(int argc, char *argv[])

{

    pthread_t tid;

    int retval;

    void *res;

    retval = pthread_create(&tid, NULL, threadFunc, NULL);

    if(retval != 0)

    {

    perror("pthread_create : ");

    exit(EXIT_FAILURE);

    }

    sleep(5);


    retval = pthread_cancel(tid);

if(retval != 0)

{

    perror("pthread_canceled : ");

    exit(EXIT_FAILURE);

}

retval = pthread_join(tid, &res);

if(retval != 0)

{

    perror("pthread_join : ");

    exit(EXIT_FAILURE);

}

if(res == PTHREAD_CANCELED)

{

    printf("thread canceled\n");

}

else

{

    printf("thread is normal exit retval = %ld \n", (long)res);

}

    exit(EXIT_SUCCESS);

}
