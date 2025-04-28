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
    if(shmid < 0){
        shmid = shmget((key_t)3836, sizeof((CHAT_INFO), 0666);
        shmaddr = shmat(shmid, (void *)0, 0666);
        if(shmaddr < 0){
            printf("shmat attch is failed : ");
            exit(-1);
        }
    }
    shmat(shmid, (void *)0, 0666);
    chatInfo = (CHAT_INFO *)shmaddr;
    printf("------------ Chat Message -------------\n");
    while(1){
        printf("[%s]%ld: %s\n",
               chatInfo->userID,
               chatInfo->messageTime,
               chatInfo->message);
        if(!strcmp(chatInfo->message, "/exit\n")){
            print("%s is out\n", chatInfo->userID);
            break;
        }
    }
    return 0;
}
