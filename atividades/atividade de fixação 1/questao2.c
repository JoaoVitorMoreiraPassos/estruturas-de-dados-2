#include <stdio.h>
#include <string.h>
#define TAM 3

void misterio1(char b[TAM], float *dec, int p,
int i)
{
 printf("aqui\n");
 if(p < strlen(b))
 {
    if(b[p] == '1')
    {
        *dec = *dec + pow(2,i);
    }
    misterio1(b,dec,++p, --i);
 }
}


void main()
{
    char str[TAM] = {"10"};
    float dec = 0;
    int p = 0;
    misterio1(str, &dec,p, strlen(str)-1);
    printf("%.0f\n", dec);
}