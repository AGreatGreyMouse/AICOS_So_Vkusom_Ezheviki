#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_SIGNALS 64

volatile sig_atomic_t quit_signal_count = 0;
int quit_signal = 0;

void handler(int sig) {
    if (sig == quit_signal) {
        quit_signal_count++;
        printf("[Caught: %s] (%d/%d)\n", strsignal(sig), quit_signal_count, 3);
    } else {
        printf("[Caught: %s]\n", strsignal(sig));
    }
}

int str_to_signal(const char *name) {
    struct {
        const char *name;
        int number;
    } signals[] = {
        {"HUP", SIGHUP}, {"INT", SIGINT}, {"QUIT", SIGQUIT}, {"ILL", SIGILL},
        {"ABRT", SIGABRT}, {"FPE", SIGFPE}, {"KILL", SIGKILL}, {"SEGV", SIGSEGV},
        {"PIPE", SIGPIPE}, {"ALRM", SIGALRM}, {"TERM", SIGTERM}, {"USR1", SIGUSR1},
        {"USR2", SIGUSR2}, {"CHLD", SIGCHLD}, {"CONT", SIGCONT}, {"STOP", SIGSTOP},
        {"TSTP", SIGTSTP}, {"TTIN", SIGTTIN}, {"TTOU", SIGTTOU}, {"BUS", SIGBUS},
        {"PROF", SIGPROF}, {"SYS", SIGSYS}, {"TRAP", SIGTRAP},
        {"URG", SIGURG}, {"VTALRM", SIGVTALRM}, {"XCPU", SIGXCPU}, {"XFSZ", SIGXFSZ},
        {NULL, 0}
    };

    for (int i = 0; signals[i].name != NULL; i++) {
        if (strcmp(name, signals[i].name) == 0) {
            return signals[i].number;
        }
    }

    return -1;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "%s сигнал квир загнулся\n", argv[0]);
        return 1;
    }

    int timeout = atoi(argv[1]);
    if (timeout <= 0) {
        fprintf(stderr, "таймаут огузок\n");
        return 1;
    }

    quit_signal = str_to_signal(argv[2]);
    if (quit_signal == -1) {
        fprintf(stderr, "неизвестный науке зверь: %s\n", argv[2]);
        return 1;
    }

    for (int i = 3; i < argc; i++) {
        int sig = str_to_signal(argv[i]);
        if (sig == -1) {
            fprintf(stderr, "allow kto eto zvonit: %s\n", argv[i]);
            return 1;
        }

        if (signal(sig, handler) == SIG_ERR) {
            perror("signal");
            return 1;
        }
    }

    int counter = 0;
    while (quit_signal_count < 3) {
        sleep(timeout);
        printf("%d: PID(id i) = %d\n", counter++, getpid());
    }

    printf(" %s threesome signal. Exiting gracefully \n", strsignal(quit_signal));
    return 0;
}
