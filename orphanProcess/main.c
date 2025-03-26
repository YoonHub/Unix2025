#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid = fork();
    if(pid > 0){
        printf("In Parent Processing");
    }
    else if(pid == 0){
        printf("In Child Process");
    }
    return 0;
}
