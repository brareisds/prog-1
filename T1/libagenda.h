/*
 * TAD agenda
 * Autor:
 *    Luis Carlos Erpen de Bona
 *
 * Versao 1.0.1 de 01/06/2023
*/

/* Lista de compromissos:
   Os membros inicio e fim sao respectivamente o tempo inicial e final do
   compromisso em minutos a partir das zero horas do dia. A lista de 
   compromissos eh ordenada pelo tempo inicio e eh implementada
   como uma lista ligada simples, tendo somente apontador para proximo. */

typedef struct compromisso {
	int id;
	char* descricao;
	int inicio; 
	int fim;   
	struct compromisso *prox;
} compromisso_t;

/* Lista de dias:
   O membro comprs aponta para o inicio da lista de compromissos.
   A lista de dias eh ordenada pelo dia, somente dias que tenham
   compromissos devem ser alocados na lista, que tambem eh implementada
   como uma lista ligada simples com apontador somente para o proximo. */

typedef struct dia {
	int dia; 
	compromisso_t *comprs;
	struct dia *prox; 
} dia_t;

/* Lista de meses:
   A lista de meses eh uma lista circular duplamente encadeada. 

   Na criacao da agenda a lista de meses possui apenas o mes 1, ao mudar de
   mes na agenda (funcoes prox_mes_agenda ou ant_mes_agenda) eh que os meses
   podem ser criados. 

   As insercoes na Lista de meses somente ocorrem quando andamos na agenda para 
   o proximo (ou anterior) mes. Alem disso a agenda nao aponta para um primeiro 
   mes, mas para um mes_atual (ptr_mes_atual), por isso o uso de sentinela na
   implementacao pode ser desnecessario. Voce pode implementar como achar melhor.
*/  

typedef struct mes {
	int mes;  /* mes representado */
	dia_t *dias;
	struct mes *prox;
	struct mes *ant;
} mes_t;

/* Agenda:
   O membro mes_atual armazena o mes_atual da agenda (inteiro entre 1 e 12),
   o membro ptr_mes_atual aponta para o mes corrente na Lista de meses, a ideia 
   eh representar um calendario onde cada "pagina" representa um mes.
   Por simplificacao vamos assumir que todos os meses tem 31 dias. */

typedef struct agenda {
	mes_t *ptr_mes_atual;
	int mes_atual;
} agenda_t;

/* Cria uma agenda vazia:
   O mes_atual deve ser inicializado com 1; ptr_mes_atual deve ser definido. */
agenda_t* cria_agenda();

/* Horario de um compromisso:
   Estrutura para armazenar inicio e fim de compromisso no formato hora/minuto.
   Representa a faixa de horario de um compromisso, com inicio e fim de hora e
   inicio e fim de mes */

typedef struct horario_compromisso {
	int ini_h;
	int ini_m; 
	int fim_h; 
	int fim_m;
} horario_compromisso_t;

/* Cria um compromisso:
   Retorna um compromisso com as informacoes de data de hc, um identificador
   id e uma string de descricao. A funcao deve alocar um novo espaco de 
   armazenamento para receber a string descricao. */ 
compromisso_t* cria_compromisso (horario_compromisso_t hc, int id,  char* descricao);

/* destroi um compromisso */
void destroi_compromisso(compromisso_t* compr);

/* Libera toda memoria associado a agenda. */
void destroi_agenda(agenda_t* agenda);

/* Marca um compromisso na agenda:
   valores de retorno possiveis:
    -1: compromisso tem interseccao com outro
     0: erro de alocacao de memoria
     1: sucesso

    A lista de compromisso eh ordenada pelo horario de inicio. Eh necessario
    testar a interseccao entre horarios de inicio e de fim no compromisso novo
    considerando o  compromisso anterior e o proximo, caso existam. */
int marca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr);

/* Desmarca o compromisso compr da agenda:
   O parametro compr eh um ponteiro para um compromisso existente da agenda.
   valores de retorno possiveis:
    1: em caso de sucesso
    0: caso nao tenha encontrado o compr */
int desmarca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr);

/* Retorna o mes atual da agenda. */
int mes_atual_agenda(agenda_t *agenda);

/* Ajusta o mes_atual para 1 e aponta prt_mes_atual para o mes 1 na Lista de 
 * meses  */
void prim_mes_agenda(agenda_t* agenda);

/* Avanca a agenda para o proximo mes, incrementando mes_atual.
 * O ponteiro ptr_mes_atual deve ser atualizado para apontar para o novo mes_atual.
 * Se o novo mes_atual nao existir deve ser alocado. A funcao retorna o inteiro 
 * mes_atual em caso de sucesso ou 0 caso contrario.  */ 
int prox_mes_agenda(agenda_t* agenda);

/* Analogo ao prox_mes_agenda porem decrementa mes_atual. */ 
int ant_mes_agenda(agenda_t* agenda);

/* Retorna um ponteiro para a lista ligada de compromissos de um dia do mes
   ou NULL se vazia. A lista de compromissos retornada pode ser percorrida
   usando-se a funcao prox_compr. */ 
compromisso_t* compr_agenda(agenda_t* agenda, int dia);

/* Retorna o proximo compromisso da lista de compromissos compr. */
compromisso_t* prox_compr(compromisso_t* compr);

/* As funcoes abaixo sao usadas para acessar os membros da struct compromisso
   obtidos com a funcao prox_compr. */
horario_compromisso_t hc_compr(compromisso_t* compr); 
int id_compr(compromisso_t* compr); 
char* descricao_compr(compromisso_t* compr); 

/* Essa funcao nao eh extritamente necessaria, o objetivo e' que o programa
principal apresente os dados. Porem pode ser util para voces durante o desenvolvimento */ 
void imprime_agenda_mes(agenda_t* agenda);
