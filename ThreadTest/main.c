#include <stdio.h>


extern char __executable_start;

extern char __etext;


int main(void)

{

  printf("0x%lx\n", (unsigned long)&__executable_start);

  printf("0x%lx\n", (unsigned long)&__etext);


  int *i;



  i = (int *)&__executable_start;

  //i = &__executable_start;



  *i = 1000;



  for(;;);


  return 0;

}
