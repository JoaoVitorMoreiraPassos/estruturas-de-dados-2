#include <stdio.h>
#include <string.h>

void main()
{
    char *s1 = {"str"};
    char *s2 = {"caractere"};
    printf("s1: %d, s2: %d\n", strlen(s1), strlen(s2));
    if(strcmp(s1, s2) == 1){
        printf("aqui\n");
    }
}