#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int i = 0;
void *print_message_function(void *ptr);
int main()

{

    pthread_t thread1, thread2;

    int thread1Return;
    int thread2Return;

    char *message1 = "Thread1 is running!!";
    char *message2 = "Thread2 is running!!";


    thread1Return = pthread_create(&thread1, NULL, print_message_function,(void *)message1);


    thread2Return = pthread_create(&thread2, NULL, print_message_function,(void*) message2);


    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);


    printf("Thread1 returns: %d\n", thread1Return);
    printf("Thread2 returns: %d\n", thread2Return);


    printf("main() thread is finished!!\n");


    exit(0);

}


// Function used for threads

void *print_message_function(void *ptr) {

    char *message;

    message = (char *)ptr;

    i++;

    printf("%s, i: %d\n", message, i);

}
