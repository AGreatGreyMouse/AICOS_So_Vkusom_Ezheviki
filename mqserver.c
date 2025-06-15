#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define MAX_SIZE 1024

int main() {
    const char *queue_name = "/queue";

    struct mq_attr attr = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_msgsize = MAX_SIZE,
        .mq_curmsgs = 0
    };

    mqd_t mq = mq_open(queue_name, O_RDONLY | O_CREAT, 0644, &attr);
    if (mq == (mqd_t) -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_SIZE + 1];
    ssize_t bytes_read;

    printf("Я сказала стартуем\n");

    while (1) {
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        if (bytes_read == -1) {
            perror("mq_receive");
            mq_close(mq);
            mq_unlink(queue_name);
            exit(EXIT_FAILURE);
        }
        buffer[bytes_read] = '\0';

        if (strcmp(buffer, "QUIT") == 0) {
            printf("Всем пака я пакидываю группу\n");
            break;
        }

        printf("Гуманои обнаружен: %s\n", buffer);
    }

    mq_close(mq);
    mq_unlink(queue_name);
    return 0;
}
