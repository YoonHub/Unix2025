#include <stdio.h>

#include <stdlib.h>


static int i[1000];       /* uninitialized static storage (BSS) */

static int j = 2;         /* initialized static storage (DATA) */

static int k = 3;         /* read-only initialized static storage  (RODATA) */

const char l[] = "linux";


extern int _end;          /* end of BSS segment */

extern int _etext;        /* end of code segment (text) */

extern int _start;        /* entry point */

extern int _edata;        /* end of initialized data segment */

extern int __bss_start;   /* start of bss segment */

extern int __data_start;  /* start of bss segment */



extern char **environ;    /* pointer to environment */


int main (int argc, const char *argv[]) {


  int *m; /* local pointer (on stack) */


  printf ("0x%lx : environ[0]   \n", environ[0]);

  printf ("0x%lx : argv[0]      \n", argv[0]);

  printf ("0x%lx : &m           \n", &m);


  m = malloc (100);

  printf ("0x%lx : m            \n", m);

  printf ("0x%lx : &_end        \n", &_end);

  printf ("0x%lx : i            \n", i);

  printf ("0x%lx : &__bss_start \n", &__bss_start);

  printf ("0x%lx : &_edata      \n", &_edata);

  printf ("0x%lx : &k           \n", &k);

  printf ("0x%lx : &j           \n", &j);

  printf ("0x%lx : &__data_start\n", &__data_start);

  printf ("0x%lx : &l           \n", &l);

  printf ("0x%lx : &_etext      \n", &_etext);

  printf ("0x%lx : main         \n", main);

  printf ("0x%lx : &_start      \n", &_start);


  return 0;

}
