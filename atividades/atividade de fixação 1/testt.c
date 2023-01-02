



void inter(int V1[TAM], int V2[TAM], int V3[TAM],int i, int j, int q1, int q2, int q3)
{
    if(i < q1 || j < q2)
    {
        if(V1[i] < V2[j])
            q3 = inter(V1,V2,V3, i, j+1,q1,q2,q3);
        else if(V1[i] > V2[j])
            inter(V1,V2,V3, i, j+1,q1,q2,q3);
        else {V3[q3] = V1[j];
            q3 = inter(V1,V2,V3,i+1,j+1,q1,q2,q3+1);
        }
    }
    return(q3);
}
void main()
{
    int v1[TAM] = {1,3,5,6,7}, v2[TAM] = {3,2,4,7,5};
    
    for(int i = 0; i < TAM; i ++){
        printf("%d - ", v1[i]);
    }printf("\n");
    
    for(int i = 0; i < TAM; i ++){
        printf("%d - ", v2[i]);
    }printf("\n");
    int v3[TAM], q3 = 0;
    inter(v1, v2, v3, 0, 0,TAM, TAM,q3);
    printf("\nq3: %d\n",q3);
    for(int i = 0; i < 3; i ++){
        printf("%d - ", v3[i]);
    }
}