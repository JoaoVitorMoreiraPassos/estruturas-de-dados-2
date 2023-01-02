

// void mostraArvore(Bt* a, int b) {
//     if (a == NULL) {
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
// int letraB(Bt **bt)
// {
//     int len = 0;
//     if (*bt != NULL)
//     {
//         len += letraB(&(*bt)->esq);
//         len += letraB(&(*bt)->dir);
//         len ++;
//     }
//     return len;
// }