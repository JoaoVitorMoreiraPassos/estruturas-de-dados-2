#include <stdio.h>
#include <stdlib.h>

void buscaDivisores(int num,int atual,int *divs, int *qdivs)
{   
    if(atual > 0)
    {
        if(num % atual == 0)
        {
            divs[*qdivs] = atual;
            ++ *qdivs;
        }
        buscaDivisores(num, atual - 1, divs, qdivs);
    }
}

void main()
{
    int n, *divs, qdivs = 0;
    printf("insira um numero: ");
    scanf("%d",&n);
    divs = (int *) malloc(sizeof(int)*n);
    buscaDivisores(n, n,divs, &qdivs);
    printf("quantidade de divisores: %d\n", qdivs);
    printf("--> ");
    int i;
    for( i = qdivs-1; i >= 0;  i--){
        if(i != 0)
            printf(" %d -",divs[i]);
        else
            printf(" %d ",divs[i]);
    }
}
