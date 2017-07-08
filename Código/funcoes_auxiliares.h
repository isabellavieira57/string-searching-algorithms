/*----------------------------------------------------------------------*/
/* 			Universidade Federal de São João del - Rei 
				Algoritmos e Estrutura de Dados III
				Ciência da Computação - 3º período
					
				Processamento de Cadeias de Caracteres
				 Detecção de plágio em letras musicais
		    
					Isabella Vieira Ferreira
					 Mônica Neli de Resende
						Outubro / 2012                                  */
/*----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#ifndef funcoes_auxiliares_H
#define funcoes_auxiliares_H

typedef unsigned long long ull;			

/*----------------------------------------------------------------------*/
/* Estrutura de dados da música											*/
/*----------------------------------------------------------------------*/

typedef struct notas_musicais { 
	
	char nota_musical;
	char alteracao_cromatica;
	int distancia;
	
} notas_musicais;

typedef struct notas_musicais *Apontador;
typedef struct musica {
	
	Apontador inicio;
	int tamanho;
	
} musica;

/*----------------------------------------------------------------------*/
/* Estrutura da base musical - notas naturais.							*/
/*----------------------------------------------------------------------*/

// Célula
typedef struct base { 
	
	char nota_musical1;        // Nota 1
	char nota_musical2;		   // Nota 2
	int distancia;			   // Distância de meios-tons entre elas
	
} base;

typedef struct base *Ponteiro;

typedef struct Notas_naturais {
	
	Ponteiro inicio;
	
} Notas_naturais;


/*----------------------------------------------------------------------*/
/* Cabeçalho das funções do arquivo "funcoes_auxiliares.c".				*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
void leitura (FILE *entrada, musica *notas, musica *trecho);
/*----------------------------------------------------------------------*/
void imprimir (int posicao);
/*----------------------------------------------------------------------*/
void destruir_vetor_musica (musica *vetor);
/*----------------------------------------------------------------------*/
void iniciar (musica trecho, int next[]);
/*----------------------------------------------------------------------*/
void destruir_vetor_notas_naturais (Notas_naturais *vetor);
/*----------------------------------------------------------------------*/
void Processamento (Notas_naturais *VetorBase, musica *Vetor);
/*----------------------------------------------------------------------*/
void PreencheVetorBase(Notas_naturais *VetorBase);
/*----------------------------------------------------------------------*/

#endif
