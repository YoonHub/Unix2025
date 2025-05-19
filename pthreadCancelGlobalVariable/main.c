

#include <stdio.h>

#include <time.h>

#include <pthread.h>

#include <unistd.h>

#include <stdlib.h>


int temp;




pthread_mutex_t mutex_lock;




void cleanup(void *arg)

{

    printf("cleanup: %s\n", (char *)arg);

}




void* th1(void *data)

{

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    pthread_cleanup_push(cleanup, "Cleaning ... ");

    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);


    for(int i=0;i<100;i++){


        pthread_mutex_lock(&mutex_lock);


        temp++;


        printf("th1 temp:%d\n",temp);

        sleep(1);


        pthread_mutex_unlock(&mutex_lock);



    }


    pthread_cleanup_pop(0);


    return NULL;


}


int main(void)

{


    pthread_t pid[2];


    pthread_attr_t attr;




    int thr_id;


    int status;


    temp=0;




    pthread_mutex_init(&mutex_lock, NULL);


    pthread_attr_init(&attr);


    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);




    thr_id = pthread_create(&pid[0], &attr, th1, NULL);


    if (thr_id < 0)


    {


        perror("thread create error : ");


        exit(0);


    }




    thr_id = pthread_create(&pid[1], &attr, th1, NULL);


    if (thr_id < 0)


    {


        perror("thread create error : ");


        exit(0);


    }


    for(int i=0;i<10;i++){


        printf("Main working...\n");


        if(i==5){//메인함수 종료 조건


            pthread_cancel(pid[0]);


            pthread_cancel(pid[1]);


            printf("cancel %ld %ld\n",pid[0],pid[1]);

            exit(0);


            break;


        }


        sleep(1);


    }


    printf("Main Exit\n");


    return 0;


}
