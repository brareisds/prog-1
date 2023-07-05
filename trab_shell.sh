#!/bin/bash

arquivo_base="historico-alg1_SIGA_ANONIMIZADO.csv"

# Questao 1
# echo -e "Questao 1:\n"
# awk -F',' '$4 != 2 || $5 != 2022 || $8 != 0 || $10 != "Aprovado" ' "$arquivo_base" > arquivo_base_filtrado.csv
# cat "$arquivo_base_filtrado.csv"    

# Número de indivíduos únicos naquele status
# echo -e "\nQuestao 2:\n"
# tail -n +2 "$arquivo_base_filtrado.csv" | cut -d ',' -f1,10 | sort | uniq > status_unicos.csv
# cut -d ',' -f2 status_unicos.csv | sort | uniq > status_existentes.csv

# qtde_status=$(wc -l < "status_existentes.csv")

# echo "Numero de individuos unicos de cada status:"
# i=1
# while [ $i -le $qtde_status ]
# do
#     status=$(awk -v linha="$i" 'NR == linha {print $1}' status_existentes.csv)
#     grep "$status" status_unicos.csv > "status_$status.csv"
#     quant=$(wc -l < "status_$status.csv")
#     echo "$status = $quant"
#     ((i++))
# done


# Questao 3
# echo -e "\nQuestao 3:\n"
padrao="Aprovado"
# gera um arquivo com a quantidade de vezes (ordenada da maior para a menor) que cada aluno cursou a materia
cut -d ',' -f1,10 arquivo_base_filtrado.csv | grep -v "$padrao" | cut -d ',' -f1 | sort -n | uniq -c | sort -nr > quant_cursou_novo.csv

# gera um arquivo somente com as matriculas dos alunos que foram aprovados
cut -d ',' -f1,10 arquivo_base_filtrado.csv | grep "$padrao" | cut -d ',' -f1 > aprovados.csv

# Verifica se o aluno com a maior quantidade de vezes que cursou a matéria foi aprovado. Caso contrario, o arquivo que
arquivo="aprovados.csv"
encontrado=0
max_vezes=0

while IFS=' ' read -r linha; do
    matricula=$(awk -v linha="$linha" 'NR == linha {print $2}' quant_cursou_novo.csv)
    if grep -w -q "$matricula" "$arquivo"; then
        encontrado=1
        max_vezes=$(awk -v linha="$linha" 'NR == linha {print $1}' quant_cursou_novo.csv)
        break
    fi
done < "$arquivo"

# if [ $encontrado -eq 1 ]; then
#     echo "O máximo de vezes que um aluno cursou a matéria antes de ser aprovado foi: $max_vezes"
# fi

# Lê o arquivo linha por linha
while IFS=' ' read -r line; do
  # Divide a linha em duas colunas (quantidade e matricula)
  columns=($line)
  
  # Verifica se a primeira coluna é igual a $max_vezes
  if [ "${columns[0]}" == $max_vezes ]; then
    ((count++))
  fi
done < quant_cursou_novo.csv

# echo "Quantidade de alunos que cursaram a matéria $max_vezes vezes: $count"

# Porcentagem de aprovação/reprovação por ano
# echo -e "\nQuestao 4\n"

separa_anos()
{
    ano=2011
    while [ $ano -le 2022 ]
        do
            cut -d ',' -f1,5,10 arquivo_base_filtrado.csv | grep -w "$ano" > aluno.$ano.csv
            ((ano++))
    done
}

calcula_total_aprovados()
{
    ano=2011
    while [ $ano -le 2022 ]
    do
        alunos=aluno.$ano.csv
        status=Aprovado
   
        cut -d ',' -f1,3 $alunos | grep "$status" |  cut -d ',' -f1 | sort -n -k1,1 | uniq  > aprovados.$ano.csv
    ((ano++))
    done
}

calcula_total_reprovados()
{
    ano=2011
    while [ $ano -le 2022 ]
    do
        alunos=aluno.$ano.csv
        status1=R-freq
        status2=R-nota
        status3=Reprovado

        cut -d ',' -f1,3 $alunos | grep -e "$status1" -e "$status2" -e "$status3" |  cut -d ',' -f1 | sort -n -k1,1 | uniq  > reprovados.$ano.csv
    ((ano++))
    done
}

