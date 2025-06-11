#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MIN_SIZE 16

int* array;
int global_sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int start;
    int end;
} ThreadArgs;

void* calculate_partial_sum(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int partial_sum = 0;

    for (int i = args->start; i < args->end; i++) {
        partial_sum += array[i];
    }
    pthread_mutex_lock(&mutex);
    global_sum += partial_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    int N;
    pthread_t threads[4];
    ThreadArgs thread_args[4];

    srand(time(NULL));

    printf("vvd3di puffdidi vnutrivenno N (must be >= 16): ");
    scanf("%d", &N);

    if (N < MIN_SIZE) {
        printf("N must be at list! (not factorial butt exclamation mark II) 4^2  %d\n", MIN_SIZE);
        return 1;
    }

    array = (int*)malloc(N * sizeof(int));
    if (array == NULL) {
        perror("memory allocation failed: u.r dory from finding nemo");
        return 1;
    }

    printf("na te array:\n");
    for (int i = 0; i < N; i++) {
        array[i] = rand() % 100;
        printf("%d ", array[i]);
    }
    printf("\n");


    int base_size = N / 4;
    int remainder = N % 4;
    int start = 0;
    for (int i = 0; i < 4; i++) {
        int end = start + base_size + (i < remainder ? 1 : 0);
        
        thread_args[i].start = start;
        thread_args[i].end = end;
        
        pthread_create(&threads[i], NULL, calculate_partial_sum, &thread_args[i]);
        
        start = end;
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    printf(" sum: %d\n", global_sum);

    free(array);
    pthread_mutex_destroy(&mutex);

    return 0;
}
