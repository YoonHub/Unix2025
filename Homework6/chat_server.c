#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>
#include "../include/chat_common.h"

int main() {
    // 공유 메모리 생성
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(ChatMemory));
    ChatMemory *chat_mem = mmap(NULL, sizeof(ChatMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // 세마포어 생성
    sem_t *mutex = sem_open(SEM_MUTEX_NAME, O_CREAT, 0666, 1);

    // 구조체 초기화
    sem_wait(mutex);
    memset(chat_mem, 0, sizeof(ChatMemory));
    sem_post(mutex);

    printf("📡 Chat server started.\n");

    while (1) {
        sleep(2);
        system("clear");
        printf("🧑‍🤝‍🧑 접속자 목록:\n");

        sem_wait(mutex);
        for (int i = 0; i < MAX_USERS; i++) {
            if (chat_mem->users[i].active) {
                printf(" - %s (color %d)\n", chat_mem->users[i].nickname, chat_mem->users[i].color_id);
            }
        }
        sem_post(mutex);
    }

    return 0;
}
