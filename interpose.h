#include <stdio.h>

void fred(int arg) {
    printf("INTERPOSE: fred is called\n");
}

void john() {
    printf("INTERPOSE: john is called\n");
}
