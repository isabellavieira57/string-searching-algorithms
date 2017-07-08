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

#include "funcoes_auxiliares.h"

/*--------------------------------------------------------------------*/
/* Função responsável por fazer a leitura do arquivo. 
   Retorna um vetor de char contendo as letras musicais.			  */
/*--------------------------------------------------------------------*/

void leitura (FILE *entrada, musica *notas, musica *trecho) {
	
	char aux;
	int i;
	int t, m;
	
	
	// Lendo quantidade de notas e tamanho do trecho suspeito
	fscanf(entrada, "%d" , &m);
	fscanf (entrada, "%c",&aux); 					// Espaço
	fscanf(entrada, "%d" , &t); 					
	
	// Atribuição dos tamanhos
	notas->tamanho = m;
	trecho->tamanho = t;
	
	// Se não for fim de arquivo
	if (m!=0 && t!=0) {
	
		fscanf(entrada,"%c", &aux);
		
		// Jogando os espaços fora
		while (aux != '\n') fscanf(entrada,"%c", &aux);
			
		// Criando vetor de char para armazenar as notas musicais
		notas->inicio = (notas_musicais *) malloc (sizeof(notas_musicais)*m);
		
		// Lendo todos os valores de notas musicais
		for (i = 0; i<m; i++) {
			
			fscanf(entrada,"%c", &aux);
			
			// Nota
			notas->inicio[i].nota_musical =  aux;
			fscanf(entrada,"%c", &aux);
			
			if (aux != ' ' && aux != '\n') {
			
					notas->inicio[i].alteracao_cromatica = aux; 	// Recebe sustenido ou bemol
					fscanf(entrada,"%c", &aux);
					
			} else 	notas->inicio[i].alteracao_cromatica = '*';  		// Onde nao tem sustenido ou bemol, tem '*'
		}
		
		// Criando vetor de char para armazenar as notas musicais
		trecho->inicio = (notas_musicais *) malloc (sizeof(notas_musicais)*t);
	
		for (i = 0; i<t; i++) {
			
			fscanf(entrada,"%c", &aux);
			
			// Nota
			trecho->inicio[i].nota_musical =  aux;
			fscanf(entrada,"%c", &aux);
			
			if (aux != ' ' && aux!= '\n') {
			
					trecho->inicio[i].alteracao_cromatica = aux; 	// Recebe sustenido ou bemol
					fscanf(entrada,"%c", &aux); 					// Le espaço
					
			} else 	trecho->inicio[i].alteracao_cromatica = '*';  	// Onde nao tem sustenido ou bemol, tem '*'
		}	 		
	}

	return;
}

/*--------------------------------------------------------------------*/
/* Função responsável por imprimir no arquivo os resultados.		  */
/*--------------------------------------------------------------------*/

void imprimir (int posicao) {		// Posicao é onde ocorre o casamento
			
	FILE *saida;	
	saida = fopen ("saida.txt", "a");
	char string[] = "Trecho maior do que a WORD da memoria - ";
	char bits[] = " bits!";
			
	// Se posicao for -1, nao ha casamento
	if (posicao == -1) fprintf (saida, "%c\n", 'N');
	else if (posicao == -99) fprintf (saida, "%s %u %s\n", string, sizeof(ull)*8, bits);			
	else fprintf (saida, "%c %d\n", 'S', posicao);
	
	fclose (saida);
}

/*--------------------------------------------------------------------*/
/* Funções responsáveis por destruir o vetor.						  */
/*--------------------------------------------------------------------*/

void destruir_vetor_musica (musica *vetor) {
	
	free (vetor->inicio);
	return;

}

void destruir_vetor_notas_naturais (Notas_naturais *vetor) {
	
	free (vetor->inicio);	
	return;

}

/*--------------------------------------------------------------------*/
/* Função auxiliar para o algoritmo KMP.				              */
/*--------------------------------------------------------------------*/

void iniciar (musica trecho, int next[]) {
	
	int i = 0,j=-1;
	next[0] = -1;

	// Calculando os deslocamentos 
	while (i < trecho.tamanho-1) {
	
			if ((j==-1) || (trecho.inicio[i].distancia == trecho.inicio[j].distancia)) {
		
				i++;
				j++;
				next[i] = j;
				
		} else j = next[j];
	}
}

/*------------------------------------------------------------------------------------------------*/
/* Processamento do texto e do trecho para obter as distancias em meio-tons de duas em duas notas.*/
/*------------------------------------------------------------------------------------------------*/

