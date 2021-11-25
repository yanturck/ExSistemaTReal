// Elabore um programa que calcule uma aproximação para π, a
// partir da série abaixo. Use 100 termos na série e 4 threads
// para efetuar os cálculos.

#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define NUMTHREADS  4
#define TERMOS 100

typedef struct {
	int idx, length;
} thread_arg, *ptr_thread_arg;

pthread_t   threads[NUMTHREADS];  // Threads do programa
thread_arg  arguments[NUMTHREADS];  // Argumentos das threads

float sum;

void *thread_func(void *arg) {
    ptr_thread_arg  argument = (ptr_thread_arg)arg;
    int i, endidx;
    float  localsum = 0;

    endidx = argument->idx + argument->length;  // Posição do ultimo+1
    printf("Calculando do termo %d ate %d\n", argument->idx, endidx);

    for (i = argument->idx; i < endidx; i++) {
        localsum += 4*(pow(-1, i)/(2*i+1));
    }
    printf("Aproxima = %f\n", localsum);
	sum += localsum; // Acumula a soma da thread na soma geral (sum = sum+localsum)
}

int main(int argc, char **argv) {
	int i, length, remainder;  // remainder = resto

	sum = 0;
    length = TERMOS / NUMTHREADS; // Tamanho dos dados de cada thread (divisão inteira)
	remainder = TERMOS % NUMTHREADS; // Resto da divisão inteira
	// Criar todas as threads
	for(i = 0; i < NUMTHREADS; i++) {
		arguments[i].idx = i * length;
		arguments[i].length = length;
		if(i == (NUMTHREADS - 1)) // Testa se é ultima thread
			arguments[i].length += remainder; // A última recebe o resto, além dos dados
		pthread_create(&threads[i], NULL, thread_func, &arguments[i]);
	}
	// Aguardar todas as threads terminarem
	for(i=0; i<NUMTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	printf("Aproximação = %f\n", sum);
}