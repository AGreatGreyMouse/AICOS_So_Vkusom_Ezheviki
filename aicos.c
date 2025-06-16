#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>

#define FUNC_COUNT 4

double f1(double x) {
    return -5 * pow(x, 3) + 9 * pow(x, 2) - 5 * x + 2;
}

double f2(double x) {
    return sin(8 * x) * (-7) - 9;
}

double f3(double x) {
    return pow(-7, x) - 1;
}

double f4(double x) {
    return 1.0 / (1 + exp(-6 * x));
}

double f0(double a, double b, double c, double d) {
    double max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    if (d > max) max = d;
    return max;
}

double (*funcs[FUNC_COUNT])(double) = {f1, f2, f3, f4};

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "лажа!");
        return 1;
    }

    double start = atof(argv[1]);
    double end = atof(argv[2]);
    double step = atof(argv[3]);

    int pipes[FUNC_COUNT][2];
    pid_t children[FUNC_COUNT];

    FILE *output = fopen("output.csv", "w");
    if (!output) {
        perror("kuda vivodit' to? na sber?");
        return 1;
    }
    dup2(fileno(output), STDOUT_FILENO);
    fprintf(stdout, "x,f(x)\n"); 

    for (int i = 0; i < FUNC_COUNT; i++) {
        if (pipe(pipes[i]) < 0) {
            perror("пипе");
            return 1;
        }
        children[i] = fork();
        if (children[i] < 0) {
            perror("вилка");
            return 1;
        }
        if (children[i] == 0) {
            close(pipes[i][0]); 
            
            for (double x = start; x <= end; x += step) {
                double val = funcs[i](x);
                write(pipes[i][1], &x, sizeof(double));
                write(pipes[i][1], &val, sizeof(double));
            }
            close(pipes[i][1]);
            exit(0);
        }
        close(pipes[i][1]); 
    }

    for (double x = start; x <= end; x += step) {
        double vals[FUNC_COUNT];
        for (int i = 0; i < FUNC_COUNT; i++) {
            double rx, ry;
            read(pipes[i][0], &rx, sizeof(double));
            read(pipes[i][0], &ry, sizeof(double));
            vals[i] = ry;
        }
        double fx = f0(vals[0], vals[1], vals[2], vals[3]);
        printf("%.6f,%.6f\n", x, fx);
    }

    for (int i = 0; i < FUNC_COUNT; i++) {
        close(pipes[i][0]);
        waitpid(children[i], NULL, 0);
    }

    fclose(output);
    return 0;
}
