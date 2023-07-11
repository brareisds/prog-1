#include <stdio.h>
#include "libpilha.h"
#define TAM 100

int abre_parenteses(char ch)
{
    if(ch == '(')
        return 1;

    return 0;
}

int abre_chaves(char ch)
{
    if(ch == '{')
        return 1;

    return 0;
}

int abre_colchetes(char ch)
{
    if(ch == '[')
        return 1;

    return 0;
}

int eh_fechado(char ch)
{
    if(ch == ')' || ch == '}' || ch == ']')
        return 1;

    return 0;
}

/* Verifica se o caracter de fechamento eh  
 * compativel com o dado no topo da pilha. */
int eh_compativel(int topo, char fechado)
{
    switch (fechado)
    {
        case ')':
            if(topo == 1)
                return 1;
            else
                return 0;
            break;
        case ']':
            if(topo == 2)
                return 1;
            else
                return 0;
            break; 
        case '}': 
            if (topo == 3)
                return 1;
            else    
                return 0;
            break;

        default:
            return 0;
    }        
}



int main()
{
    pilha_t *p;  
    char string[TAM];
    int i, topo, bem_formada;

    fgets(string, TAM, stdin);
    p = pilha_cria (); 
    
    /* 
     * bem_formada trata os casos em que a pilha 
     * termina vazia porem eh mal formada e termina 
     * o laco quando encontra incompatibilidade. 
     */
    bem_formada = 1;
    i = 0;

    while(string[i] != '\0' && bem_formada)
    {
        if(abre_parenteses(string[i]))
            push(p,1);
        else if (abre_colchetes(string[i]))
            push(p,2);
        else if (abre_chaves(string[i]))
            push(p,3);                    
        else if ((eh_fechado(string[i])))
        {
            /*Caso em que a pilha nao esta vazia e o dado eh incompativel.*/
            if(!(pilha_vazia(p)))
            {
                pop(p,&topo); 
                if(!(eh_compativel(topo, string[i]))) 
                   bem_formada = 0;     
            } 
            else
                /*Caso em que a pilha esta vazia e recebeu um char de fechamento.*/
                bem_formada = 0; 
        }
        i++;
    }

    if (!(pilha_vazia(p)) || !bem_formada)
        printf("INCORRETA\n");
    else
        printf("CORRETA\n");

    pilha_destroi(&p);

    return 0;
}