#include "funcao.h"

// Calcula a qualidade de uma solu��o
// Recebe:  A solu��o, a, a matriz de adjac�ncias, mat, e o n�mero de v�rtices, vert
// Devolve: O custo que � o n�mero de liga��es que existem na solu��o
int calcula_fit(int a[], int vert)
{
	int total=0;
    int i;
    for(i=0;i<vert;i++){
        if(a[i]==1)
            total++;
    }
	return total;
}
