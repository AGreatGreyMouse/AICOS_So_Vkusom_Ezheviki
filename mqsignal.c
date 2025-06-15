#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <signal.h>
#include <unistd.h>

#define MAX_SIZE 1024

const char *queue_name = "/queue";
mqd_t mq;

void cleanup(int signum) {
    printf("\nГей-радар засёк сигнал %d, уже разбираемся\n", signum);
    mq_close(mq);
    mq_unlink(queue_name);
    exit(EXIT_SUCCESS);
}

int main() {
    struct mq_attr attr = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_msgsize = MAX_SIZE,
        .mq_curmsgs = 0
    };

    signal(SIGINT, cleanup);

    mq = mq_open(queue_name, O_RDONLY | O_CREAT, 0644, &attr);
    if (mq == (mqd_t) -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_SIZE + 1];
    ssize_t bytes_read;

    printf("Чего тебе хозяйка надо ?(CTRL+C - с вещами на выход)\n");

    while (1) {
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        if (bytes_read == -1) {
            perror("mq_receive");
            cleanup(SIGINT);
        }
        buffer[bytes_read] = '\0';

        if (strcmp(buffer, "QUIT") == 0) {
            printf("Чемодан, вокзал, наавыход\n");
            break;
        }

        printf("зачисление рыбов на лицевой счёт: %s\n", buffer);
    }

    cleanup(0);
    return 0;
}
