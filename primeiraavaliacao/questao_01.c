#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 10000

typedef struct binarytree Bt;

struct binarytree{
    int info;
    Bt *esq, *dir;
};
typedef struct diferencas{
    int num;
    int quant;
}Diferencas;
Bt *inicia()
{
    return NULL;
}
Bt *aloca(int valor)
{
    Bt *novo = (Bt*) malloc(sizeof(Bt));
    novo->info = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}
int menorEsq(Bt *bt);
int menorDir(Bt *bt);

int insere(Bt **bt, int info)
{
    int inseriu = -1;
    if( (*bt) == NULL)
    {
        (*bt) = aloca(info);
        inseriu = 1;
    }else{
        if((*bt)->info > info)
        {
            inseriu = insere(&(*bt)->esq, info);
        }
        else if((*bt)->info < info)
        {

            inseriu = insere(&(*bt)->dir, info);
        }
    }
    return inseriu;
}
int ehfolha(Bt *bt)
{
    return (bt->esq == NULL && bt->dir == NULL);
}
int menorEsq(Bt *bt)
{   
    int menor = -1;
    if(bt != NULL)
    {
        if(ehfolha(bt))
            menor = 0;
        if(bt->esq == NULL)
            menor = menorEsq(bt->dir);
        else if(bt->dir == NULL)
            menor = menorEsq(bt->esq);
        else{
            int esq = menorEsq(bt->esq);      
            int dir = menorDir(bt->dir);
            menor = esq < dir ? esq : dir;
        }
    }
    return menor+1;
}
int menorDir(Bt *bt)
{  
    int menor = -1;
    if(bt != NULL)
    {
        if(ehfolha(bt))
            menor = 0;
        if(bt->esq == NULL)
            menor = menorDir(bt->dir);
        else if(bt->dir == NULL)
            menor = menorDir(bt->esq);
        else{
            int esq = menorEsq(bt->esq);      
            int dir = menorDir(bt->dir);  
            menor = esq < dir ? esq: dir;    
        }
    }
    return menor+1;
}
int folhaRaza(Bt *bt)
{
    int menor = -1;
    if(bt != NULL)
    {
        int esq, dir;
        if(bt->esq != NULL && bt->dir != NULL)
        {
            if(ehfolha(bt->esq) || ehfolha(bt->dir))
            {
                menor = 1;
            }else{
                esq = menorEsq(bt->esq);
                dir = menorDir(bt->dir);
                menor = esq < dir ? esq : dir;
                printf("esq: %d, dir: %d\n",esq, dir);
            }
        }else{
            if(bt->esq == NULL)
                menor = menorDir(bt->dir);
            else if(bt->dir == NULL)
                menor = menorEsq(bt->esq);
            printf("esq: %d, dir: %d\n",esq, dir);
        }
    }
    return menor;
}


int folhaFunda (Bt* r) {
    int maior = -1;
    if(r != NULL){
        int esq = folhaFunda (r->esq);
        int dir = folhaFunda (r->dir);
        maior = esq < dir ? dir+1 : esq+1;
    }
    return maior;
}
int busca(Bt *bt, int valor)
{   int achou = -1;
    if(bt != NULL)
    {
        if(bt->info == valor)
        {
            achou = 1;
        }
        else if(bt->info > valor)
            achou = busca(bt->esq, valor);
        else if(bt->info < valor)
            achou = busca(bt->dir, valor);
    }
    return achou;
}

// void mostraArvore(Bt* a, int b) {
//     if (a == 0) {
//         imprimeNo(0, b);
//         return;
//     }
//     mostraArvore(a->dir, b+1);
//     imprimeNo(a->info, b);
//     mostraArvore(a->esq, b+1);
// }

// // A função auxiliar imprimeNo imprime o caracter
// // c precedido de 3b espaços e seguido de uma mudança
// // de linha.
// void imprimeNo(int c, int b) {
//     int i;
//     for (i = 0; i < b; i++) printf("     ");
//         if(c == NULL)
//             printf("NULL\n");
//         else
//             printf("%d\n", c);
// }

void main()
{
    clock_t tempoi1, tempoi2, tempob1, tempob2;
    Diferencas *dif = (Diferencas *) malloc(sizeof(Diferencas));
    int lenofdif = 0;
    double tf;
    int i;
    // FILE *arq = fopen("1qdiferenca.txt", "w");
    srand(time(NULL));
    for(i = 0; i < 30; i ++)
    {
        Bt *bt = inicia();  
        int j;

        // gerar numeros aleatoriamente
        tempoi1 = clock();
        for( j = 0; j < TAM/2; j ++)
            while(insere(&bt, (rand()%TAM*100)) == -1);
        for( j = 0; j < TAM/2; j ++)
            while(insere(&bt, (rand()%TAM*100)) == -1);
        tempoi2 = clock();
        tf = (tempoi2) - (tempoi1) * 1000 / CLOCKS_PER_SEC;
        printf("Tempo de insercao: %lf\n", tf);
        // Maior e menor profundidade.
        // mostraArvore(bt, 1);
        int profunda = folhaFunda(bt), raza = folhaRaza(bt);
        printf("Maior profundidade: %d - Menor profundidade: %d\n", profunda, raza);

        // busca
        tempob1 = clock();
        printf("achou? %d\n", busca(bt, 1000));
        tempob2 = clock();
        tf = ((tempob2*1000) - (tempob1*1000)) / CLOCKS_PER_SEC;
        printf("Tempo de busca %lf\n", tf);
        // gravar as diferecas e suas repeticoes.
        for(j = 0; j < lenofdif; j ++)
            if((dif+j)->num == profunda - raza)break;
        if(j == lenofdif)
        {
            dif = (Diferencas *) realloc(dif, (lenofdif+1) * sizeof(Diferencas));
            (dif+lenofdif)->num = profunda - raza;
            (dif+lenofdif)->quant = 1;
            lenofdif ++;
        }
        else
            (dif+j)->quant ++;

        printf("---------------------------------------------\n");
        free(bt); 
    }
    for(i = 0;i < lenofdif; i ++){
        printf("diferenca: %d, repeticoes: %d\n",(dif+i)->num, (dif+i)->quant);
        // fprintf(arq, "%d\t%d\n", (dif+i)->num,(dif+i)->quant );
    }
}
