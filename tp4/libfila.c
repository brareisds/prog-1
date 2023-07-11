#include <stdlib.h>
#include "libfila.h"

/* 
 * Cria e retorna uma nova fila.
 * Retorna NULL em caso de erro de alocação.
*/
fila_t *fila_cria ()
{
    fila_t *f;

    if(!(f=malloc(sizeof(fila_t))))
        return NULL;
    
    f->cabeca = NULL;
    f->cauda = NULL;
    f->tamanho = 0;
    
    return f;
}

/* Desaloca toda memoria da fila e faz fila receber NULL. */
void fila_destroi (fila_t **fila)
{
    nodo_t *aux;

    while((*fila)->cabeca)
    {
        aux = (*fila)->cabeca;
        (*fila)->cabeca = aux->prox;
        free(aux);
    }

    free(*fila);
    (*fila) = NULL;
}

/* 
 * Insere dado no final da fila (politica FIFO). Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int enqueue (fila_t *fila, int dado){

    nodo_t *novo;

    if(!(novo=malloc(sizeof(nodo_t))))
        return 0;

    novo->dado = dado;
    novo->prox = NULL;

    /* Se a fila estiver vazia, a cabeca e a cauda 
     apontarão para o novo nodo.*/
    if(fila_vazia(fila))
    {
        fila->cabeca = novo;
        fila->cauda = novo;
        fila->tamanho++;

        return 1;
    }

    /* Caso contrario, o novo nodo eh inserido apos o ultimo nodo e somente 
     o ponteiro da cauda eh atualizado para o final da fila*/
    fila->cauda->prox = novo;
    fila->cauda = novo; 
    fila->tamanho++;
 
    return 1;
}

/* 
 * Remove o elemento do inicio da fila (politica FIFO) e o retorna
 * no parametro dado. Retorna 1 em caso de sucesso e 0 no caso da fila estar vazia.
*/
int dequeue (fila_t *fila, int *dado)
{
    nodo_t *aux;

    if(fila_vazia(fila))
        return 0; 

    /* Antes de dar free no aux que armazena o primeiro nodo que sera removido da fila,
      o inicio da mesma eh atualizado para o nodo seguinte e o dado eh guardado */
    aux = fila->cabeca;
    *dado = aux->dado;
    fila->cabeca = aux->prox;
    fila->tamanho--;

    free(aux);

    return 1;

}

/* Retorna o numero de elementos da fila */
int fila_tamanho (fila_t *fila)
{
    return fila->tamanho;
}

/* Retorna 1 se fila vazia, 0 em caso contrario. */ 
int fila_vazia (fila_t *fila){

    if(fila_tamanho(fila)==0)
        return 1;

    return 0;
}