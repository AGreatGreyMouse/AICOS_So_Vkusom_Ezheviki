#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "%s", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        int fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd < 0) {
            perror("");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT_FILENO) < 0) {
            perror("");
            exit(EXIT_FAILURE);
        }
        close(fd);
        execlp(argv[1], argv[1], NULL);
        perror("");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }

    return 0;
}
