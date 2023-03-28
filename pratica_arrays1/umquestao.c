#include <stdio.h>
#define MAX 1024
int v[MAX]; // por quê?

    int main() {

        int n;
        printf("Digite o tamanho do vetor:\n");
        scanf("%d",&n);

        while(n>MAX) {
            printf("Digite outro valor. Tamanho máximo %d\n", MAX);
            scanf("%d",&n);   
        }
    
    for(int i = 0; i<n; i++) {
        v[i] = i;
        printf("v[%d]: %d\n", i, v[i]);
    }

}