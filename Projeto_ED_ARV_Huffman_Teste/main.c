#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LE_ARQUIVO.h"
#include "SELECTION_SORT.h"
#include "ARVORE_HUFFMAN.h"

extern tNo elementoNeutro;
int contador;

int main(void) {
	int i,
	    tamanho = 0,
	    cont = 0;
	char *arquivo,
         car,
         *vetorCod,
         *auxfinal;
	tAHuffman arAscii[256],
	          raiz;
    tNo filho1, filho2;
	criaFolhas(arAscii);

	FILE *f = fopen("teste.txt", "r");

	arquivo = leArquivo(f);
	printf("TESTE 1");
	for(i = 0; i < strlen(arquivo)+1; i++){
		car = arquivo[i];
		++arAscii[car]->quantidade;
	}
	printf("TESTE 2");
    selectionSort(arAscii, ASCII);
    criaElemNulo(&elementoNeutro);
    printf("TESTE 3");

    for(i = 0; i < ASCII; i++){
		if(arAscii[i]->quantidade){
			break;
		}
	}
	printf("TESTE 4 %d", i);

	contador = i;


	for(; contador < 255; ++contador){
 		CriaRaiz(arAscii[contador], arAscii[contador + 1]);
        selectionSort(arAscii, ASCII);
	}
	printf("TESTE 5");

	raiz = arAscii[contador];
	printf("TESTE 6");
	for(i = 0; i < strlen(arquivo)+1; i++) {
        Percorre(raiz, arquivo[i], vetorCod, &tamanho, &cont);
	}
	printf("TESTE 7");
	auxfinal = realloc(vetorCod, cont + 1);
	if(!auxfinal){
        printf("PROBLEMA FIM");
        exit(1);
	}
	printf("Codificacao: \n");
	for(int i = 0; i < sizeof(vetorCod)/sizeof(vetorCod[0]);i++){
        printf("%d", vetorCod[i]);
	}

	return 0;
}
