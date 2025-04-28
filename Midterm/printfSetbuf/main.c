#include <stdio.h>
#include <stdlib.h>

int main()
{
    char buf[BUFSIZ];

    setbuf(stdout, buf);
    printf("Hello ");
    sleep(2);
    printf("World");
    printf("\n");
    sleep(2);
    setbuf(stdout, NULL);
    printf("PNU ");
    sleep(2);
    printf("CSE");
    sleep(2);
    printf("\n");
    sleep(2);
    return 0;
}
