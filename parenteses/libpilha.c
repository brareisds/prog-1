/* 
 * Programa para testar a libpilha.
 * feito por Marcos Castilho em 05/04/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include "libpilha.h"
#define MAX 5

/* 
 * Cria e retorna uma nova pilha.
 * Retorna NULL em caso de erro de alocação.
*/
pilha_t *pilha_cria (){

    pilha_t *p;

    if(!(p = malloc(sizeof(pilha_t))))
        return NULL;
    
    p->topo = NULL;
    p->tamanho = 0;

    return p;

}

/* Desaloca toda memoria da pilha e faz pilha receber NULL. */
void pilha_destroi (pilha_t **pilha){

    nodo_t *aux;

    while((*pilha)->topo!=NULL){
        
        aux = (*pilha)->topo;
        (*pilha)->topo = aux->prox;
        free(aux);
    }

    free(*pilha);
    *pilha=NULL;

}
/* 
 * Insere dado na pilha (politica LIFO). Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int push (pilha_t *pilha, int dado){

    nodo_t *novo;

    if(!(novo = malloc(sizeof(nodo_t))))
      return 0;

    novo->dado = dado;
    
    novo->prox = pilha->topo;
    pilha->topo = novo; 
    pilha->tamanho++;
    
    return 1;

}

/* 
 * Remove o topo (politica LIFO) e retorna o elemento 
 * no parametro dado. A funcao retorna 1 em caso de 
 * sucesso e 0 no caso da pilha estar vazia.
*/
int pop (pilha_t *pilha, int *dado){

    nodo_t *aux;

    if(pilha_vazia(pilha))
        return 0;

    aux = pilha->topo;
    pilha->topo = aux->prox;
    *dado = aux->dado;
    pilha->tamanho--;

    free(aux); 
    return 1;

}
 
/* Similar ao pop, mas retorna o elemento dado sem remove-lo. */
int pilha_topo (pilha_t *pilha, int *dado){

    *dado = pilha->topo->dado;
    return *dado;

}


/* Retorna o numero de elementos da pilha, que pode ser 0. */
int pilha_tamanho (pilha_t *pilha){

    return pilha->tamanho;

}

/* Retorna 1 se pilha vazia, 0 em caso contrario. */ 
int pilha_vazia (pilha_t *pilha){

    /*se o tamanho da pilha for 0
    * a pilha esta vazia*/
    if(pilha_tamanho(pilha)==0)
        return 1;
    
    return 0;
}