#ifndef CHATSHM_INCLUDED
#define CHATSHM_INCLUDED
typedef struct chatInfo{
    char userID[20];
    long messageTime;
    char message[40];
} CHAT_INFO;
#endif // CHATSHM_INCLUDED
