#include <stdio.h>

#include <sys/mman.h>

#include <sys/types.h>

#include <unistd.h>

#include <string.h>


int main() {

    size_t length = 4096; // 공유 메모리 크기

    void *shared_memory = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);


    if (shared_memory == MAP_FAILED) {

        perror("mmap failed");

        return 1;

    }


    pid_t pid = fork();


    if (pid == -1) {

        perror("fork failed");

        munmap(shared_memory, length);

        return 1;

    } else if (pid == 0) {

        // 자식 프로세스: 데이터 쓰기

        strcpy((char *)shared_memory, "Hello from child!");

        printf("Child wrote to shared memory.\n");

    } else {

        // 부모 프로세스: 데이터 읽기

        wait(NULL); // 자식 프로세스가 쓰기를 완료할 때까지 대기

        printf("Parent read from shared memory: %s\n", (char *)shared_memory);

    }


    // 메모리 매핑 해제

    munmap(shared_memory, length);


    return 0;

}
