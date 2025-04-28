#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char buf[BUFSIZ];
    int i, j;
    setbuf(stdin, buf);
    scanf("%d, %d", &i, &j);
    for(int i = 0; buf[i] != '\n'; i++)
        putchar((buf[i]));

    putchar('\n');
    return 0;
}
