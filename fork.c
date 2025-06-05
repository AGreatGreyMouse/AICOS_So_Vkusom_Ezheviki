#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        printf("Privet ot detey donbassa 1 - PID: %d\n", getpid());

        pid_t pid2 = fork();
        if (pid2 < 0) {
            perror("");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            printf("Privet ot detey donbassa 2 - PID: %d\n", getpid());
            exit(EXIT_SUCCESS);
        } else {
            wait(NULL);
            exit(EXIT_SUCCESS);
        }
    } else {
        wait(NULL);
        printf("Privet ot roditeley donbassa - PID: %d\n", getpid());
    }

    return 0;
}
