#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "libAgenda.h"
#define HORAS_DO_DIA 24
#define DIAS_DO_ANO 365

/* função com implementação dada pelos professores para cálculo do dia do 
 * ano, que servirá de índice para o vetor da agenda */
int obtemDiaDoAno(struct data d) {
	struct tm tipodata;
	time_t segundos;
	int dia_do_ano;

	tipodata.tm_mday = d.dia;
    tipodata.tm_mon = d.mes-1;
    tipodata.tm_year = d.ano-1900;
    tipodata.tm_isdst = -1;
	tipodata.tm_hour = 0;

	/* converte data para época, isto é, segundos desde 1970 */
	segundos = mktime(&tipodata);
	/* converte época em data, obtendo assim automaticamente
	 * o campo 'dia do ano' (tm_yday) que será o índice do
	 * vetor necessário para marcar um compromisso */
	tipodata = *localtime(&segundos);
	/* da reconversão da data, obtém o dia do ano, um número
	 * entre 0 e 364 */
    dia_do_ano = tipodata.tm_yday;
	
	return dia_do_ano;
}

/* inicializa a agenda do ano corrente, onde cada hora de cada dia deve ter o 
 * valor 0 para indicar que não há um compromisso marcado. Retorna uma agenda
 * livre */ 
struct agenda criaAgenda(int ano){
    int i,j;
     
    struct agenda agVazia;
    agVazia.ano = ano;

   for(i=0; i < DIAS_DO_ANO; i++){
        for(j = 0; j < HORAS_DO_DIA; j++){
            agVazia.agenda_do_ano[i].horas[j]= 0;
        }
    }

    return agVazia; 
}

/* lê um compromisso passado pelo usuário, com data completa e hora pretendida. */
struct compromisso leCompromisso(){

	struct compromisso compr;

	printf("Digite a data (dia, mes e ano) e a hora do seu compromisso:\n");
	scanf("%d %d %d %d",&compr.data_compr.dia, &compr.data_compr.mes, &compr.data_compr.ano, &compr.hora_compr);

	return compr;
}

/* dado um compromisso, retorna a hora definida */
int obtemHora(struct compromisso compr){

	return compr.hora_compr;

}

/* retorna o ano atribuído a uma agenda criada */
int obtemAno(struct agenda ag){

	return ag.ano; 

}

/* Valida uma data lida do usuário; 
 Retorna 0 se a data for inválida */
int validaData(struct data d, struct agenda ag){

	int meses[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; /*vetor com as quantidades dos dias de cada mes, com cada indice representando o (mes-1) desejado*/
	
	if(obtemAno(ag) == d.ano){ /*verifica se o ano do compromisso eh o mesmo da agenda*/
        if(d.mes<=12){ /*verifica se o mes eh valido*/
		    if(d.dia <= meses[d.mes-1]){/*verifica se a quantidade de dias do mes é valido*/
				return 1; 
			}

		}
	}

	return 0;


}

/* Retorna 0 se data e horário já estiverem ocupados, 1 se data e horário
 * estiverem livres */
int verificaDisponibilidade(struct compromisso compr, struct agenda ag){

    int HrCompr; 
    HrCompr = obtemHora(compr); /*variavel que armazena a hora do compromisso do usuario*/
    
    if(ag.agenda_do_ano[obtemDiaDoAno(compr.data_compr)].horas[HrCompr] == 0){ /*verifica se a data no horario esta vazia*/
    
        return 1;
    } 
    return 0;
}

/* Dada uma agenda e um compromisso válido, isto é, com data/hora válidos, 
 * hora livre e dentro do ano da agenda, muda o valor da hora do compromisso
 * de 0 (livre) para 1 (ocupado). Retorna a nova agenda com o compromisso
 * marcado. */
struct agenda marcaCompromisso(struct agenda ag, struct compromisso compr){

    int HrCompr;
    HrCompr = obtemHora(compr);

    if (HrCompr >= 0 && HrCompr <= 23){ /*valida o horario e verifica se a data e o horario estao ocupados, se não estiver marca o compromisso*/
        ag.agenda_do_ano[obtemDiaDoAno(compr.data_compr)].horas[HrCompr] = 1;  /*se o horario estiver valido marca o compromisso*/
		printf("Compromisso inserido com sucesso!\n");
    } 
    else 
        printf("Hora invalida, compromisso nao inserido\n");

    return ag;

}
// verificar aqui se a hora ta correta usa obtem hora
// se a hora nao estiver correta retornar falando que esta invalida 
/* mostra as datas e horas de todos os compromissos marcados na agenda */
void listaCompromissos(struct agenda ag){

    int i,j, PossuiCompr;

    PossuiCompr = 0; /*indica se agenda esta vazia no final*/

    for(i=0; i < DIAS_DO_ANO; i++){
        for(j = 0; j < HORAS_DO_DIA; j++){
            if(ag.agenda_do_ano[i].horas[j] == 1){
                printf("dia: %d, ano: %d, hora %d, compromisso!\n", i, ag.ano, j);
                PossuiCompr = 1; /*indica que há compromissos marcados na agenda*/
            }
        }
    }

    if(PossuiCompr == 0){ /*verifica se há compromissos marcados na agenda, caso nao exista imprime a mensagem*/
        printf("Voce nao possui nenhum compromisso valido\n");
    }

}

