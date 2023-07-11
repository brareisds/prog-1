#include <stdlib.h>
#define HORAS_DO_DIA 24
#define DIAS_DO_ANO 365

/* estrutura para representar uma data, composta por dia, mes e ano */
struct data {
	int dia;
	int mes;
	int ano;
};

/* estrutura para representar um compromisso, isto eh, uma data e uma hora */
struct compromisso {
	struct data data_compr;	/* dia, mes, ano */
	int hora_compr; /* hora do compromisso entre 0 e 23 */
};

/* estrutura para representar um dia do ano, composto por 24 horas */
struct dias {
	int horas[HORAS_DO_DIA];
};

/* estrutura para representar uma agenda de um dado ano, com 365 dias de 24 horas */
struct agenda {
	int ano;
	struct dias agenda_do_ano[DIAS_DO_ANO]; /* vetor agenda do ano, nao considerar ano bissexto */
};

/* funcao com implementacao dada pelos professores para calculo do dia do 
 * ano, que servira de indice para o vetor da agenda */
int obtemDiaDoAno(struct data d);

/* inicializa a agenda do ano corrente, onde cada hora de cada dia deve ter o 
 * valor 0 para indicar que nao ha um compromisso marcado. Retorna uma agenda
 * livre */ 
struct agenda criaAgenda(int ano);

/* le um compromisso passado pelo usuario, com data completa e hora pretendida. 
 * Cabe ao usuario desta funcao validar a data e hora do compromisso */
struct compromisso leCompromisso();

/* dado um compromisso, retorna a hora definida */
int obtemHora(struct compromisso compr);

/* retorna o ano atribuido a uma agenda criada */
int obtemAno(struct agenda ag);

/* Valida uma data lida do usuario; 
 * Retorna 1 se a data for valida e 0 caso contrario */
int validaData(struct data d, struct agenda ag);

/* Retorna 0 se data e horario já estiverem ocupados, 1 se data e horario
 * estiverem livres */
int verificaDisponibilidade(struct compromisso compr, struct agenda ag);

/* Dada uma agenda e um compromisso valido, isto eh, com data/hora validos, 
 * hora livre e dentro do ano da agenda, muda o valor da hora do compromisso
 * de 0 (livre) para 1 (ocupado). Retorna a nova agenda com o compromisso
 * marcado. */
struct agenda marcaCompromisso(struct agenda ag, struct compromisso compr);

/* mostra as datas e horas de todos os compromissos marcados na agenda */
void listaCompromissos(struct agenda ag);