// Crie um programa multithread que calcule o valor da função f(x) = (sen(x))^3
// + sqrt(cos(x)), usando a série de Taylor com 20 termos. Cada Thread irá calcular
// o valor de uma das duas funções.

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define NUMTHREADS 2
#define TERMOS 20

typedef struct {
    int fromidx, length;
}thread_arg, *ptr_thread_arg;

pthread_t threads[NUMTHREADS];
thread_arg arguments[NUMTHREADS];
int term[TERMOS];
int sum;
float f;

void *thread_func(void *arg)
{
    ptr_thread_arg argument = (ptr_thread_arg)arg;
    int i, localsum = 0, endidx;
    
    endidx = argument->fromidx + argument->length;

    for(i=argument->fromidx; i<endidx; i++) {
        f = sin(i);
    }
    sum += localsum;
}