#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int i = 0;

void *print_message_function(void *ptr);

int main() {
    pthread_t thread;
    char *messages[5] = {
        "Thread1 is finished",
        "Thread2 is finished",
        "Thread3 is finished",
        "Thread4 is finished",
        "Thread5 is finished"
    };

    int t;

    for (t = 0; t < 5; t++) {
        pthread_create(&thread, NULL, print_message_function, (void *)messages[t]);
        pthread_join(thread, NULL);
    }

    printf("Final _i: %d\n", i);
    printf("main() thread is finished!!\n");

    return 0;
}

void *print_message_function(void *ptr) {
    char *message = (char *)ptr;
    i++;
    printf("%s\n", message);
    return NULL;
}
