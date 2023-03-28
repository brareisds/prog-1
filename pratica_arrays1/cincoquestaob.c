#include <stdio.h>
#define MAX 1024
int v[MAX], w[MAX]; // por quê?

    int main() {

        int n,j,tam,soma;
        printf("Digite o tamanho do vetor:\n");
        scanf("%d",&n);

        while(n>MAX) {
            printf("Digite outro valor. Tamanho máximo %d\n", MAX);
            scanf("%d",&n);   
        }

    for(int i = 0; i<n; i++) {
        printf("Digite o valor de v[%d]:\n",i);
        scanf("%d",&v[i]);
    }
    

    tam = n-1; /*lembrar do -1!!!!!*/
    for(int j = 0; j<n; j++) {
        w[j] = v[tam];
        tam = tam-1;
    }

    soma=0;
    for(j=0; j<n; j++) {
        soma = soma + w[j];
    }

    printf("A soma dos elementos do vetor é: %d\n",soma);

}