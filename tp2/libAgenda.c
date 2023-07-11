#include <stdio.h>
#include <time.h>
#include "libAgenda.h"

#define LIVRE 0
#define OCUPADA 1

struct agenda criaAgenda(int ano)
{
    int dia,hr;
    struct agenda agVazia;
    agVazia.ano = ano;

   for(dia = 0; dia < DIAS_DO_ANO; dia++)
        for(hr = 0; hr < HORAS_DO_DIA; hr++)
            agVazia.agenda_do_ano[dia].horas[hr] = LIVRE;

    return agVazia; 

}

int obtemDiaDoAno(struct data d)
{
    struct tm tipodata={0};
    time_t segundos;
    int dia_do_ano;

    tipodata.tm_mday = d.dia;
    tipodata.tm_mon = d.mes - 1;
    tipodata.tm_year = d.ano - 1900;
    tipodata.tm_isdst = -1;
    tipodata.tm_hour = 0;

    /* converte data para epoca, isto eh, segundos desde 1970 */
    segundos = mktime(&tipodata);

    /* converte epoca em data, obtendo assim automaticamente
     * o campo 'dia do ano' (tm_yday) que sera o indice do
     * vetor necessario para marcar um compromisso */
    tipodata = *localtime(&segundos);

    /* da reconversao da data, obtem o dia do ano, um numero
     * entre 0 e 364 */
    dia_do_ano = tipodata.tm_yday;

    return dia_do_ano;

}

/* Dado um compromisso, retorna a hora definida */
int obtemHora(struct compromisso *compr)
{
    return compr->hora_compr;

}

/* Retorna o ano atribuido a uma agenda criada */
int obtemAno(struct agenda *ag)
{
    return ag->ano;

}

/*le o dia, mes, ano e hora do compromisso.
* Retorna 1 se o mesmo for valido e 0 caso contrario*/
int leCompromisso(struct agenda *ag, struct compromisso *compr)
{
	scanf("%d ",&compr->data_compr.dia);
    scanf("%d ",&compr->data_compr.mes);
    scanf("%d ",&compr->data_compr.ano);
    scanf("%d",&compr->hora_compr);
    
    if(!validaData(ag,&compr->data_compr) || !validaHora(compr)) 
        return 0;
    
    return 1;
	
}

/* Valida uma data lida do usuario; 
* Retorna 1 se a data for valida e 0 caso contrario */
int validaData(struct agenda *ag, struct data *d)
{
    /*cada indice representa o mes e guarda a quant. de dias do mesmo*/
    int meses[MESES_NO_ANO] = {31,28,31,30,31,30,31,31,30,31,30,31};
	
	if(obtemAno(ag) == d->ano && d->mes >= 1 && 
    d->mes <= MESES_NO_ANO && d->dia >= 1 && 
    d->dia <= meses[d->mes-1]) 
        return 1; 

    return 0;

}

/* Valida uma hora lida do usuario; 
 * Retorna 1 se a hora for valida e 0 caso contrario */
int validaHora(struct compromisso *compr)
{
    int hr;
    hr = obtemHora(compr);
 
    if (hr < 0 || hr > 23)
        return 0;

    return 1;

}

/* Retorna 0 se data e horario já estiverem ocupados, ou 1 caso contrario */
int verificaDisponibilidade(struct agenda *ag, struct compromisso *compr)
{
    int dia,hr; 

    /*obtem um numero entre 0 e 364 para indice 
    * do vetor agenda_do_ano*/
    dia = obtemDiaDoAno(compr->data_compr);
    hr = obtemHora(compr); 
    
    if(!ag->agenda_do_ano[dia].horas[hr]) 
        return 1;

    return 0;

}

/*atribui o valor 1 no dia e na hora do compromisso*/
void marcaCompromisso(struct agenda *ag, struct compromisso *compr)
{
    int dia,hr; 

    /*obtem um numero entre 0 e 364 para indice 
    * do vetor agenda_do_ano*/
    dia = obtemDiaDoAno(compr->data_compr);
    hr = obtemHora(compr); 
   
    ag->agenda_do_ano[dia].horas[hr] = OCUPADA; 
	printf("Compromisso inserido com sucesso!\n");

}

/* Mostra as datas e horas de todos os compromissos marcados na agenda.
 * Se a agenda nao tiver compromissos agendados nao imprime nada */
void listaCompromissos(struct agenda *ag)
{
    int dia,hr;

    for(dia = 0; dia < DIAS_DO_ANO; dia++)
        for(hr = 0; hr < HORAS_DO_DIA; hr++)
            if(ag->agenda_do_ano[dia].horas[hr]){
                printf ("dia: %3d, ", dia);
                printf ("ano: %4d, ", obtemAno(ag));
                printf ("hora: %2d, compromisso!\n", hr);
            }
    
}