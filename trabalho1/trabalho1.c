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
//  Nome: Victoria Estrelado Regis Valasque
//  email: 20222160021@ifba.edu.br
//  Matrícula:20222160021
//  Semestre: 2 semestre

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
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;

    soma = x + y;

    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    int datavalida = 1;
    DataQuebrada dq = quebraData(data);
    int dia=dq.iDia;
    int mes=dq.iMes;
    int ano=dq.iAno;

        datavalida = 1;
        if (dq.valido==0)
            return 0;
        
        if (mes>0 && mes <13) {
            datavalida=1;
            if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
                if (dia>0 && dia <31)
                    datavalida=1;
                else 
                    datavalida=0;
            }
            else if (mes == 2){
                if ((ano%4==0 && ano%100!=0) || (ano%400==0)){
                    if (dia >0 && dia <30)
                        datavalida=1;
                    else 
                        datavalida=0;
                }
                else{
                    if (dia > 0 && dia <29){
                        datavalida=1;
                    }
                    else {
                        datavalida=0;
                    }
                }
            }
            else if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
                if (dia > 0 && dia <32){
                    datavalida=1;
                }
                else {
                    datavalida=0;
                }
            }
            else {
                datavalida = 0;
            }
        }
        else {
            datavalida=0;
        }
    if (datavalida)
        return 1;
    else
        return 0;
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DiasMesesAnos dma;
    
    if (q1(datainicial) == 0){
        dma.retorno = 2;
        return dma;
    }
   
    if (q1(datafinal) == 0){
        dma.retorno = 3;
        return dma;
    }
    
    DataQuebrada dqInicial = quebraData(datainicial);
    DataQuebrada dqFinal = quebraData(datafinal);
    
    int iDiaInicial = dqInicial.iDia;
    int iMesInicial = dqInicial.iMes;
    int iAnoInicial = dqInicial.iAno;
    
    int iDiaFinal = dqFinal.iDia;
    int iMesFinal = dqFinal.iMes;
    int iAnoFinal = dqFinal.iAno;
    
    if (iAnoInicial > iAnoFinal || 
        (iAnoInicial == iAnoFinal && iMesInicial > iMesFinal) ||
        (iAnoInicial == iAnoFinal && iMesInicial == iMesFinal && iDiaInicial > iDiaFinal)){
        dma.retorno = 4;
        return dma;
    }

   
    int qtdDias = iDiaFinal - iDiaInicial;
    int qtdMeses = iMesFinal - iMesInicial;
    int qtdAnos = iAnoFinal - iAnoInicial;
    
    if (qtdMeses < 0){
        qtdAnos--;
        qtdMeses = 12 + qtdMeses;
    }

    if (qtdDias < 0){
        qtdMeses--;

        int mesAnterior = iMesFinal - 1;
        int anoReferencia = iAnoFinal;
        
        if (mesAnterior == 0){
            mesAnterior = 12;
            anoReferencia--;
        }
        
        int diasMesAnterior;
        if (mesAnterior == 2){
   
            if ((anoReferencia % 4 == 0 && anoReferencia % 100 != 0) || 
                (anoReferencia % 400 == 0)){
                diasMesAnterior = 29;
            } else {
                diasMesAnterior = 28;
            }
        } else if (mesAnterior == 4 || mesAnterior == 6 || mesAnterior == 9 || mesAnterior == 11){
            diasMesAnterior = 30;
        } else {
            diasMesAnterior = 31;
        }
        
        qtdDias = diasMesAnterior - iDiaInicial + iDiaFinal;
    }

    if (qtdMeses < 0){
        qtdAnos--;
        qtdMeses = 12 + qtdMeses;
    }
    
    dma.qtdDias = qtdDias;
    dma.qtdMeses = qtdMeses;
    dma.qtdAnos = qtdAnos;
    dma.retorno = 1;
    
    return dma;
}

int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;  // Começa com 0, não -1!
    int i;
    
    if (isCaseSensitive != 1) {
        
        for (i = 0; texto[i] != '\0'; i++) {
            char textoChar = texto[i];
            char charBusca = c;
            
            if (textoChar >= 'A' && textoChar <= 'Z') {
                textoChar = textoChar + 32;
            }
            if (charBusca >= 'A' && charBusca <= 'Z') {
                charBusca = charBusca + 32;
            }
            
            if (textoChar == charBusca) {
                qtdOcorrencias++;
            }
        }
    }
    else {
        for (i = 0; texto[i] != '\0'; i++) {
            if (texto[i] == c) {
                qtdOcorrencias++;
            }
        }
    }
    
    return qtdOcorrencias;
}
/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int tamanho = 0;
    int sizeBusca = 0;
    for (int i = 0; strTexto[i] != '\0'; i++) {
        if (strTexto[i] == '\n')
            strTexto[i] = '\0';
        tamanho++;
    }
    for (int i = 0; strBusca[i] != '\0'; i++) {
        if (strBusca[i] == '\n')
            strBusca[i] = '\0';
        sizeBusca++;
    }
    if (sizeBusca == 0 || sizeBusca > tamanho)
        return 0;
    int m = 0;
    int achou = 0;
    for (int i = 0; strTexto[i] != '\0'; i++) {

        if (strTexto[i] == strBusca[0]) {
            achou = 1;
            for (int j = 1; j < sizeBusca; j++) {
                if (strBusca[j] == strTexto[i + j])
                    achou++;
                else
                    break;
            }
            if (achou == sizeBusca) {
                qtdOcorrencias++;
                posicoes[m] = i + 1;
                m++;
                posicoes[m] = i + sizeBusca; 
                m++;
                i++; 
            }
        }
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int resultado=0;
    for (int i=0; num>0;i++){

        int resto = num%10;
        num/=10;

       resultado = (resultado*10)+resto;
    }
    return resultado;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias=0;
    int resultado=1;
    int copiaBase=numerobase;
    int copiaBusca=numerobusca;
    int potencia=1;

    for (int i=0;copiaBusca>0;i++) {
        potencia*=10;
        copiaBusca/=10;
    }
    for (int i = 0; copiaBase>0;i++){

        int resto = copiaBase%potencia;
        copiaBase/=10;
        
        if (resto == numerobusca) {
            qtdOcorrencias++;
        }
    }
    
    return qtdOcorrencias;
}



/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

int q7(char matriz[8][10], char palavra[5])
{
    int linhas = 8;
    int colunas = 10;
    int tamPalavra = 0;
   
    while(palavra[tamPalavra] != '\0'){
        tamPalavra++;
    }
 
    int direcaoLinha[8] = {0, 0, 1, -1, 1, -1, 1, -1};
    int direcaoColuna[8] = {1, -1, 0, 0, 1, -1, -1, 1};
 
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
    
            if(matriz[i][j] == palavra[0]){
                
                for(int dir = 0; dir < 8; dir++){
                    int encontrou = 1;
                    int linha = i;
                    int coluna = j;
                   
                    for(int k = 0; k < tamPalavra; k++){
                        
                        if(linha < 0 || linha >= linhas || 
                           coluna < 0 || coluna >= colunas){
                            encontrou = 0;
                            break;
                        }
                        
                        if(matriz[linha][coluna] != palavra[k]){
                            encontrou = 0;
                            break;
                        }
                        linha += direcaoLinha[dir];
                        coluna += direcaoColuna[dir];
                    }
                    
                    if(encontrou){
                        return 1;
                    }
                }
            }
        }
    }
    
    return 0;
}


DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}

