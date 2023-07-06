#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libagenda.h"

/* Cria uma agenda vazia inicializada com mes 1.*/
agenda_t* cria_agenda()
{
    agenda_t* agenda;
    mes_t* prim_mes;

    if (!(agenda = malloc(sizeof(agenda_t))) || !(prim_mes = malloc(sizeof(mes_t))))
        return NULL;

    /*Cria o nodo para o primeiro mes*/
    prim_mes->mes = 1;
    prim_mes->ant = prim_mes;
    prim_mes->prox = prim_mes;
    prim_mes->dias = NULL;

    agenda->mes_atual = 1;
    agenda->ptr_mes_atual = prim_mes;
    
    return agenda;
}

compromisso_t* cria_compromisso (horario_compromisso_t hc, int id,  char* descricao)
{
    char* compr_descricao;
    compromisso_t* compromisso;

    if (!(compromisso = malloc(sizeof(compromisso_t))) || !(compr_descricao = malloc((strlen(descricao) + 1))))
        return NULL;

    strncpy(compr_descricao, descricao, (strlen(descricao) + 1));

    compromisso->descricao = compr_descricao;
    compromisso->inicio = hc.ini_h*60 + hc.ini_m;
    compromisso->fim = hc.fim_h*60 + hc.fim_m;
    compromisso->id = id;
    
    return compromisso;
}

/* Destroi a descricao de um compromisso */
void destroi_descricao_compromisso(compromisso_t* compr)
{
    free(compr->descricao);
}

/* Destroi um compromisso */
void destroi_compromisso(compromisso_t* compr)
{
    destroi_descricao_compromisso(compr);
    free(compr);
}

/* Libera toda memoria associado a agenda. */
void destroi_agenda(agenda_t* agenda)
{
    mes_t* aux_mes;
    dia_t* aux_dia;
    compromisso_t* aux_compr;

    while(agenda->ptr_mes_atual)
    {
        while(agenda->ptr_mes_atual->dias)
        {
            while(agenda->ptr_mes_atual->dias->comprs)
            {
                aux_compr = agenda->ptr_mes_atual->dias->comprs;
                agenda->ptr_mes_atual->dias->comprs = aux_compr->prox;
                
                destroi_compromisso(aux_compr);
            }

            aux_dia = agenda->ptr_mes_atual->dias;
            agenda->ptr_mes_atual->dias = aux_dia->prox;
        
            free(aux_dia);
        }

        aux_mes = agenda->ptr_mes_atual;
        aux_mes->prox->ant = aux_mes->ant;
        aux_mes->ant->prox = aux_mes->prox;
        agenda->ptr_mes_atual = aux_mes->prox;
    
        if(aux_mes->prox == aux_mes)
            agenda->ptr_mes_atual = NULL;

        free(aux_mes);
    }

    free(agenda);
    agenda = NULL;
}

int marca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr)
{
    dia_t *dia_compr, *aux1;
    compromisso_t *aux2;

    /* Caso em que a lista de dias esta vazia e, consequentemente, a lista de compromissos tambem */
    if(!agenda->ptr_mes_atual->dias)
    {
        if(!(dia_compr = malloc(sizeof(dia_t))))
            return 0;

        dia_compr->dia = dia;
        agenda->ptr_mes_atual->dias = dia_compr;
        dia_compr->comprs = compr;
        dia_compr->prox = NULL;
        compr->prox = NULL;

        return 1;
    }

    /* O dia que sera adicionado sempre sera menor que o primeiro, ou seja, nunca sera igual.
    * Portanto, sempre sera um novo dia e, consequentemente, a lista de compr sempre estara vazia*/
    if(dia < agenda->ptr_mes_atual->dias->dia)
    {
        if(!(dia_compr = malloc(sizeof(dia_t))))
            return 0;

        dia_compr->dia = dia;
        dia_compr->prox = agenda->ptr_mes_atual->dias;
        agenda->ptr_mes_atual->dias = dia_compr;
        dia_compr->comprs = compr;
        compr->prox = NULL;

        return 1;
    }
   
    /* Encontra a posicao correta do dia */
    aux1 = agenda->ptr_mes_atual->dias;
    while(aux1->prox != NULL && dia > aux1->prox->dia)
        aux1 = aux1->prox;

    /* Verifica se o dia ja existe na lista. Caso isso aconteca, verifica-se a disponibilidade dos horarios*/
    if(aux1->dia == dia)
    {
        /* Caso em que a lista de compromissos nao esta vazia e o compr insere no inicio. */
        if(compr->inicio <= aux1->comprs->inicio)
        {   
            /* Testa se há conflito de horario entre o termino do novo compromisso e o 
            * começo do compromisso ja existente no inicio da lista. */
            if(compr->fim >= aux1->comprs->inicio)
                return -1;
                
            compr->prox = aux1->comprs;
            aux1->comprs = compr;

            return 1;
        }

        /* Encontra a posicao correta do compromisso no dia especifico*/
        aux2 = aux1->comprs;
        while(aux2->prox != NULL && compr->inicio > aux2->prox->inicio)
            aux2 = aux2->prox;
        
        if(aux2->prox == NULL)
        {
            if(compr->inicio <= aux2->fim)
                return -1;
        }

        /* Verifica o limite do compr anterior e do proximo. */
        else if(compr->inicio <= aux2->fim || compr->fim >= aux2->prox->inicio)
            return -1;
            
        compr->prox = aux2->prox;
        aux2->prox = compr;

        return 1;
    }

    /*Caso que saiu do laco pelo aux1->prox ser igual ao dia_compr. Verifica se o dia ja existe na lista. 
    Caso isso aconteca, verifica-se a disponibilidade dos horarios*/
    if(aux1->prox != NULL && aux1->prox->dia == dia)
    {
        /* Caso em que a lista de compromissos nao esta vazia e o compr insere no inicio. */
        if(compr->inicio <= aux1->prox->comprs->inicio)
        {   
            /* Testa se há conflito de horario entre o termino do novo compromisso e o 
            * começo do compromisso ja existente no inicio da lista. */
            if(compr->fim >= aux1->prox->comprs->inicio)
                return -1;
                
            compr->prox = aux1->prox->comprs;
            aux1->prox->comprs = compr;

            return 1;
        }

        /* Encontra a posicao correta do compromisso no dia especifico */
        aux2 = aux1->prox->comprs;
        while(aux2->prox != NULL && compr->inicio > aux2->prox->inicio)
            aux2 = aux2->prox;
        
        if(aux2->prox == NULL)
        {
            if(compr->inicio <= aux2->fim)
                return -1;
        }

        /* Verifica o limite do compr anterior e do proximo. */
        else if(compr->inicio <= aux2->fim || compr->fim >= aux2->prox->inicio)
            return -1;
            
        compr->prox = aux2->prox;
        aux2->prox = compr;

        return 1;
    }

    if(!(dia_compr = malloc(sizeof(dia_t))))
        return 0;

    dia_compr->dia = dia;
    /* Cria um novo dia. */
    dia_compr->prox = aux1->prox;
    aux1->prox = dia_compr;
    dia_compr->comprs = compr;
    compr->prox = NULL;

    return 1;
    
}

