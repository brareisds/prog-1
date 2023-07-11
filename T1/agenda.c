#include <stdio.h>
#include "libagenda.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define F 30
#define T 100
#define LIMITE 100
#define MESES 12
#define DIAS 31

typedef struct {
    int lideranca;
    int experiencia;
    agenda_t* agenda;
} funcionario_t;

typedef struct {
    int tempo_conclusao;
    int dificuldade;
    int concluida;
} tarefas_t;

int ALEAT(int MIN, int MAX)
{
    return (rand() % (MAX -  MIN + 1) + MIN);
}

void inicia_func_tarefas(funcionario_t funcionarios[],tarefas_t tarefas[])
{
    int func, tarefa;
    for (func = 0; func < F; func++)
    {
        funcionarios[func].lideranca = ALEAT(0,100);
        funcionarios[func].experiencia = ALEAT(20,100);
        funcionarios[func].agenda = cria_agenda();
    }
    for (tarefa = 0; tarefa < T; tarefa++)
    {
        tarefas[tarefa].tempo_conclusao = ALEAT(600,800);
        tarefas[tarefa].dificuldade = ALEAT(30,80);
    }
   
}

/* Retorna o indice do lider sorteado */
int sorteia_lider(funcionario_t funcionarios[])
{
    int indice_lider = ALEAT(0,F-1);
     
    while (funcionarios[indice_lider].lideranca < 30 || funcionarios[indice_lider].lideranca > 70)
        indice_lider = ALEAT(0,F-1); 

    return indice_lider;
}


void marcar_reunioes(funcionario_t funcionarios[])
{
    compromisso_t *compr_lider, *compr_func;
    char descricao[255];
    horario_compromisso_t hc;
    funcionario_t lider;
    int func, mes, reunioes, dia_compr, id, aleat_func, membro, quant_membros, disponiveis, lider_disponivel, membro_disponivel, indice_lider;

    for (func = 0; func < F; func++)
        prim_mes_agenda(funcionarios[func].agenda);

    for (mes = 1; mes <= MESES; mes++)
    {
        printf("M %.2d\n", mes);

        for (reunioes = 1; reunioes <= LIMITE; reunioes++)
        {
            indice_lider = sorteia_lider(funcionarios);
            lider = funcionarios[indice_lider];
          
            hc.ini_h = ALEAT(8,12);
            hc.ini_m = ALEAT(0,3)*15;
            hc.fim_h = hc.ini_h + ALEAT(1,4); 
            hc.fim_m = hc.ini_m;
            dia_compr = ALEAT(1,31);
            id = ALEAT(0, T-1);
            sprintf(descricao, "REUNIR L %.2d %.2d/%.2d %.2d:%.2d %.2d:%.2d T %.2d", indice_lider, dia_compr, mes, hc.ini_h, hc.ini_m, hc.fim_h, hc.fim_m, id);

            compr_lider = cria_compromisso(hc,id,descricao);
            
            printf("%s", descricao);

            lider_disponivel = marca_compromisso_agenda(lider.agenda, dia_compr, compr_lider);

            if(lider_disponivel == -1)
            {
                destroi_compromisso(compr_lider);
                printf("\tLIDER INDISPONIVEL \n");
            }

            else if(lider_disponivel == 1)
            {   
                disponiveis = 0;
                quant_membros = ALEAT(2,6);
                printf("\tMEMBROS:");

                /* Sorteia membros para a reuniao*/
                for (membro = 0; membro < quant_membros; membro++)
                {
                    aleat_func = ALEAT(0,F-1);
                    compr_func = cria_compromisso(hc,id,descricao);

                    if(lider.lideranca > funcionarios[aleat_func].lideranca + ALEAT(-20,10))
                    {
                        membro_disponivel = marca_compromisso_agenda(funcionarios[aleat_func].agenda, dia_compr, compr_func);
                        if(membro_disponivel == 1)
                        {
                            disponiveis++;
                            printf(" %.2d:OK",aleat_func);
                        }
                        else if(membro_disponivel == -1 || membro_disponivel == 0)
                        {
                            destroi_compromisso(compr_func);
                            printf(" %.2d:IN",aleat_func);
                        }
                    } 
                    else
                        destroi_compromisso(compr_func);
                }
                
                if(!disponiveis)
                {
                    printf("VAZIA");
                    desmarca_compromisso_agenda(lider.agenda, dia_compr, compr_lider);                
                }
            
                printf("\n");
            }
            
        }

        for (func = 0; func < F; func++)
            prox_mes_agenda(funcionarios[func].agenda);
    }
}

