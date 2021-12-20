// Faça um programa que imprima os números primos existentes entre 0 e 99999. UTILIZE
// THREADS. Dica: para cada faixa de mil valores crie um thread e dispare o processo para cada uma
// delas.

// Com uso de semáforo

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM 99999
#define LENGTH 1000
#define NUMTHREADS NUM/LENGTH

typedef struct {
    int idx, length;
} thread_arg, *ptr_tread_arg;

pthread_t threads[NUMTHREADS];
thread_arg arguments[NUMTHREADS];

sem_t S;
int count;

void *primos(void *arg) {
    ptr_tread_arg argument = (ptr_tread_arg)arg;
    int i, j, endidx;

    endidx = argument -> idx + argument -> length;
    // printf("\nBuscando primos de %d até %d\n", argument -> idx, endidx);
    for (i= argument -> idx; i < endidx; i++) {
        count = 0;
        for (j = 1; j <= i; j++) {
            if (i%j == 0) {
                sem_wait(&S);
                count++;
                sem_post(&S);
            }
        }
        if (count == 2) printf("%d - ", i);
    }
}

int main (int argc, char **argv) {
    int i, remainder;

    sem_init(&S, 0, 1);
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

    sem_destroy(&S);
    printf("\nOs números primos entre 0 e %d\n", NUM);
}