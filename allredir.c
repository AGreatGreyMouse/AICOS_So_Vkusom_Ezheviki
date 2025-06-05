#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "%s", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        int fd_in = open(argv[2], O_RDONLY);
        if (fd_in < 0) {
            perror("");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd_in, STDIN_FILENO) < 0) {
            perror("");
            exit(EXIT_FAILURE);
        }
        close(fd_in);

        int fd_out = open(argv[3], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd_out < 0) {
            perror("");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd_out, STDOUT_FILENO) < 0) {
            perror("");
            exit(EXIT_FAILURE);
        }
        close(fd_out);

        execlp(argv[1], argv[1], NULL);
        perror("");
        exit(EXIT_FAILURE);
    } else {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            printf("%d", WEXITSTATUS(status));
        } else {
            printf("pobeda\n");
        }
    }

    return 0;
}
