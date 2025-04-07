#include <pthread.h>

#include <ncurses.h>

#include <unistd.h>


pthread_mutex_t mlock; // mutex를 선언


void *abc() {  // thread 함수

    int num = 0;

    while(1) {

       for (int y = 0; y<4; y++) { // (10,20)에서 로딩(#) 증가시키기

            pthread_mutex_lock(&mlock);  // mutex를 통해 동시성 에러 방지

            move(10,20);

            for (int x = 0; x<=y; x++) printw("#");

            refresh();

            pthread_mutex_unlock(&mlock);

            usleep(100 * 1000);

        }


        for (int y = 3; y>=0; y--) {  // (10,20)에서 로딩(#) 감소시키기

            pthread_mutex_lock(&mlock);

            move(10,20);

            for (int x = 0; x<=y; x++) printw("#");

            for (int x = y + 1; x < 4; x++) printw(" "); // 남아있는 뒷자리 없애주기

            refresh();

            pthread_mutex_unlock(&mlock);

            usleep(100 * 1000);

        }

    }

}


int main()

{



    initscr();


    clear();


    pthread_t tid;

    pthread_create(&tid, NULL, abc, NULL); // thread 생성

    int num = 0;

    while(1) {  // 업카운팅

        pthread_mutex_lock(&mlock);

        mvprintw(10,10,"%d", num); // move + printw : (10,10) 떨어진 곳에 출력

        refresh();

        pthread_mutex_unlock(&mlock);

        num++;

    }


    pthread_join(tid, NULL);


    getch();

    endwin();

    return 0;


}