void PreencheVetorBase(Notas_naturais *VetorBase){
	
	// Criando vetor base
	VetorBase->inicio = (base *) malloc (sizeof(base)*8);

	// Preenchendo o vetor com as sete notas principais
	VetorBase->inicio[1].nota_musical1 = 'A';
	VetorBase->inicio[1].nota_musical2 = 'B';
	VetorBase->inicio[1].distancia = 2;
		
	VetorBase->inicio[2].nota_musical1 = 'B';
	VetorBase->inicio[2].nota_musical2 = 'C';
	VetorBase->inicio[2].distancia = 1;
		
	VetorBase->inicio[3].nota_musical1 = 'C';
	VetorBase->inicio[3].nota_musical2 = 'D';
	VetorBase->inicio[3].distancia = 2;
	
	VetorBase->inicio[4].nota_musical1 = 'D';
	VetorBase->inicio[4].nota_musical2 = 'E';
	VetorBase->inicio[4].distancia = 2;
	
	VetorBase->inicio[5].nota_musical1 = 'E';
	VetorBase->inicio[5].nota_musical2 = 'F';
	VetorBase->inicio[5].distancia = 1;

	VetorBase->inicio[6].nota_musical1 = 'F';
	VetorBase->inicio[6].nota_musical2 = 'G';		
	VetorBase->inicio[6].distancia = 2;

	VetorBase->inicio[7].nota_musical1 = 'G';
	VetorBase->inicio[7].nota_musical2 = 'A';
	VetorBase->inicio[7].distancia = 2;
		
}

/*------------------------------------------------------------------------------------------------*/
/* Processamento do texto e do trecho para obter as distancias em meio-tons de duas em duas notas.*/
/* Compara-se uma posição com a próxima.                                                          */
/*------------------------------------------------------------------------------------------------*/

void Processamento (Notas_naturais *VetorBase, musica *Vetor){
	
	int i, j = 1;
	int achou = 1;
	int flag = 0;
	
	Vetor->inicio[Vetor->tamanho-1].distancia = 0;
	
	for (i = 0; i < Vetor->tamanho-1; i++){
		
		j = 1;
		achou = 1;
		flag = 0;
		
		// Se a alteração cromatica for bemol então soma-se um meio-tom - começa do meio-tom anterior
		if (Vetor->inicio[i].alteracao_cromatica == 'b') Vetor->inicio[i].distancia = 1;
		
		// Se a alteração cromatica for bemol então subtrai-se um meio-tom - começa de um meio-tom acima
		else if (Vetor->inicio[i].alteracao_cromatica == '#') Vetor->inicio[i].distancia = -1;
				
		else Vetor->inicio[i].distancia = 0;
		
		// Se as notas forem iguais então a distancia em meio-tons entre elas é zero
		if ((Vetor->inicio[i].nota_musical == Vetor->inicio[i+1].nota_musical) && (Vetor->inicio[i].alteracao_cromatica == Vetor->inicio[i+1].alteracao_cromatica)){
	
			Vetor->inicio[i].distancia = 0;
			
		// Se não forem iguais obtem-se a distancia 
		} else {
			// Se as notas forem iguais porém a alteração comática nao for
			if ((Vetor->inicio[i].nota_musical == Vetor->inicio[i+1].nota_musical) && ((Vetor->inicio[i].alteracao_cromatica != '#' ) && (Vetor->inicio[i+1].alteracao_cromatica != '*'))) {
				achou = 0;
				flag = 1;
				
				if ((Vetor->inicio[i].alteracao_cromatica == 'b') &&	(Vetor->inicio[i+1].alteracao_cromatica == '#')) Vetor->inicio[i].distancia = 2;
				else if ((Vetor->inicio[i].alteracao_cromatica == 'b') &&	(Vetor->inicio[i+1].alteracao_cromatica == '*')) Vetor->inicio[i].distancia = 1;
				else if ((Vetor->inicio[i].alteracao_cromatica == '*') &&	(Vetor->inicio[i+1].alteracao_cromatica == '#')) Vetor->inicio[i].distancia = 1;			
				else { achou = 1; flag = 0;	}						
			
			}else{
				// Verificando com a primeira Nota do vetor base
				 if (Vetor->inicio[i].nota_musical == VetorBase->inicio[j].nota_musical1){
				
						j = 0;
						achou = 0;	
				} 
			
				// Procurando pela primeira nota			
				while (achou == 1){
				
					if (Vetor->inicio[i].nota_musical == VetorBase->inicio[j].nota_musical2) achou = 0;				
					if (achou == 1) j++;
						
				}
				
				achou = 1;
				
				// Procurando a segunda a partir da proxima célula do vetor base - o j continua de onde parou acima + 1
				j = j + 1;

				// Procurando pela segunda nota e incrementando a distancia
				while (achou == 1 && flag == 0){
				
					if (Vetor->inicio[i+1].nota_musical == VetorBase->inicio[j].nota_musical2){
						
						achou = 0;
									
						// Se a alteração cromatica for bemol então soma-se um meio-tom
						if (Vetor->inicio[i+1].alteracao_cromatica == 'b') Vetor->inicio[i].distancia = Vetor->inicio[i].distancia + VetorBase->inicio[j].distancia - 1;
						
						// Se a alteração cromatica for bemol então subtrai-se um meio-tom
						else if (Vetor->inicio[i+1].alteracao_cromatica == '#') Vetor->inicio[i].distancia = Vetor->inicio[i].distancia + VetorBase->inicio[j].distancia + 1;
						
						else Vetor->inicio[i].distancia = Vetor->inicio[i].distancia + VetorBase->inicio[j].distancia;					
						
					} else Vetor->inicio[i].distancia = Vetor->inicio[i].distancia + VetorBase->inicio[j].distancia;
					
					// Para voltar ao inicio do vetor
					j= (j % 7) + 1;
	
					
				}
				
			}//else
			
		} //Else
		
	} //For

	return;
	
}
