#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int _balance = 0;
pthread_mutex_t _lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t _newDeposit = PTHREAD_COND_INITIALIZER;

void* DepositThread(void *arg);
void* WithdrawThread(void *arg);

int main()
{
    pthread_t _deposit, _withdraw;

    pthread_create(&_deposit, NULL, DepositThread, NULL);
    pthread_create(&_withdraw, NULL, WithdrawThread, NULL);

    pthread_join(_deposit, NULL);
    pthread_join(_withdraw, NULL);


    return 0;
}


void* DepositThread(void *arg){
    while(1){

        int _amount = rand() % 10 + 1;
        pthread_mutex_lock(&_lock);

        _balance += _amount;
        printf("Deposit amount : %d | balance = %d\n", _amount, _balance);

        pthread_cond_signal(&_newDeposit);
        pthread_mutex_unlock(&_lock);

        sleep(1);
    }
    return NULL;
}

void* WithdrawThread(void* arg){

    while(1){
        int _amount = rand() % 10 + 1;
        pthread_mutex_lock(&_lock);

        while(_balance < _amount){
            printf("Withdraw : Balance isn't enough..\n");
            pthread_cond_wait(&_newDeposit, &_lock);
        }

        _balance -= _amount;
        printf("Withdraw : amount = %d | balance = %d\n", _amount, _balance);

        pthread_mutex_unlock(&_lock);

        sleep(1);
    }

    return NULL;
}