calcula_porcentagem() {
    ano=2011
    while [ $ano -le 2022 ]
    do
        total_aprovados=$(wc -l < "aprovados.$ano.csv")
        total_reprovados=$(wc -l < "reprovados.$ano.csv")
        total_alunos=$((total_aprovados + total_reprovados))

        # O resultado agora terá duas casas decimais
        porcentagem_aprovacao=$(echo "scale=2; $total_aprovados / $total_alunos * 100" | bc -l)
        porcentagem_reprovacao=$(echo "scale=2; $total_reprovados / $total_alunos * 100" | bc -l)

        # echo "Ano $ano:"
        # echo "Porcentagem de aprovação: $porcentagem_aprovacao%"
        # echo "Porcentagem de reprovação: $porcentagem_reprovacao%"

        ((ano++))
    done
}

# funcoes
separa_anos
calcula_total_aprovados
calcula_total_reprovados
calcula_porcentagem


# Media de nota dos aprovados (no período total e por ano)
echo -e "Questao 5\n"

cut -d ',' -f1,4,5,8,10 arquivo_base_filtrado.csv > notas_gerais.csv

calcula_media_ano_aprovados()
{
    status="Aprovado"
    ano=2011

    while [ $ano -le 2022 ]
    do
        cut -d ',' -f1,2,3,4,5 notas_gerais.csv | awk -F ',' -v ano="$ano" -v status="$status" '$3==ano && $5==status' > notas_aprovados_$ano.csv

        soma_notas=$(cut -d ',' -f4 notas_aprovados_$ano.csv | paste -sd+ | bc)
        quant_alunos=$(wc -l < notas_aprovados_$ano.csv)

        if [ $quant_alunos -gt 0 ]; then
            media=$(echo "scale=2; $soma_notas / $quant_alunos" | bc)
            echo "Ano: $ano, Média das notas: $media"
        else
            echo "Ano: $ano, Média das notas: 0.00"
        fi

        ((ano++))
    done
}

calcula_media_periodo_aprovados()
{
    status="Aprovado"
    ano=2011

    while [ $ano -le 2022 ]
    do
        for periodo in 1 2
        do
            cut -d ',' -f1,2,3,4,5 notas_gerais.csv | awk -F ',' -v periodo="$periodo" -v ano="$ano" -v status="$status" '$2==periodo && $3==ano && $5==status' > notas_aprovados_$ano_$periodo.csv

            soma_notas=$(cut -d ',' -f4 notas_aprovados_$ano_$periodo.csv | paste -sd+ | bc)
            quant_alunos=$(wc -l < notas_aprovados_$ano_$periodo.csv)

            if [ $quant_alunos -gt 0 ]; then
                media=$(echo "scale=2; $soma_notas / $quant_alunos" | bc)
                echo "Ano/periodo: $ano/$periodo, Média das notas: $media"
            else
                echo "Ano/periodo: $ano/$periodo, Média das notas: 0.00"
            fi
        done
        ((ano++))
    done
}


calcula_media_ano_aprovados
calcula_media_periodo_aprovados

# Questao 6

# cut -d ',' -f1,4,5,8,10 arquivo_base_filtrado.csv > notas_gerais.csv

calcula_media_ano_reprovados()
{
    status1=R-freq
    status2=R-nota
    status3=Reprovado
    ano=2011

    while [ $ano -le 2022 ]
    do
        cut -d ',' -f1,2,3,4,5 notas_gerais.csv | awk -F ',' -v ano="$ano" -v status1="$status1" -v status2="$status2" -v status3="$status3" '$3==ano && ($5==status1 || $5==status2 || $5==status3)' > notas_reprovados_$ano.csv

        soma_notas=$(cut -d ',' -f4 notas_reprovados_$ano.csv | paste -sd+ | bc)
        quant_alunos=$(wc -l < notas_reprovados_$ano.csv)

        if [ $quant_alunos -gt 0 ]; then
            media=$(echo "scale=2; $soma_notas / $quant_alunos" | bc)
            echo "Ano: $ano, Média das notas: $media"
        else
            echo "Ano: $ano, Média das notas: 0.00"
        fi

        ((ano++))
    done
}

calcula_media_periodo_reprovados()
{
    status1=R-freq
    status2=R-nota
    status3=Reprovado
    ano=2011

    while [ $ano -le 2022 ]
    do
        for periodo in 1 2
        do
            cut -d ',' -f1,2,3,4,5 notas_gerais.csv | awk -F ',' -v periodo="$periodo" -v ano="$ano" -v status1="$status1" -v status2="$status2" -v status3="$status3" '$2==periodo && $3==ano && ($5==status1 || $5==status2 || $5==status3)' > notas_reprovados_$ano_$periodo.csv

            soma_notas=$(cut -d ',' -f4 notas_reprovados_$ano_$periodo.csv | paste -sd+ | bc)
            quant_alunos=$(wc -l < notas_reprovados_$ano_$periodo.csv)

            if [ $quant_alunos -gt 0 ]; then
                media=$(echo "scale=2; $soma_notas / $quant_alunos" | bc)
                echo "Ano/periodo: $ano/$periodo, Média das notas: $media"
            else
                echo "Ano/periodo: $ano/$periodo, Média das notas: 0.00"
            fi
        done
        ((ano++))
    done
}

