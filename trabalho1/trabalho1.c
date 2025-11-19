// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Davi Brito Chagas
//  email: 20251160044@ifba.edu.br
//  Matrícula: 20251160044
//  Semestre: 2025.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################



#include <stdio.h>
#include "trabalho1.h"
#include <stdlib.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##
 somar = somar dois valores
*/
int somar(int x, int y)
{
    int soma_valor;
    soma_valor = x + y;
    return soma_valor;
}

/*
## função utilizada para testes  ##
 fatorial = fatorial de um número
*/
int fatorial(int x)
{
    int i, fat_valor = 1;

    for (i = x; i > 1; i--)
        fat_valor = fat_valor * i;

    return fat_valor;
}

int teste(int a)
{
    int valor_retorno;
    if (a == 2)
        valor_retorno = 3;
    else
        valor_retorno = 4;

    return valor_retorno;
}

/*
 Q1 = validar data
*/
int q1(char data[])
{
    int i = 0;
    int dia_index = 0;
    int mes_index = 0;
    int ano_index = 0;

    char str_dia[3];
    char str_mes[3];
    char str_ano[5];

    // Verificação mínima de formato: contar barras e posições
    int barra1 = -1, barra2 = -1;
    for (i = 0; data[i] != '\0'; i++)
    {
        if (data[i] == '/')
        {
            if (barra1 == -1)
                barra1 = i;
            else if (barra2 == -1)
                barra2 = i;
            else
                return 0; // mais de duas barras -> inválido
        }
    }

    // deve haver duas barras em posições razoáveis
    if (barra1 <= 0 || barra2 <= barra1 + 1 || data[barra2 + 1] == '\0')
        return 0;

    // separar dia (e checar caracteres e tamanho máximo 2)
    for (i = 0; i < barra1; i++)
    {
        if (data[i] < '0' || data[i] > '9')
            return 0;
        if (dia_index >= 2) // overflow de buffer (mais de 2 dígitos)
            return 0;
        str_dia[dia_index++] = data[i];
    }
    str_dia[dia_index] = '\0';

    // separar mês (tamanho máximo 2)
    for (i = barra1 + 1; i < barra2; i++)
    {
        if (data[i] < '0' || data[i] > '9')
            return 0;
        if (mes_index >= 2)
            return 0;
        str_mes[mes_index++] = data[i];
    }
    str_mes[mes_index] = '\0';

    // separar ano (aceitar 2 ou 4 dígitos, impedir 0 dígitos)
    for (i = barra2 + 1; data[i] != '\0'; i++)
    {
        if (data[i] < '0' || data[i] > '9')
            return 0;
        if (ano_index >= 4) // mais de 4 dígitos -> inválido
            return 0;
        str_ano[ano_index++] = data[i];
    }
    str_ano[ano_index] = '\0';

    if (!(ano_index == 2 || ano_index == 4))
        return 0; // aceitar apenas 2 ou 4 dígitos no ano

    int dia = atoi(str_dia);
    int mes = atoi(str_mes);
    int ano = atoi(str_ano);

    // validações principais
    if (mes < 1 || mes > 12)
        return 0;

    if (dia < 1 || dia > 31)
        return 0;

    // fevereiro
    if (mes == 2)
    {
        int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        if (bissexto && dia > 29)
            return 0;
        if (!bissexto && dia > 28)
            return 0;
    }

    // meses com 30 dias
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        if (dia > 30)
            return 0;
    }

    return 1;
}

DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DiasMesesAnos dma_resultado;

    // validar as duas datas usando q1
    if (q1(datainicial) == 0)
    {
        dma_resultado.retorno = 2;
        return dma_resultado;
    }
    if (q1(datafinal) == 0)
    {
        dma_resultado.retorno = 3;
        return dma_resultado;
    }

    // extrair os números com quebraData 
    DataQuebrada d1 = quebraData(datainicial);
    DataQuebrada d2 = quebraData(datafinal);

    // quebraData também deve ter valido=1; se n, tratamos como inválido
    if (d1.valido == 0)
    {
        dma_resultado.retorno = 2;
        return dma_resultado;
    }
    if (d2.valido == 0)
    {
        dma_resultado.retorno = 3;
        return dma_resultado;
    }

    // Se data final menor que inicial: erro
    if ((d2.iAno < d1.iAno) ||
        (d2.iAno == d1.iAno && d2.iMes < d1.iMes) ||
        (d2.iAno == d1.iAno && d2.iMes == d1.iMes && d2.iDia < d1.iDia))
    {
        dma_resultado.retorno = 4;
        return dma_resultado;
    }

    int dia = d2.iDia - d1.iDia;
    int mes = d2.iMes - d1.iMes;
    int ano = d2.iAno - d1.iAno;

    // ajustar dias (emprestando do mês anterior)
    if (dia < 0)
    {
        mes--;
        int dias_mes_anterior;
        int m = d2.iMes - 1;
        int a = d2.iAno;
        if (m == 0)
        {
            m = 12;
            a--;
        }
        if (m == 2)
        {
            int bissexto = (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
            dias_mes_anterior = bissexto ? 29 : 28;
        }
        else if (m == 4 || m == 6 || m == 9 || m == 11)
            dias_mes_anterior = 30;
        else
            dias_mes_anterior = 31;
        dia += dias_mes_anterior;
    }

    // ajustar meses
    if (mes < 0)
    {
        mes += 12;
        ano--;
    }

    dma_resultado.qtdDias = dia;
    dma_resultado.qtdMeses = mes;
    dma_resultado.qtdAnos = ano;
    dma_resultado.retorno = 1;
    return dma_resultado;
}

int q3(char *texto, char c, int is_case_sensitive)
{
    int qtd_ocorrencias = 0;
    int c_alternativo = 0;

    if (is_case_sensitive != 1)
    {
        if (c >= 'A' && c <= 'Z')
            c_alternativo = c + 32;
        else if (c >= 'a' && c <= 'z')
            c_alternativo = c - 32;

        for (int i = 0; texto[i] != '\0'; i++)
        {
            if (texto[i] == c || texto[i] == c_alternativo)
                qtd_ocorrencias++;
        }
    }
    else
    {
        for (int i = 0; texto[i] != '\0'; i++)
        {
            if (texto[i] == c)
                qtd_ocorrencias++;
        }
    }

    return qtd_ocorrencias;
}

int q4(char *str_texto, char *str_busca, int posicoes[70])
{
    int aux;
    int qtd_ocorrencias = 0;
    int posicao_index = 0;
    int palavra_idx = 0;

    for (int i = 0; str_texto[i] != '\0'; i++)
    {
        palavra_idx = 0; // Sempre reinicia o índice da palavra

        if (str_busca[palavra_idx] == str_texto[i])
        {
            int j = i;

            while (str_busca[palavra_idx] != '\0' && str_texto[j] != '\0') //compara texto com palavra até alguém acabar
            {
                if (str_busca[palavra_idx] == str_texto[j] && str_busca[palavra_idx + 1] != '\0')
                {
                    palavra_idx++;
                    j++;
                }
                else if (str_busca[palavra_idx] == str_texto[j] && str_busca[palavra_idx + 1] == '\0')
                {
                    posicoes[posicao_index] = i + 1;
                    posicao_index++;
                    posicoes[posicao_index] = j + 1;
                    posicao_index++;

                    i = j;
                    qtd_ocorrencias++;
                    break;
                }
                else
                {
                    break;
                }
            }
        }
    }
    return qtd_ocorrencias;
}

int q5(int num)
{
    int invertido = 0;

    while (num > 0)
    {
        invertido = invertido * 10 + (num % 10);
        num /= 10;
    }

    return invertido;
}

