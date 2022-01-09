// Crie um programa multithread que realize uma busca de um número em um
// vetor aleatório de 100 números inteiros. Devem ser criadas quatro threads e o
// vetor deve ser populado com números aleatórios inteiros gerados pelo sistema.

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define NUMTHREADS 4
#define DMV 100 // dimensão do vetor
#define NUM 36

typedef struct {
	int idx, length;
} thread_arg, *ptr_thread_arg;

pthread_t   threads[NUMTHREADS];  // Threads do programa
thread_arg  arguments[NUMTHREADS];  // Argumentos das threads

sem_t S;
int vetor[DMV];
bool find = false;

void *thread_func(void *arg) {
    ptr_thread_arg  argument = (ptr_thread_arg)arg;
    int i, endidx;

    endidx = argument->idx + argument->length;  // Posição do ultimo+1
    printf("Buscando número entre %d - %d no vetor\n", argument->idx, endidx);

    for (i = argument->idx; i < endidx; i++) {
        if(vetor[i] == NUM) {
            printf("\nNúmero encontrado na posicão %d pela thread %ld\n", i, pthread_self());
            sem_wait(&S);
            find = true;
            sem_post(&S);
        }
    }
}

int main (int argc, char **argv) {
    int length, remainder;
    clock_t tInicio, tFim, t;

    tInicio = clock();
	sem_init(&S, 0, 1);

    length = DMV / NUMTHREADS;
    remainder = DMV % NUMTHREADS;

    // populando o vetor
    for (int i = 0; i<DMV; i++) {
        vetor[i] = rand() % 100;
        // printf("%d-", vetor[i]);
    }

    // criando as threads
    for (int i = 0; i < NUMTHREADS; i++) {
        arguments[i].idx = i * length;
        arguments[i].length = length;

        if (i == (NUMTHREADS-1)) arguments[i].length += remainder;
        
        pthread_create(&threads[i], NULL, thread_func, &arguments[i]);

        for (int i = 0; i< NUMTHREADS; i++) {
            pthread_join(threads[i], NULL);
        }
    }
    if (!find) printf("\nThreads não encontraram o numero! :(\n");

    sem_destroy(&S);

	tFim = clock();
    t = tFim - tInicio;

    printf("Tempo gasto: %lf s\n", (double)t/CLOCKS_PER_SEC);
}