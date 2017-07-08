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

#include "cadeia_caracteres.h"

/*----------------------------------------------------------------------*/
/* Algoritmo Força Bruta.												*/
/*----------------------------------------------------------------------*/

int forca_bruta (musica nota, musica trecho) {
	
	int i, j, k, tamanho;
		
	tamanho = (nota.tamanho - trecho.tamanho) + 1;
	
	for (i=0; i < tamanho; i++) {
		
		k = i;
		j=0;
		
		while ((nota.inicio[k].distancia == trecho.inicio[j].distancia) && (j < (trecho.tamanho-1))) {
			j++;
			k++;
		}
	
		if (j == (trecho.tamanho-1)) return (i);
	}
	
	return (-1);	
}


/*----------------------------------------------------------------------*/
/* Algoritmo KMP														*/
/*----------------------------------------------------------------------*/

int kmp (musica nota, musica trecho) {
	
	int i=0,j=0;
	int next[trecho.tamanho];
			
	iniciar(trecho,next);
	
	// Enquanto não houver casamento e não chegar ao fim do texto
	while ((i<nota.tamanho)  && (j< trecho.tamanho-1)) {

		if ((j==-1) || (nota.inicio[i].distancia == trecho.inicio[j].distancia)) {
			
			i++;
			j++;
			
		} else j = next[j];		
	}
			
	if (j==trecho.tamanho-1) return((i+1) - trecho.tamanho);
	
	return (-1);	
}

/*----------------------------------------------------------------------*/
/* Algoritmo Boyer-Moore (BMH).											*/
/*----------------------------------------------------------------------*/

int BMH (musica *nota, musica *trecho) {
	
	int i,j,k;
	char d[12];
				
	// Inicialização do vetor deslocamentos d[]
	for (j=0; j<= 11; j++) d[j] = trecho->tamanho-1;
	
	// Cálculo dos deslocamentos para cada distância do trecho				
	for (j=1; j < (trecho->tamanho-1);j++) d[trecho->inicio[j-1].distancia] = (trecho->tamanho - 1) - j;
					
	i = trecho->tamanho-2;
	
	// Pesquisa
	while ((i < nota->tamanho) && (i>0)) {
		
		k = i;
		j = trecho->tamanho-2;
		
		while ( (nota->inicio[k].distancia == trecho->inicio[j].distancia) && (j >= 0) ) {
			k--;
			j--;
		}
		
		if (j == -1) return(k+1);
						
		i = i + d[nota->inicio[i].distancia];
	}
	
	return (-1);
}

/*----------------------------------------------------------------------*/
/* Algoritmo ShiftAndExato.												*/
/*----------------------------------------------------------------------*/
		
int ShiftAndExato (musica *nota, musica *trecho){
	
	ull Mascara[12];						// Tabela de mascara para cada distancia possivel
	int i;									// Contador 
	ull R;									// Automato - Conjunto para armazenar o casamento de bit
	
	// Limite de tamanho da WORD - int !
	if (trecho->tamanho > sizeof(ull)*8) return -99;

	// Inicializando a Mascara
	for (i=0; i < 12; i++)
		Mascara[i] = 0ULL;
		
	// Preenchimento da máscara segundo o alfabeto
	for (i = 0; i < trecho->tamanho-1; i++)
		Mascara[trecho->inicio[i].distancia] |= ( 1ULL << (trecho->tamanho-i-2) );
		
	// Pesquisa no texto
	R = 0LL;
	for (i = 0; i < nota->tamanho-1; i++) {
		
		// Verificando se há casamento através de operações lógicas bit-a-bit
		R = ( (R >> 1) | (1ULL << (trecho->tamanho - 2)) ) & (Mascara[nota->inicio[i].distancia]);
		
		// Se o ultimo caractere for ativado(igual a 1) então houve o casamento exato do padrao
		if ((R & 1ULL) != 0) return (i - trecho->tamanho+2);
		
	}
	
	return(-1);
}
