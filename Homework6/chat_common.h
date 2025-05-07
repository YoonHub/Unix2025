#ifndef CHAT_COMMON_H
#define CHAT_COMMON_H

#include <time.h>

#define MAX_USERS 5
#define MAX_MSGS 100
#define MAX_NICKNAME 32
#define MAX_MSG_LEN 256

#define SHM_NAME "/chat_shm"
#define SEM_MUTEX_NAME "/chat_mutex"

typedef struct {
    char nickname[MAX_NICKNAME];
    int color_id;
    int active; // 1: 접속, 0: 없음
} UserInfo;

typedef struct {
    char nickname[MAX_NICKNAME];
    char message[MAX_MSG_LEN];
    time_t timestamp;
    int color_id;
} ChatMessage;

typedef struct {
    UserInfo users[MAX_USERS];
    ChatMessage messages[MAX_MSGS];
    int msg_count;
} ChatMemory;

#endif
