// Implemente um programa que simule uma corrida de cavalos, contendo 5 participantes, usando
// threads. Cada thread deve representar um cavalo e o percurso da corrida será gerenciado a partir de
// uma matriz de 5 x 10 posições. As linhas desta matriz representam os cavalos e as colunas
// representam as distâncias percorridas em certo instante de tempo (10 tomadas de tempo) de valores
// aleatórios para cada cavalo (inteiros de 1 a 3). Vence a corrida quem tiver percorrido, ao final das
// dez tomadas, a maior distância (soma das colunas de cada linha).

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUMTHREADS 5
#define DISTANCIA 10
#define LENGTH 1

typedef struct {
    int idx, length;
} thread_arg, *ptr_tread_arg;

pthread_t threads[NUMTHREADS];
thread_arg arguments[NUMTHREADS];

sem_t S;
int disputa[NUMTHREADS][DISTANCIA];

void *corrida(void *arg) {
    ptr_tread_arg argument = (ptr_tread_arg)arg;
    int i, j, count, endidx;

    endidx = argument -> idx + argument -> length;

    for (i= argument -> idx; i < endidx; i++) {
        for (j = 0; j < DISTANCIA; j++) {
            sem_wait(&S);
            disputa[i][j] = (rand() % 3) + 1; // valores aleatorios de 1 a 3
            sem_post(&S);
        }
    }
}

int main(int argc, char **argv) {
    int i, j, vencedor;
    sem_init(&S, 0, 1);

    int apuracao[NUMTHREADS]; // vetor responsavel pela soma de todos os participantes
    int tragetoria = 0; // tragetoria do participante

    // criando as threads
    for (i = 0; i < NUMTHREADS; i++) {
        arguments[i].idx = i;
        arguments[i].length = LENGTH;

        pthread_create(&(threads[i]), NULL, corrida, &(arguments[i]));
    }

    // aguardando as threads terminarem
    for (i = 0; i < NUMTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // apurando as distancias
    for (i = 0; i < NUMTHREADS; i++) {
        apuracao[i] = 0;
        
        for (j = 0; j < DISTANCIA; j++) {
            apuracao[i] += disputa[i][j]; // somando a distancia do participante "i"
        }

        printf("O Cavalo %d percorreu %d.\n", i+1, apuracao[i]);

        // verificando o vencedor
        if (apuracao[i] > tragetoria) {
            vencedor = i;
            tragetoria = apuracao[i]; 
        }
    }
    sem_destroy(&S);
    printf("O vencedor da corrida foi o Cavalo de número %d.\n", vencedor+1);
}