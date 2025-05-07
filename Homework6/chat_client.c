#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <ncurses.h>
#include <sys/mman.h>
#include <time.h>
#include "../include/chat_common.h"

ChatMemory *chat_mem;
sem_t *mutex;
char my_nickname[MAX_NICKNAME];
int my_color = 1;

WINDOW *chatwin, *userwin;

void *receive_loop(void *arg) {
    int last_count = 0;
    while (1) {
        sem_wait(mutex);
        for (int i = last_count; i < chat_mem->msg_count; i++) {
            ChatMessage *msg = &chat_mem->messages[i];
            wattron(chatwin, COLOR_PAIR(msg->color_id));
            wprintw(chatwin, "[%s] %s\n", msg->nickname, msg->message);
            wattroff(chatwin, COLOR_PAIR(msg->color_id));
        }
        last_count = chat_mem->msg_count;
        sem_post(mutex);
        wrefresh(chatwin);
        usleep(300000);
    }
    return NULL;
}

void *user_list_loop(void *arg) {
    while (1) {
        sem_wait(mutex);
        werase(userwin);
        box(userwin, 0, 0);
        mvwprintw(userwin, 1, 1, "USERS:");
        int line = 2;
        for (int i = 0; i < MAX_USERS; i++) {
            if (chat_mem->users[i].active) {
                wattron(userwin, COLOR_PAIR(chat_mem->users[i].color_id));
                mvwprintw(userwin, line++, 1, "- %s", chat_mem->users[i].nickname);
                wattroff(userwin, COLOR_PAIR(chat_mem->users[i].color_id));
            }
        }
        sem_post(mutex);
        wrefresh(userwin);
        usleep(500000);
    }
    return NULL;
}

int main() {
    initscr();
    noecho();
    cbreak();
    start_color();
    for (int i = 1; i <= MAX_USERS; i++)
        init_pair(i, i % 7 + 1, COLOR_BLACK);

    printw("닉네임을 입력하세요: ");
    echo(); getnstr(my_nickname, MAX_NICKNAME); noecho();
    clear();

    // 창 나누기
    int height, width;
    getmaxyx(stdscr, height, width);
    chatwin = newwin(height, width - 20, 0, 0);
    userwin = newwin(height, 20, 0, width - 20);
    scrollok(chatwin, TRUE);
    box(userwin, 0, 0);
    wrefresh(chatwin);
    wrefresh(userwin);

    // 공유 메모리, 세마포어 연결
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    chat_mem = mmap(NULL, sizeof(ChatMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    mutex = sem_open(SEM_MUTEX_NAME, 0);

    // 사용자 등록
    sem_wait(mutex);
    for (int i = 0; i < MAX_USERS; i++) {
        if (!chat_mem->users[i].active) {
            chat_mem->users[i].active = 1;
            strncpy(chat_mem->users[i].nickname, my_nickname, MAX_NICKNAME);
            chat_mem->users[i].color_id = my_color = i + 1;
            break;
        }
    }
    sem_post(mutex);

    pthread_t recv_thread, user_thread;
    pthread_create(&recv_thread, NULL, receive_loop, NULL);
    pthread_create(&user_thread, NULL, user_list_loop, NULL);

    // 메시지 입력 루프
    char msg[MAX_MSG_LEN];
    while (1) {
        mvwgetnstr(chatwin, getcury(chatwin), 0, msg, MAX_MSG_LEN);

        if (strncmp(msg, "/clear", 6) == 0) {
            werase(chatwin);
            wrefresh(chatwin);
            continue;
        }

        if (strncmp(msg, "/exit", 5) == 0) {
            sem_wait(mutex);
            for (int i = 0; i < MAX_USERS; i++) {
                if (chat_mem->users[i].active && strcmp(chat_mem->users[i].nickname, my_nickname) == 0) {
                    chat_mem->users[i].active = 0;
                    break;
                }
            }
            sem_post(mutex);
            break;
        }

        sem_wait(mutex);
        ChatMessage *m = &chat_mem->messages[chat_mem->msg_count++];
        strncpy(m->nickname, my_nickname, MAX_NICKNAME);
        strncpy(m->message, msg, MAX_MSG_LEN);
        m->color_id = my_color;
        m->timestamp = time(NULL);
        if (chat_mem->msg_count >= MAX_MSGS) chat_mem->msg_count = 0;
        sem_post(mutex);
    }

    endwin();
    return 0;
}
