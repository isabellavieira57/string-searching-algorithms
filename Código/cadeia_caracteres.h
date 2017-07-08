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

#include "funcoes_auxiliares.h"

#ifndef cadeia_caracteres_H
#define cadeia_caracteres_H

/*----------------------------------------------------------------------*/
/* Cabeçalho das funções do arquivo "cadeia_caracteres.c".				*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
int forca_bruta (musica nota, musica trecho);
/*----------------------------------------------------------------------*/
int kmp (musica nota, musica trecho);
/*----------------------------------------------------------------------*/
int BMH (musica *nota, musica *trecho); 
/*----------------------------------------------------------------------*/
int ShiftAndExato (musica *nota, musica *trecho);
/*----------------------------------------------------------------------*/


#endif
