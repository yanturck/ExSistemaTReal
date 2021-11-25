// Crie um programa multithread para calcular o produto de duas matrizes
// inteiras quadradas de ordem 4. Devem ser criadas dezesseis threads, cada uma
// para calcular um dos dezesseis elementos da matriz resultante.

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUMTHREADS 16
#define DM 4 // dimensão das matrizes

int main (void)
{
  int rst[DM][DM] = {0, 0, 0, 0};
  int sum;

  int a[DM][DM] = {1, 1, 2, 0,
                  0, 1, 3, 4,
                  3, 1, 0, 2,
                  3, 2, 1, 1};
  int b[DM][DM] = {5, 3, 3, 6,
                  2, 3, 1, 1,
                  2, 1, 1, 0,
                  2, 1, 1, 3};
      
  for (int i = 0; i<DM; i++) // capturando linhas
  {
    for (int j = 0; j<DM; j++) // capturando columas
    {
      sum = 0;
      for (int k = 0; k<DM; k++) {sum += a[i][k]*b[k][j];}
      rst[i][j] = sum;
    }
  }

  for (int i = 0; i<DM; i++)
  {
    for (int j = 0; j<DM; j++)
    {
      printf("%d\n", rst[i][j]);
    }
  }

  return 0;
}
