#include "funcao.h"

// Calcula a qualidade de uma solução
// Recebe:  A solução, a, a matriz de adjacências, mat, e o número de vértices, vert
// Devolve: O custo que é o número de ligações que existem na solução
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