int desmarca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr)
{
    dia_t *aux_dia, *temp_dia;
    compromisso_t *aux_comp, *temp_comp;

    /*agenda do mes esta vazia*/
    if(!agenda->ptr_mes_atual->dias)
        return 0;

    if(dia == agenda->ptr_mes_atual->dias->dia)
    {
        /*remove primeiro compr do primeiro dia e, em seguida, o dia pois o mesmo só possui um compromisso*/
        if(compr == agenda->ptr_mes_atual->dias->comprs) 
        {
   
            aux_comp = agenda->ptr_mes_atual->dias->comprs;
            agenda->ptr_mes_atual->dias->comprs = aux_comp->prox;
        
            destroi_compromisso(aux_comp);

            /*verifica se a agenda de compromisso do dia ficou vazia*/
            if(agenda->ptr_mes_atual->dias->comprs == NULL)
            {
                aux_dia = agenda->ptr_mes_atual->dias;
                agenda->ptr_mes_atual->dias = aux_dia->prox;

                free(aux_dia);
            }

            return 1;
        }

        aux_comp = agenda->ptr_mes_atual->dias->comprs;
        while(aux_comp->prox != NULL && aux_comp->prox != compr)
            aux_comp = aux_comp->prox;

        if(aux_comp->prox == NULL)
            return 0;
        
        temp_comp = aux_comp->prox;
        aux_comp->prox = temp_comp->prox;

        destroi_compromisso(temp_comp);
    }
    
    /* Encontra o dia do compromisso */
    aux_dia = agenda->ptr_mes_atual->dias;
    while (aux_dia->prox != NULL && dia != aux_dia->prox->dia)
        aux_dia = aux_dia->prox;
    
    /* Verifica se o dia exite na lista */
    if (aux_dia->prox == NULL) 
        return 0;

    /* Verifica se o compromisso eh o primeiro compromisso do dia */
    if(compr == aux_dia->prox->comprs)
    {
        aux_comp = aux_dia->prox->comprs;
        aux_dia->prox->comprs = aux_comp->prox;
        
        destroi_compromisso(aux_comp);

        /* Verifica se a agenda de compromisso do dia ficou vazia */
        if(aux_dia->prox->comprs == NULL)
        {
            temp_dia = aux_dia->prox;
            aux_dia->prox = temp_dia->prox;
        
            free(temp_dia);
        }

        return 1;
    }

    /* Procura o compromisso no dia encontrado */
    aux_comp = aux_dia->prox->comprs;
    while(aux_comp->prox != NULL && aux_comp->prox != compr)
        aux_comp = aux_comp->prox;

    if(aux_comp->prox == NULL)
        return 0;
    
    temp_comp = aux_comp->prox;
    aux_comp->prox = temp_comp->prox;

    destroi_compromisso(temp_comp);

    return 1;
}

/* Retorna o mes atual da agenda. */
int mes_atual_agenda(agenda_t *agenda)
{
    return agenda->mes_atual;
}

