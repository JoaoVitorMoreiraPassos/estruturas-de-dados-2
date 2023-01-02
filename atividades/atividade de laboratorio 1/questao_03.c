#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct lista Lista;

typedef struct pessoa 
{
    int Id;
    char *Nome;
    int AnoNascimento;
    int Altura;
}Pessoa;

struct lista
{
    Pessoa Info;
    Lista *prox;
};
int listLen(Lista *lis){
    int len = 0;
    if(lis != NULL){
        len += listLen(lis->prox);
        len ++;
    }
    return len;
}
Lista * incializa()
{
    return NULL;
}
Lista *alocaNo(int id, char *nome, int ano_nascimento, int altura)
{
    Lista *no = (Lista*) malloc(sizeof(Lista));
    no->Info.Id = id;
    no->Info.Nome = (char *) malloc(sizeof(char) * strlen(nome));
    strcpy(no->Info.Nome, nome);
    no->Info.AnoNascimento = ano_nascimento;
    no->Info.Altura = altura;
    no->prox = NULL;
    return no;
}
Lista * insere(Lista *lis, int id, char *nome, int ano_nascimento, int altura)
{
    Lista *no = alocaNo( id, nome, ano_nascimento, altura);
    no->prox = lis;
    return no;
}

int *letraA(Lista *lis,char **nomes,int *q, int menor)
{
    if(lis != NULL)
    {
        if(lis->Info.Altura <= menor)
            menor = letraA(lis->prox,nomes, q, lis->Info.Altura);
        else
            menor = letraA(lis->prox, nomes, q, menor);
        if(lis->Info.Altura == menor)
        {
            *(nomes+*q) = (char *) malloc(sizeof(char) * strlen(lis->Info.Nome));
            strcpy(*(nomes+*q), lis->Info.Nome);
            ++ *q;
        }
    }
    return menor;
}

void letraB(Lista *lis, int *menor, int *maior)
{
    if(lis != NULL)
    {
        if(lis->Info.Altura < menor || lis->Info.Altura > maior)
        {
            if(lis->Info.Altura < *menor)
                *menor = lis->Info.Altura;
            if(lis->Info.Altura > *maior)
                *maior = lis->Info.Altura;
            letraB(lis->prox,menor, maior);
        }
        else
            letraB(lis->prox, menor, maior);     
    }
}

void letraC(Lista *lis,int media, int *q)
{
    if(lis != NULL)
    {
        if(lis->Info.Altura == media)
            ++ *q;
        letraC(lis->prox, media, q);
    }
}

void letraD(Lista* lis, int media, int *q)
{
    if(lis != NULL)
    {
        if(lis->Info.Altura > media && (2022 - lis->Info.AnoNascimento) > 50)
            ++ *q;
        letraD(lis->prox, media, q);
    }
}

void main()
{
    Lista *people;
    people = incializa();
    people = insere(people, 1, "Joao", 2001, 140);
    people = insere(people, 2, "Vitor", 1956, 170);
    people = insere(people, 3, "Moreira", 2003, 130);
    people = insere(people, 4, "Passos", 2000, 130);
    people = insere(people, 5, "Ana", 1970, 175);
    people = insere(people, 6, "Carla", 2015, 162);
    people = insere(people, 7, "Beatriz", 1998, 180);

    // letra a)
    char **mais_baixos;
    mais_baixos = (char **) malloc(sizeof(char*)*listLen(people));
    int menor, q = 0;
    menor = letraA(people, mais_baixos,&q, people->Info.Altura);
    for(int i = 0; i< q; i ++)
    {
        printf("%s\n", mais_baixos[i]);
    }printf("----------------------\n");
    
    //letra b)
    int maior = people->Info.Altura;
    letraB(people,&menor, &maior);
    printf("menor: %d, maior: %d\n-----------------------\n",menor, maior);

    //letra c)
    int media = (maior+menor)/2;
    int pessoas_altura_media = 0;
    letraC(people, media, &pessoas_altura_media);
    printf("altura media: %d\n", media);
    printf("pessoas na altura media: %d\n", pessoas_altura_media);
    printf("----------------------\n");

    //letra d)
    int idosos_altos = 0;
    letraD(people, media, &idosos_altos);
    printf("idosos altos: %d\n", idosos_altos);
}