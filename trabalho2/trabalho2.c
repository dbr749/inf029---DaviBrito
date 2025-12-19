#include <stdio.h>
#include <stdlib.h>
#include "trabalho2.h"

#define TAM 10
#define TAMANHO 0
#define QTD 1
#define INICIO_DADOS 2

// estrutura principal com 10 posições
int *vetorPrincipal[TAM];

// inicializa o vetor principal

void inicializar()
{
    for (int i = 0; i < TAM; i++)
    {
        vetorPrincipal[i] = NULL;
    }
}

// libera todas as estruturas auxiliares
void finalizar()
{
    for (int i = 0; i < TAM; i++)
    {
        if (vetorPrincipal[i] != NULL)
        {
            free(vetorPrincipal[i]);
            vetorPrincipal[i] = NULL;
        }
    }
}

// cria estrutura auxiliar na posição informada
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;

    if (tamanho < 1)
        return TAMANHO_INVALIDO;

    if (vetorPrincipal[posicao - 1] != NULL)
        return JA_TEM_ESTRUTURA_AUXILIAR;

    vetorPrincipal[posicao - 1] =
        (int *) malloc((tamanho + INICIO_DADOS) * sizeof(int));

    if (vetorPrincipal[posicao - 1] == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[posicao - 1][TAMANHO] = tamanho;
    vetorPrincipal[posicao - 1][QTD] = 0;

    return SUCESSO;
}

//insere um número na estrutura auxiliar
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;

    if (vetorPrincipal[posicao - 1] == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[posicao - 1][QTD] >=
        vetorPrincipal[posicao - 1][TAMANHO])
        return SEM_ESPACO;

    vetorPrincipal[posicao - 1]
        [INICIO_DADOS + vetorPrincipal[posicao - 1][QTD]] = valor;

    vetorPrincipal[posicao - 1][QTD]++;

    return SUCESSO;
}

//exclui o último número da estrutura auxiliar

int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;

    if (vetorPrincipal[posicao - 1] == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[posicao - 1][QTD] == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    vetorPrincipal[posicao - 1][QTD]--;

    return SUCESSO;
}

//exclui a primeira ocorrência de um número específico
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;

    if (vetorPrincipal[posicao - 1] == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[posicao - 1][QTD] == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    for (int i = 0; i < vetorPrincipal[posicao - 1][QTD]; i++)
    {
        if (vetorPrincipal[posicao - 1][INICIO_DADOS + i] == valor)
        {
            for (int j = i;
                 j < vetorPrincipal[posicao - 1][QTD] - 1;
                 j++)
            {
                vetorPrincipal[posicao - 1][INICIO_DADOS + j] =
                    vetorPrincipal[posicao - 1][INICIO_DADOS + j + 1];
            }

            vetorPrincipal[posicao - 1][QTD]--;
            return SUCESSO;
        }
    }

    return NUMERO_INEXISTENTE;
}

//retorna os dados da estrutura auxiliar

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;

    if (vetorPrincipal[posicao - 1] == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    for (int i = 0; i < vetorPrincipal[posicao - 1][QTD]; i++)
    {
        vetorAux[i] =
            vetorPrincipal[posicao - 1][INICIO_DADOS + i];
    }

    return SUCESSO;
}

//ordena um vetor usando insertion sort
void insertionSort(int v[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int atual = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > atual)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = atual;
    }
}

//retorna os dados ordenados da estrutura auxiliar
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);

    if (retorno != SUCESSO)
        return retorno;

    insertionSort(vetorAux,
                  vetorPrincipal[posicao - 1][QTD]);

    return SUCESSO;
}

//retorna os dados de todas as estruturas auxiliares

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int k = 0;

    for (int i = 0; i < TAM; i++)
    {
        if (vetorPrincipal[i] != NULL)
        {
            for (int j = 0; j < vetorPrincipal[i][QTD]; j++)
            {
                vetorAux[k++] =
                    vetorPrincipal[i][INICIO_DADOS + j];
            }
        }
    }

    if (k == 0)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    return SUCESSO;
}

//retorna todos os dados ordenados

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);

    if (retorno != SUCESSO)
        return retorno;

    int total = 0;
    for (int i = 0; i < TAM; i++)
    {
        if (vetorPrincipal[i] != NULL)
            total += vetorPrincipal[i][QTD];
    }

    insertionSort(vetorAux, total);
    return SUCESSO;
}

//modifica o tamanho da estrutura auxiliar

int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;

    if (vetorPrincipal[posicao - 1] == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    if (novoTamanho < 0)
        return NOVO_TAMANHO_INVALIDO;

    int tamanhoFinal =
        vetorPrincipal[posicao - 1][TAMANHO] + novoTamanho;

    if (tamanhoFinal < 1)
        return NOVO_TAMANHO_INVALIDO;

    int *nova =
        realloc(vetorPrincipal[posicao - 1],
                (tamanhoFinal + INICIO_DADOS) * sizeof(int));

    if (nova == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[posicao - 1] = nova;
    vetorPrincipal[posicao - 1][TAMANHO] = tamanhoFinal;

    if (vetorPrincipal[posicao - 1][QTD] > tamanhoFinal)
        vetorPrincipal[posicao - 1][QTD] = tamanhoFinal;

    return SUCESSO;
}

//retorna a quantidade de elementos preenchidos

int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    if (posicao < 1 || posicao > TAM)
        return POSICAO_INVALIDA;

    if (vetorPrincipal[posicao - 1] == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[posicao - 1][QTD] == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    return vetorPrincipal[posicao - 1][QTD];
}

//montar uma lista encadeada com cabeçalho contendo todos os números

No *montarListaEncadeadaComCabecote()
{
    int existe = 0;

    for (int i = 0; i < TAM; i++)
    {
        if (vetorPrincipal[i] != NULL && vetorPrincipal[i][QTD] > 0)
        {
            existe = 1;
            break;
        }
    }

    if (!existe)
        return NULL;

    No *cabecote = (No *) malloc(sizeof(No));
    cabecote->prox = NULL;

    No *aux = cabecote;

    for (int i = 0; i < TAM; i++)
    {
        if (vetorPrincipal[i] != NULL)
        {
            for (int j = 0; j < vetorPrincipal[i][QTD]; j++)
            {
                No *novo = (No *) malloc(sizeof(No));
                novo->conteudo = vetorPrincipal[i][INICIO_DADOS + j];
                novo->prox = NULL;

                aux->prox = novo;
                aux = novo;
            }
        }
    }

    return cabecote;
}

//copia os dados da lista encadeada para um vetor
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    if (inicio == NULL)
        return;

    No *atual = inicio->prox;
    int i = 0;

    while (atual != NULL)
    {
        vetorAux[i++] = atual->conteudo;
        atual = atual->prox;
    }
}

//libera a lista encadeada 

void destruirListaEncadeadaComCabecote(No **inicio)
{
    if (inicio == NULL || *inicio == NULL)
        return;

    No *atual = *inicio;
    No *aux;

    while (atual != NULL)
    {
        aux = atual->prox;
        free(atual);
        atual = aux;
    }

    *inicio = NULL;
}

//dobrar o valor apontado por x

void dobrar(int *x)
{
    if (x != NULL)
        *x = (*x) * 2;
}
