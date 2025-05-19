#include <stdio.h>

#include <stdlib.h>

#include <string.h>


static char letter[2];


char

*letter_grade(float number_grade)

{


  if      (number_grade >= 90.0) strncpy(letter, "A", 1);

  else if (number_grade >= 80.0) strncpy(letter, "B", 1);

  else if (number_grade >= 70.0) strncpy(letter, "C", 1);

  else if (number_grade >= 60.0) strncpy(letter, "D", 1);

  else                           strncpy(letter, "F", 1);

  letter[1] = '\0';


  return letter;

}


int

main(void)

{

  printf("Exam 1: %s\n", letter_grade(85.5));


  return 0;

}
