#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x, y;

    printf("Enter (number of your) x: ");
    scanf("%d", &x);
    printf("Введи у: ");
    scanf("%d", &y);
    swap(&x, &y);
    printf("Свопнутые: x = %d, y = %d\n", x, y);

    return 0;
}
