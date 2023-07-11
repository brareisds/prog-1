#include <stdio.h>
#include "libAgenda.h"

int main()
{
    struct agenda ag;
    struct compromisso compr;
	char ch; 
    int ano;

    /*cria uma agenda ag com o ano passado pelo usuario
    * e zera o vetor agenda_do_ano*/
    scanf("%d", &ano); 
    ag = criaAgenda(ano); 
    
    do
    {
        /*retorna o compromisso e valida sua data e hora*/
        if (leCompromisso(&ag,&compr)) 
            if(verificaDisponibilidade(&ag,&compr))
                marcaCompromisso(&ag,&compr);
            else
                printf("Data/Hora ocupada, compromisso nao inserido\n");
        else
            printf("Data e/ou hora invalidos, compromisso nao inserido\n");

        scanf(" %c", &ch); 
    } 
    while (ch != 's');

    listaCompromissos(&ag);

    return 0;

}