int q6(int numerobase, int numerobusca)
{
    int qtd_ocorrencias = 0;
    int qtd_digitos_busca = 0;

    int copia_busca = numerobusca;

    while (copia_busca > 0)
    {
        copia_busca /= 10;
        qtd_digitos_busca++;
    }

    int divisor = 1;

    for (int k = 0; k < qtd_digitos_busca; k++)
        divisor *= 10;

    int trecho;

    while (numerobase > 0)
    {
        trecho = numerobase % divisor;

        if (trecho == numerobusca)
        {
            qtd_ocorrencias++;
            numerobase /= divisor;
        }
        else
        {
            numerobase /= 10;
        }
    }

    return qtd_ocorrencias;
}

int q7(char matriz[8][10], char palavra[5])
{
    int achou = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int p = 0;

            if (palavra[p] == matriz[i][j])
            {
                int k = i, l = j;

                while (k < 8 && palavra[p] != '\0' && palavra[p] == matriz[k][l])
                {
                    p++;
                    k++;
                }
                if (palavra[p] == '\0')
                    return 1;

                p = 0; k = i; l = j;

                while (k >= 0 && palavra[p] != '\0' && palavra[p] == matriz[k][l])
                {
                    p++;
                    k--;
                }
                if (palavra[p] == '\0')
                    return 1;

                p = 0; k = i; l = j;

                while (l < 10 && palavra[p] != '\0' && palavra[p] == matriz[k][l])
                {
                    p++;
                    l++;
                }
                if (palavra[p] == '\0')
                    return 1;

                p = 0; k = i; l = j;

                while (l >= 0 && palavra[p] != '\0' && palavra[p] == matriz[k][l])
                {
                    p++;
                    l--;
                }
                if (palavra[p] == '\0')
                    return 1;

                p = 0; k = i; l = j;

                while (k < 8 && l < 10 && palavra[p] != '\0' && palavra[p] == matriz[k][l])
                {
                    p++;
                    k++;
                    l++;
                }
                if (palavra[p] == '\0')
                    return 1;

                p = 0; k = i; l = j;

                while (k < 8 && l >= 0 && palavra[p] != '\0' && palavra[p] == matriz[k][l])
                {
                    p++;
                    k++;
                    l--;
                }
                if (palavra[p] == '\0')
                    return 1;

                p = 0; k = i; l = j;

                while (k >= 0 && l < 10 && palavra[p] != '\0' && palavra[p] == matriz[k][l])
                {
                    p++;
                    k--;
                    l++;
                }
                if (palavra[p] == '\0')
                    return 1;

                p = 0; k = i; l = j;

                while (k >= 0 && l >= 0 && palavra[p] != '\0' && palavra[p] == matriz[k][l])
                {
                    p++;
                    k--;
                    l--;
                }
                if (palavra[p] == '\0')
                    return 1;
            }
        }
    }

    return 0;
}

DataQuebrada quebraData(char data[])
{
    DataQuebrada dq;
    char str_dia[3];
    char str_mes[3];
    char str_ano[5];
    int i;

    for (i = 0; data[i] != '/'; i++)
        str_dia[i] = data[i];

    if (i == 1 || i == 2)
        str_dia[i] = '\0';
    else
    {
        dq.valido = 0;
        return dq;
    }

    int j = i + 1;
    i = 0;

    for (; data[j] != '/' ; j++)
    {
        str_mes[i] = data[j];
        i++;
    }

    if (i == 1 || i == 2)
        str_mes[i] = '\0';
    else
    {
        dq.valido = 0;
        return dq;
    }

    j++;
    i = 0;

    for (; data[j] != '\0'; j++)
    {
        str_ano[i] = data[j];
        i++;
    }

    if (i == 2 || i == 4)
        str_ano[i] = '\0';
    else
    {
        dq.valido = 0;
        return dq;
    }

    dq.iDia = atoi(str_dia);
    dq.iMes = atoi(str_mes);
    dq.iAno = atoi(str_ano);
    dq.valido = 1;

    return dq;
}
