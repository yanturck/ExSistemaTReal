// Crie um programa multithread que realize uma busca de um número em um
// vetor aleatório de 100 números inteiros. Devem ser criadas quatro threads e o
// vetor deve ser populado com números aleatórios inteiros gerados pelo sistema.

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUMTHREADS 4
#define DM 100 // dimensão do vetor

int main (void)
{
    int vetor[DM];
    for (int i = 0; i<DM; i++) {
        vetor[i] = rand() % 100;
        printf("%d-", vetor[i]);
    }
}