#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "chatshm.h"

int main()
{
    int shmid;
    int shmbufindex, readmsgcount;
    CHAT_INFO *chatInfo = NULL;

    //address type is void
    void *shmaddr = (void *)0; //typecast
    shmid = shmget((key_t)3836, sizeof((CHAT_INFO), 0666|IPC_CREAT|IPC_EXCL);

    //if error occured
    if(shmid < 0){
            shmid = shmget((key_t)3836, sizeof((CHAT_INFO), 0666);
            //shmat()
    }

    return 0;
}
