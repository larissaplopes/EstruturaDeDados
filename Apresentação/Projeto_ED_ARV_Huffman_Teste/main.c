#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LE_ARQUIVO.h"
#include "DECODIFICA.h"
#include "SELECTION_SORT.h"
#include "ARVORE_HUFFMAN.h"

extern tNo elementoNeutro;
extern int contador;

int main(void) {
	int i;
//	    tamanho;
//	    *cod,
//	    *auxcod,
//	    cont = 0;
	char *arquivo,
	     *arquivo2,
         car;
	tAHuffman arAscii[256];
	tNo *raiz,
	    *aux;
	criaFolhas(arAscii);

	FILE *f = fopen("teste.txt", "r"),
	     *codigo = fopen("cod.txt", "w");
   rewind(codigo);

//	if(!(cod = malloc(1 * sizeof(int)))){
//        printf("PROBLEMA!");
//	}

//	tamanho = sizeof(cod)/sizeof(cod[0]);

	arquivo = leArquivo(f);
	for(i = 0; i < strlen(arquivo)+1; i++){
		car = arquivo[i];
		++arAscii[car]->quantidade;
	}
    selectionSort(arAscii, ASCII);
    criaElemNulo(&elementoNeutro);

    for(i = 0; i < ASCII; i++){
		if(arAscii[i]->quantidade){
			break;
		}
	}

	contador = i;

	for(; contador < 255; contador++){
      if(arAscii[contador]->quantidade){
         CriaRaiz(arAscii);
         selectionSort(arAscii, ASCII);
      }else{
         continue;
      }
	}

	raiz = arAscii[contador];

	printf("\nCodificacao: \n");
	for(i = 0; i < strlen(arquivo)+1; i++) {
        Percorre(raiz, arquivo[i], codigo);
	}

	fclose(codigo);

	codigo = fopen("cod.txt", "r");

	arquivo2 = leArquivo(codigo);

	aux = arAscii[contador];

	printf("\n");
	for(i = 0; i < strlen(arquivo2)+1; i++){
      if(aux->esq && aux->dir){
         if(arquivo2[i] == '1'){
            aux = aux->esq;
         }else{
            aux = aux->dir;
         }
      }else{
         printf("%c", aux->conteudo[0]);
         aux = arAscii[contador];
      }
	}

	printf("\n");

	return 0;
}
