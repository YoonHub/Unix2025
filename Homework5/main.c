#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <pthread.h>

#include <termios.h>

#include <time.h>

#include <string.h>

#include <sys/ioctl.h>



#define WIDTH 80

#define HEIGHT 24

#define DELAY 20000



typedef struct {

    int row, col;

} Plane;



typedef struct {

    int row;

} Bullet;



typedef struct {

    int row;

} Target;



Plane plane;

Target target;

int game_over = 0;

pthread_mutex_t screen_lock;



void set_terminal_mode() {

    struct termios term;

    tcgetattr(STDIN_FILENO, &term);

    term.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &term);

}



int input_ready() {

    int bytes;

    ioctl(STDIN_FILENO, FIONREAD, &bytes);

    return bytes > 0;

}



int fetch_key() {

    char buf[3];

    read(STDIN_FILENO, buf, 3);



    if (buf[0] == 27 && buf[1] == 91) {



        switch (buf[2]) {

        case 'A':

            return 'U';

        case 'B':

            return 'D';

        case 'C':

            return 'R';

        case 'D':

            return 'L';

        }



    }

    else if (buf[0] == ' ') {

        return 'F';

    }



    return 0;

}



void show_target() {

    pthread_mutex_lock(&screen_lock);



    printf("\033[%d;%dHX", target.row + 1, WIDTH);

    fflush(stdout);



    pthread_mutex_unlock(&screen_lock);

}



void render_plane() {

    pthread_mutex_lock(&screen_lock);



    printf("\033[%d;%dHA", plane.row + 1, plane.col + 1);

    fflush(stdout);



    pthread_mutex_unlock(&screen_lock);

}



void clear_plane() {

    pthread_mutex_lock(&screen_lock);



    printf("\033[%d;%dH ", plane.row + 1, plane.col + 1);



    pthread_mutex_unlock(&screen_lock);

}



void gameover_message() {

    pthread_mutex_lock(&screen_lock);



    printf("\033[%d;%dHGame Over", HEIGHT / 2, WIDTH / 2 - 5);

    fflush(stdout);



    pthread_mutex_unlock(&screen_lock);

}



void* fire_bullet(void* arg) {



    Bullet* bullet = (Bullet*)arg;

    int r = bullet->row;

    int c = 1;

    free(bullet);



    while (c < WIDTH) {

        pthread_mutex_lock(&screen_lock);



        printf("\033[%d;%dH>", r + 1, c + 1);

        fflush(stdout);



        pthread_mutex_unlock(&screen_lock);



        usleep(DELAY);



        pthread_mutex_lock(&screen_lock);



        printf("\033[%d;%dH ", r + 1, c + 1);



        pthread_mutex_unlock(&screen_lock);



        if (r == target.row && c == WIDTH - 1) {

            game_over = 1;

            break;

        }



        c++;

    }



    return NULL;

}



void handle_input(int key) {



    clear_plane();



    if (key == 'U' && plane.row > 0) {

        plane.row--;

    }

    else if (key == 'D' && plane.row < HEIGHT - 1) {

        plane.row++;

    }

    else if (key == 'L' && plane.col > 0) {

        plane.col--;

    }

    else if (key == 'R' && plane.col < WIDTH - 2) {

        plane.col++;

    }

    else if (key == 'F') {

        Bullet* b = malloc(sizeof(Bullet));

        b->row = plane.row;



        pthread_t tid;

        pthread_create(&tid, NULL, fire_bullet, b);

        pthread_detach(tid);

    }



    render_plane();

}



int main() {

    system("clear");

    set_terminal_mode();

    pthread_mutex_init(&screen_lock, NULL);

    srand(time(NULL));



    plane.row = HEIGHT / 2;

    plane.col = 0;



    target.row = rand() % HEIGHT;

    show_target();

    render_plane();

    while (!game_over) {



        if (input_ready()) {

            int key = fetch_key();

            handle_input(key);

        }



        usleep(10000);

    }



    gameover_message();

    pthread_mutex_destroy(&screen_lock);





    return 0;

}
