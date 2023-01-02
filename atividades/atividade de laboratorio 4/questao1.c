#include <stdio.h>
#include <stdlib.h>

typedef struct Arv23 Arv23;
struct Arv23{
	int Info1, Info2, NInfos;
	struct Arv23 *esq, *cen,*dir;
};

struct Arv23 *criaNo(int valor,struct Arv23 *FEsq,struct Arv23 *FCen,struct Arv23 *FDir)
{
	struct Arv23 *No;
	
	No = (struct Arv23 *) malloc(sizeof(struct Arv23));
	
	(*No).Info1 = valor;
	(*No).Info2 = 0;
	(*No).NInfos = 1;
	(*No).esq = FEsq;
	(*No).cen = FCen;
	(*No).dir = FDir;
	
return No;	
}

int ehFolha(struct Arv23 *R)
{   
    int folha = (R->cen == NULL && R->dir == NULL && R->esq == NULL); // não é folha
    return folha;
}

void adiciona(struct Arv23 **Raiz, int Valor, struct Arv23 *MaiorNo)
{
	if(Valor > (*Raiz)->Info1)
    { 
        (*Raiz)->Info2 = Valor;
        (*Raiz)->dir = MaiorNo;
    }	
	else {
		(*Raiz)->Info2 = (*Raiz)->Info1;
		(*Raiz)->Info1 = Valor;
		(*Raiz)->dir = (*Raiz)->cen;
		(*Raiz)->cen = MaiorNo;
	}
    (*Raiz)->NInfos = 2;
	
}

struct Arv23 *quebraNo(struct Arv23 **Raiz,int valor,int *sobe, struct Arv23 *MaiorNo)
{ 
    struct Arv23 *Novo;
        
    if(valor < (*Raiz)->Info1)
    {
        *sobe = (*Raiz)->Info1;
        Novo = criaNo((*Raiz)->Info2,(*Raiz)->cen,(*Raiz)->dir,NULL);
        (*Raiz)->Info1 = valor;
        (*Raiz)->cen = MaiorNo;

    }
    else if (valor < (*Raiz)->Info2) 	
    {
        *sobe = valor;
        Novo = criaNo((*Raiz)->Info2,MaiorNo,(*Raiz)->dir,NULL);
    }
    else{
        *sobe = (*Raiz)->Info2;
        Novo = criaNo(valor,(*Raiz)->dir,MaiorNo,NULL);
    }
    (*Raiz)->Info2 = 0;
    (*Raiz)->NInfos = 1;
    (*Raiz)->dir = NULL;

    return(Novo);	
}

struct Arv23 *insereArv23(struct Arv23 *Pai, struct Arv23 **Raiz, int valor, int *sobe)
{ 
    struct Arv23 *maiorNo;
	maiorNo = NULL;
	if(*Raiz == NULL)
		*Raiz = criaNo(valor,NULL,NULL,NULL);	
	else{ 
        if(ehFolha(*Raiz))
	    { 
            if((*Raiz)->NInfos == 1)
			{
				adiciona(Raiz,valor,maiorNo);
			}
			else // quando não tem espaço
			{ 
                struct Arv23 *novo;	
                novo=quebraNo(Raiz,valor,sobe,maiorNo);
                if(Pai == NULL)
                {   	
                    struct Arv23 *no;
                    no = criaNo(*sobe,*Raiz,novo,NULL);
                    *Raiz = no;
                }
                else maiorNo = novo;	
			}
		}
		else{//quando não é folha
            if(valor < (*Raiz)->Info1)
                maiorNo = insereArv23(*Raiz, &((*Raiz)->esq), valor,sobe);
            else if((*Raiz)->NInfos ==1 || (valor < (*Raiz)->Info2))
                maiorNo = insereArv23(*Raiz, &((*Raiz)->cen), valor,sobe);
            else 
                maiorNo = insereArv23(*Raiz, &((*Raiz)->dir), valor,sobe);	
            
            if(maiorNo != NULL)
            {
                if((*Raiz)->NInfos == 1)
                {
                    adiciona(Raiz,*sobe,maiorNo);
                    maiorNo = NULL;
                }
                else // quando não tem espaço
                {  
                    int sobe1;
                    struct Arv23 *novo;	
                    novo=quebraNo(Raiz,*sobe,&sobe1,maiorNo);
                    if(Pai == NULL)
                    {	
                        struct Arv23 *no;
                        no = criaNo(sobe1,*Raiz,novo,NULL);
                        *Raiz = no;
                        maiorNo = NULL;
                    }
                    else maiorNo = novo;
                }  
            }
        }
    }   
    return maiorNo;	
}

void mostra(Arv23 *tree){
    if(tree != NULL){
        mostra(tree->esq);
        printf("%d - ", tree->Info1);
        mostra(tree->cen);
        tree->Info2 == 0 ? 1 : printf("%d - ", tree->Info2);
        mostra(tree->dir);
    }
}
int busca(Arv23 *tree, int valor){
    int achou = 0;
    if(tree != NULL){
        if(tree->Info1 == valor || tree->Info2 == valor)
            achou = 1;
        else{
            if(tree->Info1 > valor)
                achou = busca(tree->esq, valor);
            else if(tree->Info1 < valor && tree->NInfos == 1)
                achou = busca(tree->cen, valor);
            else if(tree->NInfos == 2 && tree->Info2 < valor)
                achou = busca(tree->dir, valor);
            else if(tree->NInfos == 2 && (tree->Info1 < valor && tree->Info2 > valor))
                achou = busca(tree->cen, valor);   
        }
    }
    return achou;
}

int nivel(Arv23 *tree){
    int level = -1;
    if (tree != NULL){
        if(tree->esq != NULL){
            level = nivel(tree->esq);
        }
    }
    return level+1;
}

void nosFolhas(Arv23 *tree, int *folhas, int *quant){
    if(tree != NULL){
        if(ehFolha(tree)){
            *folhas = *folhas + 1;
            *quant += tree->NInfos;
        }
        else{
            nosFolhas(tree->esq, folhas, quant);
            nosFolhas(tree->cen, folhas, quant);
            nosFolhas(tree->dir, folhas, quant); 
        }
    }
}

void main()
{
    Arv23 *tree = NULL, *pai = NULL;
    int sobe = 0;
    
    insereArv23(pai, &tree, 50, &sobe);
    insereArv23(pai, &tree, 30, &sobe);
    insereArv23(pai, &tree, 40, &sobe);
    insereArv23(pai, &tree, 70, &sobe);
    insereArv23(pai, &tree, 55, &sobe);
    insereArv23(pai, &tree, 78, &sobe);
    insereArv23(pai, &tree, 51, &sobe);
    insereArv23(pai, &tree, 88, &sobe);
    insereArv23(pai, &tree, 29, &sobe);
    insereArv23(pai, &tree, 15, &sobe);
    insereArv23(pai, &tree, 99, &sobe);


    mostra(tree);
    printf("busca: %d\n", busca(tree, 10));
    printf("level: %d\n", nivel(tree));
    int folhas = 0, quant = 0;
    nosFolhas(tree, &folhas, &quant);
    printf("folhas: %d - quant: %d\n", folhas, quant);
}