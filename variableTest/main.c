#include <stdio.h>


int main()

{

    int i;

    register int j;

    volatile int k;


    i = 10;

    j = 20;

    k = 30;


    printf("i = %d\n", i);

    printf("j = %d\n", j);

    printf("k = %d\n", k);


    return 0;

}
