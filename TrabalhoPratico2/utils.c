#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include <string.h>

// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
// Devolve a matriz de adjacencias
int* init_dados(char *nome, int *v, int *a)
{
	FILE *f;
	int *p, *q;
	int i, x, y;
    char lixo[1000],aux;
	f=fopen(nome, "r");
	if(!f)
	{
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}


    while(fscanf(f,"%c",&aux)!= EOF) {
        if(aux=='c') {
            fscanf(f, "%[^\n] ", lixo);
        }else if(aux=='p') {
            fscanf(f, "%s",lixo);
            fscanf(f,"%d %d",v,a);

            q = malloc(sizeof(int)*(*v)*(*v));
            if(!q)
            {
                printf("Erro na alocacao de memoria\n");
                exit(1);
            }
            p=q;
            for(i=0;i<((*v)*(*v));i++){
                p[i]=0;
            }
        }else if(aux=='e'){
            fscanf(f, " %d %d",&x,&y);
            printf("x-> %d - y-> %d\n",x,y);
            p[((x-1)*(*v))+(y-1)]=1;
            p[((y-1)*(*v))+(x-1)]=1;
        }
    }

    for(i=0;i<((*v)*(*v));i++){
        printf("p[%d]=%d\n",i+1,p[i]);
    }

    fclose(f);
	return p;

}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
void gera_sol_inicial(int *sol, int v)
{
	int i, x;

	for(i=0; i<v; i++)
        sol[i]=0;
	for(i=0; i<v/2; i++)
    {
        do
			x = random_l_h(0, v-1);
        while(sol[x] != 0);
        sol[x]=1;
    }
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert)
{
	int i;

	printf("\nConjunto A (0): ");
	for(i=0; i<vert; i++)
		if(sol[i]==0)
			printf("%2d  ", i);
	printf("\nConjunto B (1): ");
	for(i=0; i<vert; i++)
		if(sol[i]==1)
			printf("%2d  ", i);
	printf("\n");
}

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}

// Inicializa o gerador de numeros aleatorios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01()
{
	return ((float)rand())/RAND_MAX;
}
