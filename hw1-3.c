#include <stdio.h>
#include <stdlib.h>

// динамически аллоцируем двумверный массив
int** allocate_matrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) return NULL;

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) return NULL;
    }

    return matrix;
}

// бомбически деаллоцируем двумверный массив
void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix); // #freedurov
}

int main() {
    int N, M;

    printf("сколько строк: ");
    scanf("%d", &N);
    printf("сколько бензоколонок: ");
    scanf("%d", &M);

    int **matrix = allocate_matrix(N, M);
    if (matrix == NULL) {
        printf("аллокация накрылась медным купоросом\n");
        return 1;
    }

    printf("Введи элементы матрички вот такой ширины %d вот такой низины %d:\n", N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int **transpose = allocate_matrix(M, N);
    if (transpose == NULL) {
        printf("\n");
        free_matrix(matrix, N);
        return 1;
    }

    // трахпонируем
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }

    printf("Эво рыбинская транспозиция: \n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", transpose[i][j]);
        }
        printf("\n");
    }

    // чемодан вокзал на выход
    free_matrix(matrix, N);
    free_matrix(transpose, M);

    return 0;
}