int calcula_min_trab(compromisso_t* compr)
{
    horario_compromisso_t hc;
    int minutos_inicio, minutos_final, min_trab;
    hc = hc_compr(compr);

    minutos_inicio = hc.ini_h*60 + hc.ini_m;;
    minutos_final = hc.fim_h*60 + hc.fim_m;

    min_trab = minutos_final - minutos_inicio;

    return min_trab;
    
}

/* Realiza todas as reuniões marcadas */
void realizar_reunioes(funcionario_t funcionarios[], tarefas_t tarefas[], int *qtdes_reunioes_realizadas, int* qtde_tarefas_tempo_restante_zero)
{
    int func, mes, dia, min_trab,t, tarefa;
    compromisso_t* lista_comprs;
    char* descricao;

    for (func = 0; func < F; func++)
        prim_mes_agenda(funcionarios[func].agenda);

    (*qtdes_reunioes_realizadas) = 0;
    for (mes = 1; mes <= MESES; mes++)
    {
        for (dia = 1; dia <= DIAS; dia++)
        {
            for (func = 0; func < F; func++)
            {
                lista_comprs = compr_agenda(funcionarios[func].agenda,dia);
                while(lista_comprs)
                {
                    t = id_compr(lista_comprs);
                    min_trab = calcula_min_trab(lista_comprs);
                    if(tarefas[t].tempo_conclusao > 0)
                    {
                        tarefas[t].tempo_conclusao -= min_trab * (funcionarios[func].experiencia / 100.0) * ((100 - tarefas[t].dificuldade) / 100.0);
                        if(funcionarios[func].experiencia < LIMITE)
                            funcionarios[func].experiencia++;
                        (*qtdes_reunioes_realizadas)++;
                    }
                    else    
                        tarefas[t].tempo_conclusao = 0;

                    descricao = descricao_compr(lista_comprs);
                    printf("%.2d/%.2d F %.2d: %s \n", dia, mes, func, descricao);

                    if(tarefas[t].tempo_conclusao <= 0)
                        printf("\tCONCLUIDA\n");
                    else
                        printf("\tT %.2d D %.2d TCR %.2d\n", t, tarefas[t].dificuldade, tarefas[t].tempo_conclusao);

                    lista_comprs = prox_compr(lista_comprs); 
                }
            }
        }

        for (func = 0; func < F; func++)
            prox_mes_agenda(funcionarios[func].agenda);
    }

    /* Soma quantidade de tarefas */
    (*qtde_tarefas_tempo_restante_zero) = 0;
    for(tarefa = 0; tarefa < T; tarefa++)
    {
        if(tarefas[tarefa].tempo_conclusao <= 0)
            (*qtde_tarefas_tempo_restante_zero)++;
    }
   
}


/* libera a memoria de todas as agendas */
void destroi_agendas(funcionario_t funcionarios[])
{
    int func;
    for (func = 0; func < F; func++)
        destroi_agenda(funcionarios[func].agenda);
}


int main()
{
    tarefas_t tarefas[T];
    funcionario_t funcionarios[F];
    int qtdes_reunioes_realizadas, qtde_tarefas_tempo_restante_zero;
    srand(0);
   
    inicia_func_tarefas(funcionarios,tarefas);
    marcar_reunioes(funcionarios);
    realizar_reunioes(funcionarios, tarefas, &qtdes_reunioes_realizadas, &qtde_tarefas_tempo_restante_zero);

    printf("REUNIOES REALIZADAS %d\n", qtdes_reunioes_realizadas);
    printf("TAREFAS CONCLUIDAS %d\n", qtde_tarefas_tempo_restante_zero);

    destroi_agendas(funcionarios);

    return 0;
}

    
