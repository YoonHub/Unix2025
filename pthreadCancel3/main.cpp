

#include <iostream>

#include <pthread.h>

#include <unistd.h>



using namespace std;



pthread_t t_thread;

void *ThreadTest(void *arg);



int main(int argc, char *argv[])

{

    int status = 0;

    int arg = 0;

    pthread_attr_t attr;



    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    status = pthread_create(&t_thread, &attr, ThreadTest, &arg);

    pthread_attr_destroy(&attr);



    sleep(10);

    pthread_cancel(t_thread);

    cout << "pthread cancel" << endl;



    return 0;

}



void *ThreadTest(void *arg)

{

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);



    while(1)

    {

        sleep(1);

        cout << "pthread" << endl;

    }

}
