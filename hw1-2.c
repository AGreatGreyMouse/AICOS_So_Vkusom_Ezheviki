#include <stdio.h>
#include <stdlib.h>  

int main() {
    int N, i;

    printf("хаумач мексиканцев в троянском коне: ");
    scanf("%d", &N);

    int *arr = (int *)malloc(N * sizeof(int));
    if (arr == NULL) {
        printf("память не выделилась\n");
        return 1;  // выходим с позором
    }

    printf("Введи %d <- столько интов:\n", N);
    for (i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    for (i = 0; i < N / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[N - 1 - i];
        arr[N - 1 - i] = temp;
    }

    printf("австралийский массив, получите-распишитесь:\n");
    for (i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
