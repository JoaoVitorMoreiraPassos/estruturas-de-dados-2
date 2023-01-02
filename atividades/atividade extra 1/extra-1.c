#include <stdio.h>
#include <stdlib.h>


typedef struct binaretree Bt;

struct binaretree
{
    int info;
    Bt *esquerda;
    Bt *direita;
};

Bt *inicia()
{
    return NULL;
}

Bt *alocaNo(int info){
    Bt *no = (Bt *) malloc(sizeof(Bt));
    no->direita = NULL;
    no->esquerda = NULL;
    no->info = info;
    return no;
}
void mostraArvore(Bt* a, int b) {
    if (a == NULL) {
        imprimeNo(NULL, b);
        return;
    }
    mostraArvore(a->direita, b+1);
    imprimeNo(a->info, b);
    mostraArvore(a->esquerda, b+1);
}

// A função auxiliar imprimeNo imprime o caracter
// c precedido de 3b espaços e seguido de uma mudança
// de linha.
void imprimeNo(int c, int b) {
    int i;
    for (i = 0; i < b; i++) printf("     ");
        if(c == NULL)
            printf("NULL\n");
        else
            printf("%d\n", c);
}

void insere(Bt **bt, unsigned info)
{
    if((*bt) == NULL)
        (*bt) = alocaNo(info);
    else if(info < (*bt)->info)
        insere(&(*bt)->esquerda, info);
    else if(info > (*bt)->info)
        insere(&(*bt)->direita, info);
}

int profundidade (Bt *bt, int num)
{
    int depht = 0;
    if(bt != NULL)
    {
        if(num < bt->info){
            depht += profundidade(bt->esquerda, num);
            depht ++;
        }
        else if(num > bt->info){
            depht += profundidade(bt->direita,  num);
            depht ++;
        }
    }
    return depht;
}

int altura (Bt *bt) {
    if (bt == NULL) 
        return -1; // altura da árvore vazia
    else {
        int he = altura (bt->esquerda);
        int hd = altura (bt->direita);
        
        return he > hd ? he+1 : hd+1;
    }
}

int buscaAltura(Bt *bt, int info)
{
    int h;
    if(bt != NULL){
        if(bt->info == info)
            h = altura(bt);
        else if(bt->info > info)
            h = buscaAltura(bt->esquerda, info);
        else if(bt->info < info)
            h = buscaAltura(bt->direita, info);
    }
    return h;
}


void main()
{
    Bt *bt  = inicia();
    int infos[] = {50,40,100,20,45,30,120,60,55,70,65,64,68, NULL};
    for(int i = 0; *(infos+i) != NULL; i ++)
        insere(&bt, *(infos+i));
    mostraArvore(bt, 7);
    // printf("profundidade 50: %d\n",profundidade(bt, 50));
    // printf("profundidade 100: %d\n",profundidade(bt, 100));
    // printf("profundidade 45: %d\n",profundidade(bt, 45));
    // printf("profundidade 70: %d\n",profundidade(bt, 70));
    // printf("profundidade 65: %d\n",profundidade(bt, 65));
    // printf("profundidade 68: %d\n",profundidade(bt, 68));

    printf("\n-------------\n");
    printf("altura 50: %d\n", buscaAltura(bt,50));
    printf("altura 100: %d\n", buscaAltura(bt,100));
    printf("altura 45: %d\n", buscaAltura(bt,45));
    printf("altura 70: %d\n", buscaAltura(bt,70));
    printf("altura 65: %d\n", buscaAltura(bt,65));
    printf("altura 68: %d\n", buscaAltura(bt,68));
}