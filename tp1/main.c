#include "libAgenda.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



int main(){

    struct agenda ag;
    struct compromisso compr;
	char ch; 
    int ano;


    printf("Digite o ano da sua agenda\n");
    scanf("%d", &ano);

    ag = criaAgenda(ano); /*cria uma agenda ag com o membro do ano preenchido pelo user e com o vetor agenda_do_ano zerado*/

    do
    {
        compr = leCompromisso(); /*preenche a data e a hora do compromisso do usuario na struct compromisso compr*/

        if(validaData(compr.data_compr,ag)) { /*verifica se a data do compromisso é valida e se o ano é compativel com o da agenda*/
            if(verificaDisponibilidade(compr, ag)) /*verifica se o campo que representa a data e hora na agenda esta vazio*/
                ag = marcaCompromisso(ag,compr); /*se a data estiver valida e disponivel marca o compromisso*/
            else
                printf("Horario nao disponivel, compromisso nao inserido\n");
        }
        else 
			printf("Data invalida, compromisso nao inserido\n");

		
        printf("\n");
		printf("Digite c para continuar ou s para listar os compromissos da agenda:\n");
        scanf(" %c", &ch);
        printf("\n");


    } while (ch != 's');

    listaCompromissos(ag);

    return 0;
}
