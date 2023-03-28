#include <stdio.h>
#define MAX 1024
int v[MAX]; // por quê?

    int main() {

        int n, tam;
        printf("Digite o tamanho do vetor:\n");
        scanf("%d",&n);

        while(n>MAX) {
            printf("Digite outro valor. Tamanho máximo %d\n", MAX);
            scanf("%d",&n);   
        }

    tam = n-1;
    for(int i = 0; i<n; i++) {
        v[i] = tam;
        tam = tam - 1;
        printf("v[%d]: %d\n", i, v[i]);
    }

}