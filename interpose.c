#include <stdio.h>

void bill(char *arg) {
    printf("INTERPOSE: bill is called\n");
}

void sam() {
    printf("INTERPOSE: sam is called\n");
}

void fred(int arg) {
    printf("INTERPOSE: fred is called instead of real fred\n");
}

void john() {
    printf("INTERPOSE: john is called instead of real john\n");
}
