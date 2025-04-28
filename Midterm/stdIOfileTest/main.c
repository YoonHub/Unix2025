#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

int getch() {
    int ch;
    // struct to hold the terminal settings
    struct termios old_settings, new_settings;
    // take default setting in old_settings
    tcgetattr(STDIN_FILENO, &old_settings);
    // make of copy of it (Read my previous blog to know
    // more about how to copy struct)
    new_settings = old_settings;
    // change the settings for by disabling ECHO mode
    // read man page of termios.h for more settings info
    new_settings.c_lflag &= ~(ICANON | ECHO); // bit operator
    // apply these new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    // now take the input in this mode
    ch = getchar();
    // reset back to default settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
    return ch;
}

int main(void) {
    char password[100];
    int i = 0;
    int ch;

    printf("Enter password: ");
    while ((ch = getch()) != '\n') {
        if (ch == 127 || ch == 8) { // handle backspace
            if (i != 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            // echo the '*' to get feel of taking password
            printf("*");
        }
    }
    password[i] = '\0';

    printf("\nYou entered password: %s\n", password);

    return 0;
}