calcula_media_ano_reprovados
calcula_media_periodo_reprovados

# Questao 7 = Qual é a média da frequência dos reprovados por nota (período total e por ano)?

cut -d ',' -f1,4,5,8,9,10 arquivo_base_filtrado.csv > notas_gerais.csv

calcula_media_frequencia_anual()
{
    status=R-nota
    ano=2011
    echo "Média anual das frequencias dos reprovados por nota: "
    while [ $ano -le 2022 ]
    do
        
        cut -d ',' -f1,3,5,6 notas_gerais.csv | awk -F ',' -v ano="$ano" -v status="$status" '$2==ano && $4==status ' > freq_reprovados_$ano.csv

        soma_freq=$(cut -d ',' -f3 freq_reprovados_$ano.csv | paste -sd+ | bc)
        quant_alunos=$(wc -l < freq_reprovados_$ano.csv)

        if [ $quant_alunos -gt 0 ]; then
            media_freq=$(echo "scale=2; $soma_freq / $quant_alunos" | bc)
            echo "$ano: $media_freq"
        else
            echo "$ano: 0.00"
        fi

        ((ano++))
    done
}

calcula_media_frequencia_total()
{
    status=R-nota
   
    cut -d ',' -f1,5,6 notas_gerais.csv | awk -F ',' -v status="$status" '$3==status ' > freq_reprovados.csv

    soma_freq=$(cut -d ',' -f2 freq_reprovados.csv | paste -sd+ | bc)
    quant_alunos=$(wc -l < freq_reprovados.csv)

    media_freq=$(echo "scale=2; $soma_freq / $quant_alunos" | bc)
    echo "Média total das frequencias dos reprovados por nota: $media_freq"
    
}

calcula_media_frequencia_anual
calcula_media_frequencia_total




#Questo 8 = Qual a porcentagem de evasões total e anual

cut -d ',' -f1,5,14 arquivo_base_filtrado.csv > situacaoDiscente_geral.csv

calcula_evasao_total()
{
    situacaoDiscente=Evasão
    cut -d ',' -f1,3 situacaoDiscente_geral | grep "$situacaoDiscente" > evasao_total.csv
    quant_total=$(wc -l < situacaoDiscente_geral.csv)
    quant_evasao_total=$(wc -l < evasao_total.csv)

    porcentagem_evasao_total=$(echo "scale=2; $quant_evasao_total / $quant_total * 100" | bc -l)
    echo "Porcentagem de evasao total: $porcentagem_evasao_total%"

}

calcula_evasao_anual()
{
    situacaoDiscente=Evasão
    ano=2011

    while [ $ano -le 2022 ]
    do
        # cut -d ',' -f2,3 situacaoDiscente_geral.csv | grep "$situacaoDiscente" -w "$ano" > evasao_$ano.csv
        cut -d ',' -f2,3 situacaoDiscente_geral.csv | awk -F ',' -v ano="$ano" -v situacaoDiscente="$situacaoDiscente" '$1==ano && $2==situacaoDiscente' > evasao_$ano.csv
        cut -d ',' -f2,3 situacaoDiscente_geral.csv | grep -w "$ano" > quant_alunos_$ano.csv
        quant_total=$(wc -l < quant_alunos_$ano.csv)
        quant_evasao_total=$(wc -l < evasao_$ano.csv)

        porcentagem_evasao_anual=$(echo "scale=2; $quant_evasao_total / $quant_total * 100" | bc -l)
        echo "Porcentagem de evasao anual do ano $ano: $porcentagem_evasao_anual%"
        ((ano++))
    done
}


calcula_evasao_anual
calcula_evasao_total

# Questao 9 = Como os anos de pandemia impactaram no rendimento dos estudantes em relação aos anos anteriores? Calcule em percentual o rendimento dos aprovados, a taxa de cancelamento e de reprovações.
# Considere como anos de pandemia os anos de 2020 e 2021. (EXEMPLO: qual o percentual de aumento ou diminuição de notas, frequências, aprovações/reprovações e cancelamentos).



# Questao 10 = Compare a volta às aulas híbrida (2022 período 1) com os anos de pandemia e os anos anteriores em relação às aprovações, reprovações, mediana das notas e cancelamentos.