/* Ajusta o mes_atual para 1 e aponta prt_mes_atual para o mes 1 na Lista de meses  */
void prim_mes_agenda(agenda_t* agenda)
{
    mes_t *aux;

    aux = agenda->ptr_mes_atual;
    while(aux->mes != 1)
        aux = aux->prox;

    agenda->ptr_mes_atual = aux;
    agenda->mes_atual = aux->mes;

}

/* Avanca a agenda para o proximo mes, incrementando mes_atual. */
int prox_mes_agenda(agenda_t* agenda)
{
    mes_t *novo_mes_atual, *antigo_mes_atual;

    antigo_mes_atual = agenda->ptr_mes_atual;

    /* Verifica se o proximo mes ja existe. Se o proximo mes for 1, siginifica que ele eh o ultimo 
    mes da lista e eh necessario criar um novo mes. Caso contrario, o mes ja existe na lista. */
    if(antigo_mes_atual->prox->mes != 1 || antigo_mes_atual->mes == 12)
    {
        novo_mes_atual = antigo_mes_atual->prox;
        agenda->ptr_mes_atual = novo_mes_atual;
        agenda->mes_atual = novo_mes_atual->mes;
    
        return agenda->mes_atual;
    }
    
    /*Adiciona mes no final*/
    if (!(novo_mes_atual = malloc(sizeof(mes_t))))
        return 0;

    agenda->mes_atual++;
    novo_mes_atual->mes = agenda->mes_atual;
    novo_mes_atual->dias = NULL;
    
    novo_mes_atual->prox = antigo_mes_atual->prox;
    antigo_mes_atual->prox->ant = novo_mes_atual;
    novo_mes_atual->ant = antigo_mes_atual;
    antigo_mes_atual->prox = novo_mes_atual;
    
    /*Atualiza o ponteiro da agenda e o numero do mes*/
    agenda->ptr_mes_atual = novo_mes_atual;
    return agenda->mes_atual;
}

/* Analogo ao prox_mes_agenda porem decrementa mes_atual. */ 
int ant_mes_agenda(agenda_t* agenda)
{
    mes_t *novo_mes_atual, *antigo_mes_atual;

    antigo_mes_atual = agenda->ptr_mes_atual;

    if(antigo_mes_atual->ant->mes == antigo_mes_atual->mes-1)
    {
        novo_mes_atual = antigo_mes_atual->ant;
        agenda->ptr_mes_atual = novo_mes_atual;
        agenda->mes_atual = novo_mes_atual->mes;

        return agenda->mes_atual;
    }

    if (!(novo_mes_atual = malloc(sizeof(mes_t))))
        return 0;

    if(antigo_mes_atual->mes == 1)
    {
        agenda->mes_atual = 12;
        novo_mes_atual->mes = agenda->mes_atual;
        novo_mes_atual->dias = NULL;

        antigo_mes_atual->ant = novo_mes_atual;
        novo_mes_atual->prox = antigo_mes_atual;
        antigo_mes_atual->prox = novo_mes_atual;
        novo_mes_atual->ant = antigo_mes_atual;
        agenda->ptr_mes_atual = novo_mes_atual;

        return agenda->mes_atual;
    }

    agenda->mes_atual--;
    novo_mes_atual->mes = agenda->mes_atual;
    novo_mes_atual->dias = NULL;

    antigo_mes_atual->ant->prox = novo_mes_atual;
    novo_mes_atual->ant = antigo_mes_atual->ant;
    antigo_mes_atual->ant = novo_mes_atual;
    novo_mes_atual->prox = antigo_mes_atual;

    agenda->ptr_mes_atual = novo_mes_atual;
    return agenda->mes_atual;
}

/* Retorna um ponteiro para a lista ligada de compromissos de um dia do mes ou NULL se vazia. */ 
compromisso_t* compr_agenda(agenda_t* agenda, int dia)
{
    dia_t* aux;

    /*Verifica se o mes esta vazio*/
    if(!agenda->ptr_mes_atual->dias)
        return NULL;

    aux = agenda->ptr_mes_atual->dias;
    while(aux != NULL && aux->dia != dia)
        aux = aux->prox;

    /* Verifica se o dia existe na lista ou se a lista de comprs esta vazia*/
    if(!aux || !aux->comprs)
        return NULL;
    
    return aux->comprs;
}

/* Retorna o proximo compromisso da lista de compromissos compr.*/
compromisso_t* prox_compr(compromisso_t* compr)
{
    return compr->prox;
}

horario_compromisso_t hc_compr(compromisso_t* compr)
{
    horario_compromisso_t horario_convertido;

    horario_convertido.ini_h =  compr->inicio / 60;
    horario_convertido.fim_h = compr->fim / 60;
    horario_convertido.ini_m = compr->inicio % 60;
    horario_convertido.fim_m = compr->fim % 60;

    return horario_convertido;
}

int id_compr(compromisso_t* compr)
{
    return compr->id;
}

char* descricao_compr(compromisso_t* compr)
{
    return compr->descricao;
}
