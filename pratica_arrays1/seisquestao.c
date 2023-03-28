#include <stdio.h>
#define MAX 1024
int v[MAX], w[MAX], m[MAX]; // por quê?

    int main() {

        int i,n,j,K, tam,maior,menor;
    

        printf("Digite o tamanho do vetor:\n");
        scanf("%d",&n);

        while(n>MAX) {
            printf("Digite outro valor. Tamanho máximo %d\n", MAX);
            scanf("%d",&n);   
        }

    printf("Primeiro vetor\n");
    for(int i = 0; i<n; i++) {
        printf("Digite o valor de v[%d]:\n",i);
        scanf("%d",&v[i]);
    }
    
    printf ("Segundo vetor\n");
     for(i = 0; i<n; i++) {
        printf("Digite o valor de w[%d]:\n",i);
        scanf("%d",&w[i]);
    }

    i = 0;
    for(int k = 0; k<n; k++) {
        m[k] = v[i] * w[i]; // teste
        i = i+1;
    }

    i = 0;
    for(int k = 0; k<n; k++) {
        printf("m[%d]: %d\n", k, m[k]);
        printf("A multiplicação de %d por %d é: %d\n", v[i], w[i], m[k]);
        i = i +1;

    }
}