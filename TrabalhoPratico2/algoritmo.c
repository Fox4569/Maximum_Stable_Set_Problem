#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
#include "math.h"

// Gera um vizinho
// Parametros: solucao actual, vizinho, numero de vertices
//swap two vertices
void gera_vizinho(int a[], int b[], int n)
{
    int i, p1,p2,prob;

    for(i=0; i<n; i++)
        b[i]=a[i];

    prob=random_l_h(0, 100);

   if(prob<=50) {
       do {
       p1 = random_l_h(0, n - 1);
   } while (b[p1] == 1);
       b[p1]=1;

   }else{
       do {
           p1 = random_l_h(0, n - 1);
       } while (b[p1] == 0);
       b[p1]=0;
   }
}

//void gera_vizinho2(int a[], int b[], int n)
//{
//    int i, p1, p2;
//
//    for(i=0; i<n; i++)
//        b[i]=a[i];
//	// Encontra posicao com valor 0
//    do
//        p1=random_l_h(0, n-1);
//    while(b[p1] != 0);
//	// Encontra posicao com valor 1
//    do
//        p2=random_l_h(0, n-1);
//    while(b[p2] != 1);
//	// Troca
//    b[p1] = 1;
//    b[p2] = 0;
//
//    do
//        p1=random_l_h(0, n-1);
//    while(b[p1] != 0);
//	// Encontra posicao com valor 1
//    do
//        p2=random_l_h(0, n-1);
//    while(b[p2] != 1);
//	// Troca
//    b[p1] = 1;
//    b[p2] = 0;
//}

int verifica_validade(int *sol, int *mat,int vert) {
    int i = 0, j = 0;
    for (i = 0; i < vert; i++)
        if (sol[i] == 1) {
            for (j = 0; j < vert; j++)
                if (sol[j] == 1 && mat[i * vert + j] == 1) {
                    return 0;
                }
        }
    return 1;
}

// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada
int trepa_colinas(int sol[], int *mat, int vert, int arestas, int num_iter)
{
    int *nova_sol, custo, custo_viz, i;
    int verifica = 0;
    //matriz para a nova solucao
	nova_sol = malloc(sizeof(int)*vert);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    //------------------------------------------//

	// Avalia solucao inicial
    custo = calcula_fit(nova_sol, vert);
    //-------------------------------------//

    for(i=0; i<num_iter; i++)
    {
        do {
            gera_vizinho(sol, nova_sol, vert);
            verifica = verifica_validade(nova_sol, mat, vert);
        }while(verifica==0);
		// Avalia vizinho
        custo_viz = calcula_fit(nova_sol,vert);

        if(custo_viz >= custo) //trocar isto pela linha de baixo
        {
			substitui(sol, nova_sol, vert);
			custo = custo_viz;
        }
    }
    free(nova_sol);
    return custo;
}

//int trepa_colinas_prob(int sol[], int *mat, int vert, int num_iter, float input_prob){
//    int *nova_sol, custo, custo_viz, i;
//    float r;
//
//	nova_sol = malloc(sizeof(int)*vert);
//    if(nova_sol == NULL)
//    {
//        printf("Erro na alocacao de memoria");
//        exit(1);
//    }
//	// Avalia solucao inicial
//    custo = calcula_fit(sol, vert);
//    for(i=0; i<num_iter; i++)
//    {
//		// Gera vizinho
//		gera_vizinho(sol, nova_sol, vert);
//		// Avalia vizinho
//		custo_viz = calcula_fit(nova_sol, mat, vert);
//		// Aceita vizinho se o custo diminuir (problema de minimizacao)
//        if(custo_viz <= custo)  ///Aceita soluções com o mesmo custo
//        {
//			substitui(sol, nova_sol, vert);
//			custo = custo_viz;
//        }else{
//            r = rand_01();
//            if(r < input_prob){ /// r < numero dado pelo stor
//                substitui(sol, nova_sol, vert);
//                custo = custo_viz;
//            }
//        }
//    }
//    free(nova_sol);
//    return custo;
//}
//
//int simulated_annealing(int sol[], int *mat, int vert, int num_iter, float T_Max, float T_Min, float vel_arref){
//    float t = T_Max, delta_c, prob, expression;
//
//    int *nova_sol, custo, custo_viz, num_iter_final = 0, i;
//
//	nova_sol = malloc(sizeof(int)*vert);
//    if(nova_sol == NULL)
//    {
//        printf("Erro na alocacao de memoria");
//        exit(1);
//    }
//	// Avalia solucao inicial
//    custo = calcula_fit(sol, mat, vert);
//    for(i=0; i<num_iter; i++)
//    {
//        // Gera vizinho
//		gera_vizinho(sol, nova_sol, vert);
//		// Avalia vizinho
//		custo_viz = calcula_fit(nova_sol, mat, vert);
//		// Aceita vizinho se o custo diminuir (problema de minimizacao)
//		delta_c = custo_viz - custo;
//        if(delta_c <= 0)  ///Aceita soluções com o mesmo custo
//        {
//			substitui(sol, nova_sol, vert);
//			custo = custo_viz;
//        }else{  ///aceita soluções piores
//            prob = rand_01();
//            expression = exp(-delta_c/t);
//            if(prob <= expression){
//                substitui(sol, nova_sol, vert);
//                custo = custo_viz;
//            }
//        }
//        t = t * vel_arref;
//
//        if(t <= T_Min){
//            break;
//        }
//        num_iter_final = i;
//    }
//
//    free(nova_sol);
//    printf("\nIteracoes = %d \n", num_iter_final);
//    return custo;
//}
