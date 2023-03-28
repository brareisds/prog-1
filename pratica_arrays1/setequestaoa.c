#include <stdio.h>
#define MAX 1024
int v[MAX]; // por quê?

int main() {

    int i,n, quant;
    

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

    for(int i = 0; i<n; i++) {
        printf("v[%d]: %d\n",i, v[i]);
    }

    quant = 0;
    for(int i = 0; i<n; i++){

        for(int j = i+1; j<n; j++){
            if(v[i] == v[j]) {
                quant++;
            } else
        }

    printf("O elemento %d apareceu %d vezes\n", v[i], quant);
    }


}