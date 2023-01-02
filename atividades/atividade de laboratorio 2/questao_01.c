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

void insere(Bt **bt, unsigned info)
{
    if((*bt) == NULL)
        (*bt) = alocaNo(info);
    else if(info < (*bt)->info)
        insere(&(*bt)->esquerda, info);
    else if(info > (*bt)->info)
        insere(&(*bt)->direita, info);
}

double letraA(Bt **bt)
{
    double mult = 1;
    if(*bt != NULL)
    {
        if((*bt)->info % 5 == 0 && (*bt)->info > 20)
        {
            mult *= (*bt)->info;
            mult *= letraA(&(*bt)->esquerda);
            mult *= letraA(&(*bt)->direita);
        }
        else{
            mult = letraA(&(*bt)->esquerda);
            mult = letraA(&(*bt)->direita);
        }
    }
    return mult;
}   

int letraB(Bt **bt)
{
    int len = 0;
    if (*bt != NULL)
    {
        len += letraB(&(*bt)->esquerda);
        len += letraB(&(*bt)->direita);
        len ++;
    }
    return len;
}
int descendentes(Bt **bt, int valor){
    int quant = 0;
    if((*bt) != NULL){
        if((*bt)->info == valor)
        {
            printf("achou\n");
            quant = letraB(&(*bt));
            if(quant > 0){
                quant --;
            }
        }
        else if((*bt)->info < valor)
            quant = descendentes(&(*bt)->direita, valor);
        else if((*bt)->info > valor)
            quant = descendentes(&(*bt)->esquerda, valor);
    }
    printf("quant: %d\n",quant);
    return quant;
}
int letraC(Bt **root,Bt **node, unsigned son)
{//Essa eh uma solucao para numeros inteiros positivos;
    int dad = -1;
    if (*node != NULL)
    {
        if((*node)->info > son)
            dad = letraC(&root,&(*node)->esquerda, son);
        else if((*node)->info < son)
            dad = letraC(&root,&(*node)->direita, son);
        if(dad == -2)
            dad = (*node)->info;
        else if((*node)->info == son && (*node)->info != (*root)->info)
            dad = -2;
    }
    return dad;
}

int letraD(Bt **bt, int info)
{
    int del = 0;
    if(*bt != NULL)
    {
        if((*bt)->info > info)
            del = letraD(&(*bt)->esquerda, info);
        else if((*bt)->info < info)
            del = letraD(&(*bt)->direita, info);
        else{
            if((*bt)->direita == NULL &&  (*bt)->esquerda == NULL)
            {   
                *bt = NULL;
                free(*bt);
            }else if((*bt)->direita == NULL &&  (*bt)->esquerda != NULL)
            {
                Bt *aux = (*bt)->esquerda;
                (*bt)->info = aux->info;
                (*bt)->esquerda = aux->esquerda;
                (*bt)->direita = aux->direita;
                aux = NULL;
                free(aux);                
            }else if((*bt)->direita != NULL &&  (*bt)->esquerda == NULL)
            {
                Bt *aux = (*bt)->direita;
                (*bt)->info = aux->info;
                (*bt)->esquerda = aux->esquerda;
                (*bt)->direita = aux->direita;
                aux = NULL;
                free(aux); 
            }
            else if((*bt)->direita != NULL &&  (*bt)->esquerda != NULL)
            {
                Bt *aux = (*bt)->direita, *ant;
                ant = aux;
                while(aux->esquerda != NULL)
                {
                    ant = aux;
                    aux = aux->esquerda;
                }
                (*bt)->info = aux->info;
                if(ant != aux)
                    ant->esquerda = aux->direita != NULL ? aux->direita : NULL;
                else
                    (*bt)->direita = NULL;
                aux = NULL;
                free(&aux);
            }
            del = 1;
        }
    }
    return del;
}

// A função mostraArvore faz um desenho esquerda-direita-raiz
// da árvore x. O desenho terá uma margem esquerda de
// 3b espaços.
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

void inOrdem(Bt **bt)
{
    if (*bt != NULL)
    {
        printf("%d -> ", (*bt)->info);
        inOrdem(&(*bt)->esquerda);
        inOrdem(&(*bt)->direita);
    }
}

void main()
{
    Bt *bt  = inicia();
    int infos[] = {50,40,100,20,45,30,120,60,55,70,65,64,68, NULL};
    for(int i = 0; *(infos+i) != NULL; i ++)
        insere(&bt, *(infos+i));
    
    // printf("--> ");
    // inOrdem(&bt);
    // printf("\n");

    // //letra A
    // printf("produto dos multiplos de 5 e maiores que 20: %.0lf\n",letraA(&bt));

    // //letra B
    // printf("quantidade de nos: %d\n", letraB(&bt));

    // //letra C
    // printf("pai: %d\n", letraC(&bt,&bt, 55));

    // //letra D
    // int del = letraD(&bt, 100);
    // printf("deletou: %d\n", del);
    // del = letraD(&bt, 60);
    // printf("deletou: %d\n", del);
    // del = letraD(&bt, 45);
    // printf("deletou: %d\n", del);
    // del = letraD(&bt, 40);
    // printf("deletou: %d\n", del);
    // del = letraD(&bt, 50);
    // printf("deletou: %d\n", del);

    mostraArvore(bt,7);
    printf("descente: %d\n", descendentes(&bt, 40));
}