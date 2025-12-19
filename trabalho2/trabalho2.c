#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

// Estrutura para gerenciar cada posição do vetor principal
typedef struct {
    int *dados;           // Ponteiro para o vetor dinâmico de dados
    int tamanho;          // Tamanho total alocado
    int quantidade;       // Quantidade de elementos preenchidos
} EstruturaAuxiliar;

EstruturaAuxiliar vetorPrincipal[TAM];

/*
Objetivo: criar estrutura auxiliar na posição 'posicao' com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    if (posicao < 1 || posicao > 10) {
        return POSICAO_INVALIDA;
    }

    if (tamanho < 1) {
        return TAMANHO_INVALIDO;
    }
  
    int indice = posicao - 1;

    if (vetorPrincipal[indice].dados != NULL) {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    vetorPrincipal[indice].dados = (int *)malloc(tamanho * sizeof(int));

    if (vetorPrincipal[indice].dados == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    vetorPrincipal[indice].tamanho = tamanho;
    vetorPrincipal[indice].quantidade = 0;
    
    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;

    if (posicao < 1 || posicao > 10) {
        posicao_invalida = 1;
    }

    if (posicao_invalida)
        retorno = POSICAO_INVALIDA;
    else
    {
        int indice = posicao - 1;
       
        if (vetorPrincipal[indice].dados != NULL) {
            existeEstruturaAuxiliar = 1;
        }
        
        if (existeEstruturaAuxiliar)
        {
            if (vetorPrincipal[indice].quantidade < vetorPrincipal[indice].tamanho) {
                temEspaco = 1;
            }
            
            if (temEspaco)
            {
                vetorPrincipal[indice].dados[vetorPrincipal[indice].quantidade] = valor;
                vetorPrincipal[indice].quantidade++;
                retorno = SUCESSO;
            }
            else
            {
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: excluir o numero do final da estrutura (exclusão lógica)
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar [3, 8, 7,  ,  ,  ].

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if (posicao < 1 || posicao > 10) {
        return POSICAO_INVALIDA;
    }
    
    int indice = posicao - 1;

    if (vetorPrincipal[indice].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (vetorPrincipal[indice].quantidade == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    vetorPrincipal[indice].quantidade--;
    
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' específico da estrutura
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: [3, 8, 7, 9,  ,  ] excluir 8 -> [3, 7, 9,  ,  ,  ]

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    if (posicao < 1 || posicao > 10) {
        return POSICAO_INVALIDA;
    }
    
    int indice = posicao - 1;

    if (vetorPrincipal[indice].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
 
    if (vetorPrincipal[indice].quantidade == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    int posicaoValor = -1;
    for (int i = 0; i < vetorPrincipal[indice].quantidade; i++) {
        if (vetorPrincipal[indice].dados[i] == valor) {
            posicaoValor = i;
            break;
        }
    }
    if (posicaoValor == -1) {
        return NUMERO_INEXISTENTE;
    }

    for (int i = posicaoValor; i < vetorPrincipal[indice].quantidade - 1; i++) {
        vetorPrincipal[indice].dados[i] = vetorPrincipal[indice].dados[i + 1];
    }
    
    vetorPrincipal[indice].quantidade--;
    
    return SUCESSO;
}

int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao'
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) {
        return POSICAO_INVALIDA;
    }
    
    int indice = posicao - 1;
    
    if (vetorPrincipal[indice].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
   
    for (int i = 0; i < vetorPrincipal[indice].quantidade; i++) {
        vetorAux[i] = vetorPrincipal[indice].dados[i];
    }
    
    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao'
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) {
        return POSICAO_INVALIDA;
    }
    
    int indice = posicao - 1;
 
    if (vetorPrincipal[indice].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    for (int i = 0; i < vetorPrincipal[indice].quantidade; i++) {
        vetorAux[i] = vetorPrincipal[indice].dados[i];
    }

    int temp;
    for (int i = 0; i < vetorPrincipal[indice].quantidade - 1; i++) {
        for (int j = 0; j < vetorPrincipal[indice].quantidade - i - 1; j++) {
            if (vetorAux[j] > vetorAux[j + 1]) {
                temp = vetorAux[j];
                vetorAux[j] = vetorAux[j + 1];
                vetorAux[j + 1] = temp;
            }
        }
    }
    
    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int totalElementos = 0;
    
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL) {
            totalElementos += vetorPrincipal[i].quantidade;
        }
    }

    if (totalElementos == 0) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    int posicaoVetorAux = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL) {
            for (int j = 0; j < vetorPrincipal[i].quantidade; j++) {
                vetorAux[posicaoVetorAux] = vetorPrincipal[i].dados[j];
                posicaoVetorAux++;
            }
        }
    }
    
    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int totalElementos = 0;
    
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL) {
            totalElementos += vetorPrincipal[i].quantidade;
        }
    }
   
    if (totalElementos == 0) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }
    
    int posicaoVetorAux = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL) {
            for (int j = 0; j < vetorPrincipal[i].quantidade; j++) {
                vetorAux[posicaoVetorAux] = vetorPrincipal[i].dados[j];
                posicaoVetorAux++;
            }
        }
    }
  
    int temp;
    for (int i = 0; i < totalElementos - 1; i++) {
        for (int j = 0; j < totalElementos - i - 1; j++) {
            if (vetorAux[j] > vetorAux[j + 1]) {
                temp = vetorAux[j];
                vetorAux[j] = vetorAux[j + 1];
                vetorAux[j + 1] = temp;
            }
        }
    }
    
    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar
novo tamanho = tamanho atual + novoTamanho
O resultado deve ser sempre >= 1

Rertono (int)
    SUCESSO - modificado com sucesso
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida
    NOVO_TAMANHO_INVALIDO - tamanho resultante < 1
    SEM_ESPACO_DE_MEMORIA - erro na alocação
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) {
        return POSICAO_INVALIDA;
    }
    
    int indice = posicao - 1;
    
    if (vetorPrincipal[indice].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    int tamanhoResultante = vetorPrincipal[indice].tamanho + novoTamanho;

    if (tamanhoResultante < 1) {
        return NOVO_TAMANHO_INVALIDO;
    }

    int *novosDados = (int *)realloc(vetorPrincipal[indice].dados, tamanhoResultante * sizeof(int));

    if (novosDados == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    vetorPrincipal[indice].dados = novosDados;
    vetorPrincipal[indice].tamanho = tamanhoResultante;

    if (vetorPrincipal[indice].quantidade > tamanhoResultante) {
        vetorPrincipal[indice].quantidade = tamanhoResultante;
    }
    
    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    Um número > 0 com a quantidade de elementos
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA) {
        return POSICAO_INVALIDA;
    }
    
    int indice = posicao - 1;
    

    if (vetorPrincipal[indice].dados == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    
    
    if (vetorPrincipal[indice].quantidade == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    

    return vetorPrincipal[indice].quantidade;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números

Retorno (No*)
    NULL - não tem nenhum número
    No* - ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    No *cabecote = (No *)malloc(sizeof(No));
    if (cabecote == NULL) {
        return NULL;
    }
    
    cabecote->prox = NULL;
    
    No *atual = cabecote;
    int temElementos = 0;
    
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL) {
            for (int j = 0; j < vetorPrincipal[i].quantidade; j++) {
                temElementos = 1;

                No *novoNo = (No *)malloc(sizeof(No));
                if (novoNo == NULL) {

                    destruirListaEncadeadaComCabecote(&cabecote);
                    return NULL;
                }
                
                novoNo->conteudo = vetorPrincipal[i].dados[j];
                novoNo->prox = NULL;

                atual->prox = novoNo;
                atual = novoNo;
            }
        }
    }
    
    if (!temElementos) {
        free(cabecote);
        return NULL;
    }
    
    return cabecote;
}

/*
Objetivo: retorna os números da lista encadeada com cabeçote
armazenando em vetorAux
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    if (inicio == NULL) {
        return;
    }
    
    No *atual = inicio->prox; 
    int indice = 0;
    
    while (atual != NULL) {
        vetorAux[indice] = atual->conteudo;
        indice++;
        atual = atual->prox;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote
O ponteiro inicio deve ficar com NULL
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    if (inicio == NULL || *inicio == NULL) {
        return;
    }
    
    No *atual = *inicio;
    No *proximo;
    
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa
Deve ser chamado ao início do programa
*/
void inicializar()
{
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i].dados = NULL;
        vetorPrincipal[i].tamanho = 0;
        vetorPrincipal[i].quantidade = 0;
    }
}

/*
Objetivo: finaliza o programa
Libera todos os espaços de memória das estruturas auxiliares
*/
void finalizar()
{
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].dados != NULL) {
            free(vetorPrincipal[i].dados);
            vetorPrincipal[i].dados = NULL;
            vetorPrincipal[i].tamanho = 0;
            vetorPrincipal[i].quantidade = 0;
        }
    }
}