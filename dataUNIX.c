// Elabore um programa que pergunte a sua data de nascimento (três valores inteiros). Em seguida,
// deve-se converter esses valores para uma data no padrão UNIX. Calcula a sua idade precisa (anos,
// meses e dias) usando as funções de tempo da biblioteca “time”.

#include <stdio.h>
#include <time.h>

int main() {
    int dia, mes, ano;
    time_t dataNascimento, dataAtual;

    struct tm *data, *idade;

    printf("Qual o dia em que você nasceu?\n");
    scanf("%d", &dia);
    printf("\nQual o mês que você nasceu?\n");
    scanf("%d", &mes);
    printf("\nQual o ano que você nasceu?\n");
    scanf("%d", &ano);

    time(&dataNascimento);
    data = localtime(&dataNascimento);
    data -> tm_mday = dia;
    data -> tm_mon = mes-1;
    data -> tm_year = ano-1830;
    
    dataNascimento = mktime(data);
    dataAtual = time(NULL);

    long int idadeSeg = dataAtual - dataNascimento;
    idade = localtime(&idadeSeg);

    printf("\nVocê tem %d anos, %d meses e %d dias.\n", idade -> tm_year, idade -> tm_mon, idade -> tm_mday);
}