// Implemente um programa que simule uma corrida de cavalos, contendo 5 participantes, usando
// threads. Cada thread deve representar um cavalo e o percurso da corrida será gerenciado a partir de
// uma matriz de 5 x 10 posições. As linhas desta matriz representam os cavalos e as colunas
// representam as distâncias percorridas em certo instante de tempo (10 tomadas de tempo) de valores
// aleatórios para cada cavalo (inteiros de 1 a 3). Vence a corrida quem tiver percorrido, ao final das
// dez tomadas, a maior distância (soma das colunas de cada linha).

#include <stdio.h>
#include <math.h>
#include <pthread.h>