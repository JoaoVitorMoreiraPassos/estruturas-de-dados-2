#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ehConsoante(char c)
{
    return (c != 'a' && c !='e' && c !='i' && c!='o' && c!='u' && c != 'A' && c !='E' && c !='I' && c!='O' && c!='U');
}
int ehVogalMaiscula(char c)
{
    return (c == 'A' || c =='E' || c =='I' || c=='O' || c=='U');
}

char ** lerStrings()
{   
    char **strs = (char **) malloc(sizeof(char));
    char temp[20];
    int control, q = 0;
    do
    {
        printf("digite uma string: ");
        scanf(" %[^\n]s", temp);

        strs = (char **) realloc(strs, (q+1)*sizeof(char*));
        *(strs+q) = (char *) malloc(sizeof(char)*strlen(temp));

        strcpy(*(strs+q), temp);
        q ++;
        
        printf("String adicionada!\n");
        printf("---------------------------\n");
        printf("deseja continuar?[1/0]: ");
        // scanf("%d",&control);
        printf("contrl: %d\n", control); 
    }while(control != 0);
    printf("--------------------------\n");
    *(strs+q) = NULL;
    
    return strs;
}

char * letraA(char **strs, char *menor)
{
    if(*(strs) !=  NULL)
    {
        if(strlen(menor) == strlen(*(strs))){
            if(strcmp(menor, *(strs)) == 1)
                menor = letraA(strs+1, *strs);
            else
                menor = letraA(strs+1, menor);
        }
        else if(strlen(menor) > strlen(*(strs)))
            menor =  letraA(strs+1, *strs);
        else
            menor =  letraA(strs+1, menor);
    }
    return menor;
}

void letraB(char **strs, int *q)
{
    if(*(strs) != NULL)
    {
        if(ehConsoante(*(strs)[0]))
        {
            ++ *q;
            letraB(strs+1, q);
        }else
            letraB(strs+1, q);
    }
}

char **letraC(char **strs,char **new_strs, int *q)
{
    if(*(strs) != NULL)
    {
        if(strlen(*(strs)) <= 6 && ehVogalMaiscula(*(strs)[0]))
        {
            if(q == 0)
            {
                *new_strs = (char *) malloc(sizeof(char)); 
                strcpy(*new_strs, *(strs));
                ++ *q;
                letraC(strs+1, new_strs ,q);
            }else
            {
                *(new_strs+*q) = (char *) malloc(sizeof(char));
                strcpy(*(new_strs+*q), *(strs));
                ++ *q;
                letraC(strs+1, new_strs, q);
            }
        }else{
            letraC(strs+1, new_strs, q);
        }
    }  
}

void main()
{
    int i;
    char **strs = lerStrings();
    for(int i = 0; *(strs+i) != NULL; i ++)printf("%s - ", *(strs+i));
    printf("\n--------------------------\n");

    // letra a)
        char *menor;
        menor = letraA(strs, *strs);
        printf("menor: %s\n",menor);
        printf("--------------------------\n");
    // letra b)
        int comecam_com_consoante = 0;
        letraB(strs, &comecam_com_consoante);
        printf("Comecam com consoante: %d\n", comecam_com_consoante);
        printf("--------------------------\n");
    // letra c)
        char **new_matriz = (char **) malloc(sizeof(char *));
        int q = 0;
        letraC(strs, new_matriz,&q);
        printf("Tamanho menor que 6 e inicial vogal minuscula: \n");
        for(i = 0; i < q; i ++)
            printf("--> %d: %s\n",i+1,new_matriz[i]);
}
