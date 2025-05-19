

#include <pthread.h>

#include <stdlib.h>

#include <stdio.h>

#include <string.h>


static void *thread_entry(void *arg);

char *letter_grade(float number_grade);


static pthread_key_t   grader_key;

static pthread_once_t  grader_once = PTHREAD_ONCE_INIT;


static void

*thread_entry(void *arg)

{

  float number_grade = *(float *)arg;

  //void  *result = (void *)letter_grade(number_grade);

  //return result;


  printf("Thread: %s\n", letter_grade(number_grade));

  return NULL;

}


static

void free_memory(void *buffer)

{

  free(buffer);

  printf("free memory at [%p] is called...\n", buffer);

}


static

void create_key(void)

{

  // By default, pthread_key_create(&grader_key, NULL);

  pthread_key_create(&grader_key, free_memory);

}



char

*letter_grade(float number_grade)

{

  char *letter;


  // The first caller must create the key for the thread-specific data

  pthread_once(&grader_once, create_key);


  // Get the memory for the key

  letter = pthread_getspecific(grader_key);


  // If this is the first call from this thread then the memory

  // will be NULL and, hence, must be allocated (and saved)

  if (letter == NULL)

    {

      letter = malloc(2);

      pthread_setspecific(grader_key, letter);

      printf("pthread_setspecific data at[%p] ... is called!!\n", letter);

    }


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

  char        *letter_main;

  float       number_helper;

  pthread_t   exam_helper;


  // Calculate one letter grade in the main thread

  letter_main = letter_grade(85.5);


  // Calculate (and print) another letter grade in the helper thread

  number_helper = 48.0;

  pthread_create(&exam_helper, NULL, thread_entry, &number_helper);


  // Terminate the helper thread

  pthread_join(exam_helper, NULL);


  // Now that the helper thread has terminated, print the

  // grade that was calculated in the main thread

  printf("Main: %s\n", letter_main);


  return 0;

}


