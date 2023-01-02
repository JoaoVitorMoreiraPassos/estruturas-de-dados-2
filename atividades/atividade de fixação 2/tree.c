#include <stdio.h>


typedef struct tree Tree;

struct tree{
    int info;
    Tree *esq, *dir;
};

Tree *inicia()
{
    return NULL;
}

Tree *alocaNo(int info){
    Tree *no = (Tree *) malloc(sizeof(Tree));
    no->dir = NULL;
    no->esq = NULL;
    no->info = info;
    return no;
}

void insere(Tree **bt, unsigned info)
{
    if((*bt) == NULL)
        (*bt) = alocaNo(info);
    else if(info < (*bt)->info)
        insere(&(*bt)->esq, info);
    else if(info > (*bt)->info)
        insere(&(*bt)->dir, info);
}
void mostra( Tree *bt)
{
    if(bt != NULL)
    {
        printf("%d --> ", bt->info);
        mostra(bt->esq);
        mostra(bt->dir);
    }
}
void main()
{
    int v[] = {400, 200, 900, 800, 700, 500, 100, NULL};
    Tree *bt = inicia();
    for (int i = 0; v[i] != NULL; i ++)
    {
        insere(&bt, v[i]);
    }
    mostra(bt);   
}