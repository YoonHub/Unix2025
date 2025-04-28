#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 1024

int evaluate_expression(const char *expr) {
    int num1, num2;
    char op;
    if (sscanf(expr, "%d %c %d", &num1, &op, &num2) == 3) {
        switch (op) {
            case '+': return num1 + num2;
            case '-': return num1 - num2;
            case '*': return num1 * num2;
            case '/': return (num2 != 0) ? num1 / num2 : 0;
        }
    }
    return 0;
}

int main() {
    void *shared_memory = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        char *math_problems[] = {
            "2 + 3", "3 + 4", "25 * 6", "4 - 3", "10 / 5", NULL
        };

        char *ptr = (char *)shared_memory;
        ptr[0] = '\0';

        int i;
        for (i = 0; math_problems[i] != NULL; i++) {
            strcat(ptr, math_problems[i]);
            strcat(ptr, "\n");
        }

        exit(0);
    } else {
        wait(NULL);

        char *ptr = (char *)shared_memory;
        char *line = strtok(ptr, "\n");

        while (line != NULL) {
            printf("%d\n", evaluate_expression(line));
            line = strtok(NULL, "\n");
        }

        munmap(shared_memory, SIZE);
    }

    return 0;
}
