#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"

#define DEFAULT_RUNS 100

int main(int argc, char *argv[])
{
    char    nome_fich[100];
    int     vert, arestas, k, runs, custo, best_custo=0, verifica, iter;
    int     *grafo, *sol, *best;
	float   mbf = 0.0;
	///Caso -> Trepa_Colina Probabilístico
	//float input_prob;
	///Caso -> Simulated Annealing
	//float T_Max, T_Min, vel_arref;

	if(argc == 3)
	{
		runs = atoi(argv[2]);
		strcpy(nome_fich, argv[1]);
	}
	else
        if(argc == 2)
        {
            runs = DEFAULT_RUNS;
            strcpy(nome_fich, argv[1]);
        }
        else
        {
            runs = DEFAULT_RUNS;
            printf("Nome do Ficheiro: ");
            gets(nome_fich);
        }
	if(runs <= 0)
		return 0;

	init_rand();
    // Preenche matriz de adjacencias
    grafo = init_dados(nome_fich, &vert, &arestas);
	sol = malloc(sizeof(int)*vert);
	best = malloc(sizeof(int)*vert);
	if(sol == NULL || best == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}

    printf("\n\nInsira o numero de iterecoes: ");
    scanf("%d",&iter);
	for(k=0; k<runs; k++)
	{
		// Gerar solucao inicial
        do {
            gera_sol_inicial(sol, vert);

            verifica = verifica_validade(sol, grafo, vert);
        }while(verifica==0);

		escreve_sol(sol, vert);

		/// Trepa colinas
		custo = trepa_colinas(sol, grafo, vert, arestas, iter);

		 // Escreve resultados da repeticao k
		printf("\nRepeticao %d:\n", k);
        printf("\tSolucao final: ");
		escreve_sol(sol, vert);
		printf("\tCusto final: %2d\n", custo);
        mbf += custo;
		if(k==0 || best_custo < custo)
		{
			best_custo = custo;
			substitui(best, sol, vert);
		}
    }
	// Escreve resultados globais
	printf("\n\nMBF: %f\n", mbf/k);
	printf("\nMelhor solucao encontrada");
	escreve_sol(best, vert);
	printf("Custo final: %2d\n", best_custo);
	free(grafo);
    free(sol);
	free(best);
    return 0;
}
