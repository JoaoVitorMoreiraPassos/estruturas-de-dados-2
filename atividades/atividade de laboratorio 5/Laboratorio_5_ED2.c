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
    int folha = (R->cen == NULL && R->dir == NULL && R->esq == NULL);
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
    else
	{
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

void mostra(Arv23 *tree)
{
    if(tree != NULL)
	{
        mostra(tree->esq);
        printf("%d - ", tree->Info1);
        mostra(tree->cen);
        tree->Info2 == 0 ? 1 : printf("%d - ", tree->Info2);
        mostra(tree->dir);
    }
}
int busca(Arv23 *tree, int valor)
{
    int achou = 0;
    if(tree != NULL)
	{
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

void menorInfoDir(Arv23 *Raiz, Arv23 **no, Arv23 **paiNo)
{
	if (Raiz->esq != NULL)
	{
		*paiNo = Raiz;
		menorInfoDir(Raiz->esq, no, paiNo);
	}
	else
		*no = Raiz;
}

void maiorInfoEsq(Arv23 *Raiz, Arv23 **no, Arv23 **paiNo)
{
	if (Raiz->dir != NULL)
	{
		*paiNo = Raiz;
		maiorInfoEsq(Raiz->dir, no, paiNo);
	}
	else
		*no = Raiz;
}

int removerArv23(Arv23 **Pai, Arv23 **Raiz, int valor)
{
	int removeu = 0;
	Arv23 *no = NULL, *no1, *paiNo = NULL, *paiNo1 = NULL, **aux;
	aux = (Arv23 **)malloc(sizeof(Arv23 *));
	no1 = (Arv23 *)malloc(sizeof(Arv23));

	if (*Raiz != NULL)
	{
		if (ehFolha(*Raiz) == 1)
		{
			if ((*Raiz)->NInfos == 2)
			{
				if (valor == (*Raiz)->Info2)
				{ 
					(*Raiz)->Info2 = 0;
					(*Raiz)->NInfos = 1;
					removeu = 1;
				}
				else if (valor == (*Raiz)->Info1)
				{
					(*Raiz)->Info1 = (*Raiz)->Info2;
					(*Raiz)->Info2 = 0;
					(*Raiz)->NInfos = 1;
					removeu = 1;
				}
			}
			else if (valor == (*Raiz)->Info1)
			{
				if (*Pai == NULL)
				{
					free(*Raiz);
					*Raiz = NULL;
					removeu = 1;
				}
				else if (*Raiz == (*Pai)->esq)
				{
					(*Raiz)->Info1 = (*Pai)->Info1;
					paiNo = *Pai;
					menorInfoDir((*Pai)->cen, &no, &paiNo);
					(*Pai)->Info1 = no->Info1;
					removeu = 1;

					if (no->NInfos == 2)
					{
						no->Info1 = no->Info2;
						no->Info2 = 0;
						no->NInfos = 1;
					}
					else
					{
						if (paiNo->NInfos == 1)
						{
							(*Raiz)->Info2 = no->Info1;
							(*Raiz)->NInfos = 2;
							free(no);
							*Pai = *Raiz;
						}
						else
						{
							no->Info1 = paiNo->Info2;
							paiNo1 = paiNo;
							menorInfoDir(paiNo->dir, &no1, &paiNo1);
							paiNo->Info2 = no1->Info1;

							if (no1->NInfos == 2)
							{
								no1->Info1 = no1->Info2;
								no1->Info2 = 0;
								no1->NInfos = 1;
							}
							else
							{
								no->Info2 = paiNo->Info2;
								no->NInfos = 2;
								paiNo->Info2 = 0;
								paiNo->NInfos = 1;
								free(no1);
								paiNo1->dir = NULL;
							}
						}
					}
				}
				else if (*Raiz == (*Pai)->cen)
				{
					removeu = 1;
					if ((*Pai)->NInfos == 1)
					{
						if (((*Pai)->esq)->NInfos == 2)
						{
							(*Raiz)->Info1 = (*Pai)->Info1;
							(*Pai)->Info1 = ((*Pai)->esq)->Info2;
							((*Pai)->esq)->Info2 = 0;
							((*Pai)->esq)->NInfos = 1;
						}
						else
						{
							((*Pai)->esq)->Info2 = (*Pai)->Info1;
							free(*Raiz);
							((*Pai)->esq)->NInfos = 2;
							*aux = (*Pai)->esq;
							free(*Pai);
							*Pai = *aux;
						}
					}
					else
					{
						(*Raiz)->Info1 = (*Pai)->Info2;
						paiNo = *Pai;
						menorInfoDir((*Pai)->dir, &no, &paiNo);
						(*Pai)->Info2 = no->Info1;

						if (no->NInfos == 2)
						{
							no->Info1 = no->Info2;
							no->Info2 = 0;
							no->NInfos = 1;
						}
						else
						{
							(*Raiz)->NInfos = 2;
							(*Raiz)->Info2 = (*Pai)->Info2;
							(*Pai)->Info2 = 0;
							(*Pai)->NInfos = 1;
							free(no);
							(*Pai)->dir = NULL;
						}
					}
				}
				else
				{
					removeu = 1;
					paiNo = *Pai;
					maiorInfoEsq((*Pai)->cen, &no, &paiNo);

					if (no->NInfos == 1)
					{
						no->Info2 = (*Pai)->Info2;
						(*Pai)->Info2 = 0;
						(*Pai)->NInfos = 1;
						no->NInfos = 2;
						free(*Raiz);
						*Raiz = NULL;
					}
					else
					{
						(*Raiz)->Info1 = (*Pai)->Info2;
						(*Pai)->Info2 = no->Info2;
						no->Info2 = 0;
						no->NInfos = 1;
					}
				}
			}
		}
		else
		{
			if (valor < (*Raiz)->Info1)
				removeu = removerArv23(Raiz, &(*Raiz)->esq, valor);
			else if (valor == (*Raiz)->Info1)
			{
				paiNo = *Raiz;
				menorInfoDir((*Raiz)->cen, &no, &paiNo);
				(*Raiz)->Info1 = no->Info1;
				removerArv23(Raiz, &(*Raiz)->cen, (*Raiz)->Info1);
				removeu = 1;
			}
			else if (((*Raiz)->NInfos == 1) || (valor < (*Raiz)->Info2))
			{
				removeu = removerArv23(Raiz, &(*Raiz)->cen, valor);
			}
			else if (valor == (*Raiz)->Info2)
			{
				paiNo = *Pai;
				menorInfoDir((*Pai)->dir, &no, &paiNo);
				(*Raiz)->Info2 = no->Info1;
				removerArv23(Raiz, &(*Raiz)->dir, (*Raiz)->Info2);
				removeu = 1;
			}
			else
			{
				removeu = removerArv23(Raiz, &(*Raiz)->dir, valor);
			}
		}
	}
	return removeu;
}
void mostraArvore(Arv23* a, int b) {
    if (a == NULL) {
        imprimeNo(NULL, b);
        return;
    }
    mostraArvore(a->dir, b+1);
    imprimeNo(a->Info2, b);
    mostraArvore(a->cen, b+1);
    imprimeNo(a->Info1, b);
    mostraArvore(a->esq, b+1);
}


void imprimeNo(int c, int b) {
    int i;
    for (i = 0; i < b; i++) printf("     ");
        if(c == NULL)
            printf("NULL\n");
        else
            printf("%d\n", c);
}

int main()
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

	mostra(tree);printf("\n");
	printf("antes de remover: %d\n", busca(tree, 88));
    printf("removeu: %d\n",removerArv23(&pai, &tree, 88));
	printf("depois de remover: %d\n", busca(tree, 88));
	mostra(tree);

	return 0;
}