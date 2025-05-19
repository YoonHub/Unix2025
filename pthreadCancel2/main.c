

#define _MULTI_THREADED

#include <pthread.h>

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#define checkResults(string, val)
{

 if (val) {

   printf("Failed with %d at %s", val, string);

   exit(1);

 }

}



void *theThread(void *parm)

{

   printf("Thread: Entered\n");

   while (1) {

      printf("Thread: Looping or long running request\n");

      //pthread_testcancel();

      sleep(10);

   }

   return NULL;

}



int main(int argc, char **argv)

{

  pthread_t             thread;

  int                   rc=0;

  void                 *status;



  printf("Enter Testcase - %s\n", argv[0]);



  printf("Create/start a thread\n");

  rc = pthread_create(&thread, NULL, theThread, NULL);

  checkResults("pthread_create()\n", rc);



  printf("Wait a bit until we 'realize' the thread needs to be canceled\n");

  sleep(3);

  rc = pthread_cancel(thread);

  checkResults("pthread_cancel()\n", rc);



  printf("Wait for the thread to complete, and release its resources\n");

  rc = pthread_join(thread, &status);

  checkResults("pthread_join()\n", rc);



  printf("Thread status indicates it was canceled\n");

  if (status != PTHREAD_CANCELED) {

     printf("Unexpected thread status\n");

  }



  printf("Main completed\n");

  return 0;

}
