#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <mqueue.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

char msgQName[100] = { 0, };
char semSend[100] = { 0, };
char semRecv[100] = { 0, };

void server_function()
{
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;

    char result[100];
    mqd_t mfd;
    sem_t *sem_c2s;
    sem_t *sem_s2c;

    mq_unlink(msgQName);
    mfd = mq_open(msgQName, O_RDWR | O_CREAT, 0644, &attr);
    if(mfd == -1)
    {
        perror("Server mq open error\n");
        exit(0);
    }

    sem_c2s = sem_open(semSend, O_CREAT, 0644, 0);
    sem_s2c = sem_open(semRecv, O_CREAT, 0644, 0);
    if(sem_c2s == SEM_FAILED || sem_s2c == SEM_FAILED)
    {
        perror("sem_open error (server)");
        exit(1);
    }

    int j = 1;
    while(j < 11)
    {
        sem_wait(sem_c2s);

        if(mq_receive(mfd, result, attr.mq_msgsize, NULL) == -1)
        {
            perror("Server Receive error\n");
            exit(-1);
        }

        printf("[Recv] %s\n", result);
        fflush(stdout);

        sem_post(sem_s2c);
        j++;
    }

    mq_close(mfd);
    sem_close(sem_c2s);
    sem_close(sem_s2c);
    sem_unlink(semSend);
    sem_unlink(semRecv);
}

void client_function()
{
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;

    char buf[100] = { 0, };
    mqd_t mfd;
    sem_t *sem_c2s;
    sem_t *sem_s2c;

    mfd = mq_open(msgQName, O_WRONLY, 0644, &attr);
    if(mfd == -1)
    {
        perror("Client mq open error\n");
        exit(1);
    }

    sem_c2s = sem_open(semSend, 0);
    sem_s2c = sem_open(semRecv, 0);
    if(sem_c2s == SEM_FAILED || sem_s2c == SEM_FAILED)
    {
        perror("sem_open error (client)");
        exit(1);
    }

    int i = 1;
    while(i < 11)
    {
        sprintf(buf, "Msg %d", i);
        if(mq_send(mfd, buf, attr.mq_msgsize, 1) == -1)
        {
            perror("Client Send error\n");
            exit(-1);
        }

        printf("[Send] %s\n", buf);
        fflush(stdout);

        sem_post(sem_c2s);
        sem_wait(sem_s2c);
        i++;
    }

    mq_close(mfd);
    sem_close(sem_c2s);
    sem_close(sem_s2c);
}

int main(int argc, char* argv[])
{
    char name[L_tmpnam];
    char *ptr = tmpnam(name);
    sprintf(msgQName, "/%s", ptr + 5);
    sprintf(semSend, "/s1_%s", ptr + 5);
    sprintf(semRecv, "/s2_%s", ptr + 5);

    int32_t pid = fork();

    if(pid > 0)
    {
        server_function();
    }
    else if(pid == 0)
    {
        client_function();
    }
    else if(pid == -1)
    {
        perror("fork error : ");
        exit(0);
    }

    return 0;
}
