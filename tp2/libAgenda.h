#define HORAS_DO_DIA 24
#define MESES_NO_ANO 12
#define DIAS_DO_ANO 365

/* Estrutura para representar uma data, composta por dia, mes e ano 
 * 1 <= dia <= DIAS_DO_ANO
 * 1 <= mes <= MESES_NO_ANO
 * ano eh um inteiro qualquer */
struct data {
	int dia;
	int mes;
	int ano;
};

/* Estrutura para representar um compromisso, isto eh, uma data e uma hora */
struct compromisso {
	struct data data_compr;	/* dia, mes, ano */
	int hora_compr;         /* hora do compromisso entre 0 e 23 */
};

/* Estrutura para representar um dia do ano, composto por 24 horas */
struct dias {
	int horas[HORAS_DO_DIA];
};

/* Estrutura para representar uma agenda de um dado ano, 
 * com 365 dias de 24 horas, nao considerar anos bissestos */
struct agenda {
	int ano;
	struct dias agenda_do_ano[DIAS_DO_ANO]; /* vetor agenda do ano */
};

/* Inicializa a agenda do ano corrente, onde cada hora de cada dia deve ter o 
 * valor 0 para indicar que nao ha um compromisso marcado. 
 * Retorna uma agenda livre */
struct agenda criaAgenda(int ano);

/* Funcao para calculo do dia do ano, que sera o indice para o vetor da agenda
 * O codigo sera fornecido pelos professores e nao devera ser alterado.
 * Obs: o codigo fornecido para o tp2 eh diferente do fornecido no tp1! */
int obtemDiaDoAno(struct data d);

/* Dado um compromisso, retorna a hora definida */
int obtemHora(struct compromisso *compr);

/* Retorna o ano atribuido a uma agenda criada */
int obtemAno(struct agenda *ag);

/* Le um compromisso do teclado (dia, mes, ano e hora, nesta ordem) 
 * Devolve o compromisso no parametro e retorna 1 se o compromisso
 * eh valido ou 0 caso contrario */
int leCompromisso(struct agenda *ag, struct compromisso *compr);

/* Valida um data lida do usuario; 
 * Retorna 1 se a data for valida e 0 caso contrario */
int validaData(struct agenda *ag, struct data *d);

/* Valida uma hora lida do usuario; 
 * Retorna 1 se a hora for valida e 0 caso contrario */
int validaHora(struct compromisso *compr);

/* Retorna 0 se data e horario já estiverem ocupados, ou 1 caso contrario */
int verificaDisponibilidade(struct agenda *ag, struct compromisso *compr);

/* Esta funcao considera que o comprimisso eh valido e a agenda esta livre
 * para da data/hora fornecidos, portanto quem chama esta funcao tem que
 * garantir estas informacoes. Portanto, a funcao simplesmente muda o valor
 * da hora do compromisso de livre para ocupado */
void marcaCompromisso(struct agenda *ag, struct compromisso *compr);

/* Mostra as datas e horas de todos os compromissos marcados na agenda.
 * Se a agenda nao tiver compromissos agendados nao imprime nada */
void listaCompromissos(struct agenda *ag);