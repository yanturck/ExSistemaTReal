// Faça um programa que imprima os números primos existentes entre 0 e 99999. UTILIZE
// THREADS. Dica: para cada faixa de mil valores crie um thread e dispare o processo para cada uma
// delas.

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM 99999
#define LENGTH 1000
#define NUMTHREADS NUM/LENGTH

typedef struct {
    int idx, length;
} thread_arg, *ptr_tread_arg;

pthread_t threads[NUMTHREADS];
thread_arg arguments[NUMTHREADS];

void *primos(void *arg) {
    ptr_tread_arg argument = (ptr_tread_arg)arg;
    int i, j, count, endidx;

    endidx = argument -> idx + argument -> length;
    // printf("\nBuscando primos de %d até %d\n", argument -> idx, endidx);
    for (i= argument -> idx; i < endidx; i++) {
        count = 0;
        for (j = 1; j <= i; j++) {
            if (i%j == 0) {
                count++;
            }
        }
        if (count == 2) printf("%d - ", i);
    }
}

int main (int argc, char **argv) {
    int i, remainder;

    remainder = NUM%LENGTH;

    for (i = 0; i < NUMTHREADS; i++) {
        arguments[i].idx = i * LENGTH;
        arguments[i].length = LENGTH;

        if (i == (NUMTHREADS)-1) arguments[i].length += remainder;

        pthread_create(&(threads[i]), NULL, primos, &(arguments[i]));
    }

    for (i = 0; i <= NUMTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nOs números primos entre 0 e %d\n", NUM);
}