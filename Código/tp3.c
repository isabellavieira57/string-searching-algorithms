/*----------------------------------------------------------------------*/
/* 			Universidade Federal de São João del - Rei 
				Algoritmos e Estrutura de Dados III
				Ciência da Computação - 3º período
					
				Processamento de Cadeias de Caracteres
				 Detecção de plágio em letras musicais
		    
					Isabella Vieira Ferreira
					 Mônica Neli de Resende
						Outubro / 2012                                   */
/*----------------------------------------------------------------------*/

#include "funcoes_auxiliares.h"
#include "cadeia_caracteres.h"

#include <stdio.h>
#include <stdlib.h>


/*----------------------------------------------------------------------*/
/* Função principal.													*/
/*----------------------------------------------------------------------*/

int main (int argc, char *argv[]) {

	FILE *entrada;
	FILE *saida;
	musica nota, trecho;
	Notas_naturais VetorBase;
	int posicao=-2;
	
	char *arquivo_entrada;
	char *estrategia;

	arquivo_entrada = argv[1];
	estrategia = argv[2];	
	entrada = fopen(arquivo_entrada, "r");
	
	if ((entrada == NULL) || (estrategia[0] != '1' && estrategia[0] != '2' && estrategia[0] != '3' && estrategia[0] != '4')){
		
		printf ("\nParametro incorreto!\n\n");
		printf ("Para compilar voce deve digitar:\n");
		printf ("./tp3 <nome_do_arquivo_entrada> <estrategia>\n");
		printf ("\nA estrategia sera:\n");
		printf ("1 - para utilizar algoritmo Força Bruta;\n");
		printf ("2 - para utilizar algoritmo KMP;\n");
		printf ("3 - para utilizar algoritmo BMH;\n");
		printf ("4 - para utilizar algoritmo ShiftAndExato.\n\n");
			
		return 1;
		
	}
	
	//le a primeira vez
	leitura(entrada, &nota, &trecho);
	
	//cria um arquivo de saida
	saida = fopen ("saida.txt", "w");


	while (nota.tamanho != 0 && trecho.tamanho !=0) {
			
		PreencheVetorBase(&VetorBase);
		Processamento(&VetorBase, &nota);
		Processamento(&VetorBase, &trecho);
			
		if (estrategia[0] == '1') posicao = forca_bruta(nota,trecho);
		else if (estrategia[0] == '2') posicao = kmp(nota,trecho);
		else if (estrategia[0] == '3') posicao = BMH(&nota,&trecho);
		else posicao = ShiftAndExato (&nota,&trecho);
			
		imprimir(posicao);
		destruir_vetor_musica(&nota);
		destruir_vetor_musica(&trecho);
		destruir_vetor_notas_naturais(&VetorBase);
		
		leitura(entrada, &nota, &trecho);
	}
		
	fclose(entrada);
	
	return 1;
}
