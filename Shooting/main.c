#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main()

{

    int raw=10, col=10;		// Coordinates Variables

    initscr();

    keypad(stdscr,TRUE);

    while(1)

    {

        int input = getch();	// Input

        clear();
        curs_set(0);

        switch( input )

        {

            case KEY_UP:    mvprintw( --raw, col, "A" ); continue;

            case KEY_DOWN:  mvprintw( ++raw, col, "A" ); continue;

            case KEY_LEFT:  mvprintw( raw, --col, "A" ); continue;

            case KEY_RIGHT: mvprintw( raw, ++col, "A" ); continue;

            case ' ':{
                int x = raw, y = col + 1, prevX = raw, prevY = col;
                mvprintw(x, col, "A");
                move(x, col+1);
                for(int i = col + 1; i < 76; i++){
                    move(x, col + 1);
                    for(int k = col + 1; k < i; k++) printw(">");
                    move(x, col + 1);
                    for(int k = col + 1; k < i-1; k++) printw(" ");
                    refresh();
                    usleep(25 * 1000);
                }
                printw("Dead!!");
            }

        }

        if( input == 'q' ) break;	// Escape Condition

    }

    endwin();

}
