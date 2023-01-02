#include <stdio.h>
#include <stdlib.h>


typedef struct avl avl;

struct avl{
    int info;
    int altura;
    avl *esq, *dir;
};

int alturar(avl* esq, avl* dir){
    int maior = 0;
    if(esq == NULL && dir != NULL)
        maior = dir->altura+1;
    if(dir == NULL && esq != NULL)
        maior = esq->altura+1;
    else
        maior = esq->altura > dir->altura ? esq->altura+1 : dir->altura+1;
    return maior;
}

void inserir(avl **tree, int valor){
    if((*tree) == NULL){
        (*tree) = (avl *) malloc(sizeof(avl));
        (*tree)->info = valor;
        (*tree)->altura = 0;
        (*tree)->esq = NULL;
        (*tree)->dir = NULL;
    }
    else{
        if((*tree)->info > valor)
            inserir(&(*tree)->esq, valor);
        else
            inserir(&(*tree)->dir, valor);
        (*tree)->altura = alturar((*tree)->esq, (*tree)->dir);
    }
}

void rot1(avl **tree){
    
}
preorder(avl *tr){
    if(tr != NULL)
    {
        printf("%d, %d --> ",tr->info, tr->altura);
        preorder(tr->esq);
        preorder(tr->dir);
    }
}
void main()
{
    avl *tr = NULL;
    inserir(&tr, 40);
    printf("tr: %d\n",tr->info);
    inserir(&tr, 20);
    inserir(&tr, 50);
    inserir(&tr, 10);
    inserir(&tr, 1);
    preorder(tr);
}