/* 
 * Programa para testar a libpilha.
 * feito por Marcos Castilho em 05/04/2022
*/

#include <stdio.h>
#include "libpilha.h"
#define MAX 5

pilha_t* teste_criar_pilha ()
{
    pilha_t* p;

    if (! (p = pilha_cria ()))
        fprintf (stderr, "Falha na alocacao da pilha\n");

    printf ("\tPilha criada com sucesso\n");
    return p;
}

void teste_pilha_vazia (pilha_t* p)
{
    if (pilha_vazia (p))
        printf ("\tpilha esta vazia");
    else
        printf ("\tpilha nao esta vazia");
    printf (", seu tamanho eh %d.\n", pilha_tamanho (p));
}

void teste_push (pilha_t* p, int limite)
{
    int i, dado;

    for (i=1; i <= limite; i++)
    {
        printf ("\tEmpilhando %d", i + 10);
        if (! push (p, i + 10)){
            printf ("Pilha cheia, nao inseriu.\n");
            return;
        }
        if (pilha_topo (p, &dado))
            printf ("\tTopo = %d\n", dado);
    }
}

void teste_pop_e_topo (pilha_t* p)
{
    int dado;

    /* remove todo mundo */
    while (! pilha_vazia (p))
    {
        if (pilha_topo (p, &dado))
            printf ("\tTopo = %d, ", dado);
        if (pop (p, &dado))
            printf ("removeu %d\n", dado);
    }
}

int main (void)
{
    pilha_t *p;
    int dado;

    printf ("Teste 1: criar pilha e ver se esta vazia:\n");
    printf ("Esperado: tem que dar pilha vazia com tamanho zero\n");
    p= teste_criar_pilha ();
    teste_pilha_vazia (p);
    printf ("\n\n");

    printf ("Teste 2: tenta desempilhar elemento com pilha vazia:\n");
    printf ("Esperado: nao pode ter dado segfault\n");
    if (! pop (p, &dado))
        printf ("\tOK: pop na pilha vazia nao deu segfault.\n");
    printf ("\n\n");

    printf ("Teste 3: inserir 5 elementos:\n");
    printf ("Esperado: tem que mostrar empilhar de 11 ate 15\n");
    printf ("          o tamanho tem que terminar com valor 5\n");
    printf ("          E a pilha NAO PODE estar vazia\n");
    teste_push (p, MAX); 
    teste_pilha_vazia (p);
    printf ("\n\n");

    printf ("Teste 4: esvaziar a pilha:\n");
    printf ("Esperado: tem que mostrar desempilhar de 15 ate 11\n");
    printf ("          o tamanho tem que terminar com valor 0\n");
    printf ("          E a pilha tem que estar vazia\n");
    teste_pop_e_topo (p); 
    teste_pilha_vazia (p);
    printf ("\n\n");

    printf ("Teste 5: destruir uma pilha vazia:\n");
    printf ("Esperado: nao pode ter leak (conferir com valdrind)\n");
    printf ("          E nao pode ter segfault\n");
    pilha_destroi (&p);
    printf ("\n\n");

    printf ("Teste 6: destruir uma pilha com elementos:\n");
    printf ("Esperado: nao pode ter leak (conferir com valdrind)\n");
    printf ("          E nao pode ter segfault\n");
    p = pilha_cria ();
    if (push (p, 1) && push (p, 2) && push (p, 3))
        pilha_destroi (&p);
    else
        printf ("Falha na alocação dos elementos!!!");
    printf ("\n\n");

    return 0;
}
