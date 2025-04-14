#include <stdio.h>
#include <stdlib.h>

int main()
{
    char buf[BUFSIZ];

    //print HelloUnix\n at once after 3seconds
    setbuf(stdout, buf);
    printf("Hello"); fflush(stdout); sleep(1);
    printf("UNIX");sleep(1);
    printf("\n");sleep(1);

    //print Hello, Unix, \n every 1 second
    setbuf(stdout, NULL);
    printf("Hello"); sleep(1);
    printf("UNIX");sleep(1);
    printf("\n");sleep(1);


    return 0;
}
