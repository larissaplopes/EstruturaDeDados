#include <stdio.h>
#include <stdlib.h>
#include "ARVORE_HUFFMAN.h"

extern tNo elementoNeutro;

int criaElemNulo(tNo *nulo) {
	if(!(nulo->conteudo = calloc(1, sizeof(tNo)))){
      printf("PROBLEMA!");
		return 0;
	}else{
      nulo->quantidade = 0;
      nulo->esq = nulo->dir = NULL;
	return 1;
	}
}

int criaFolhas(tAHuffman *arv)
{
   int i;
	for(i = 0; i < ASCII; i++){
        arv[i] = malloc(sizeof(tNo));
        if(!arv[i])
            return 0;
		arv[i]->conteudo = calloc(1, sizeof(char));
		if(!arv[i]->conteudo)
			return 0;
		arv[i]->conteudo[0] = i;
		arv[i]->quantidade = 0;
		arv[i]->codFilhos = i;
		arv[i]->esq = NULL;
		arv[i]->dir = NULL;
	}
	return 1;
}

void CriaRaiz(tAHuffman *t) {

    int i,
        tamParcial = (sizeof(t[contador]->conteudo)/sizeof(t[contador]->conteudo[0])),
        tamanho = ((sizeof(t[contador]->conteudo)/sizeof(t[contador]->conteudo[0]))
                   + (sizeof(t[contador + 1]->conteudo)/sizeof(t[contador + 1]->conteudo[0])));

	tNo *novoNo;

	novoNo = malloc(sizeof(tNo));
	if(!novoNo)
        exit(1);
    novoNo->conteudo = calloc(tamanho, sizeof(char));

	if(!novoNo->conteudo){
		exit(1);
	}

	for(i = 0; i < tamanho; i++){
		if(i < tamParcial){
			novoNo->conteudo[i] = t[contador]->conteudo[i];
			novoNo->codFilhos += t[contador]->conteudo[i];
        }else{
			novoNo->conteudo[i] = t[contador + 1]->conteudo[i - tamParcial];
			novoNo->codFilhos += t[contador + 1]->conteudo[i - tamParcial];
     }
	}
	novoNo->quantidade = t[contador]->quantidade + t[contador + 1]->quantidade;
	if(t[contador]->codFilhos < t[contador + 1]->codFilhos){
      novoNo->esq = t[contador];
      novoNo->dir = t[contador + 1];
	}else{
	   novoNo->esq = t[contador + 1];
	   novoNo->dir = t[contador];
	}

   t[contador] = &elementoNeutro;
	t[contador + 1] = novoNo;
}

int Busca(char car, tNo *t)
{
    int tam, i;
    tam = sizeof(t->conteudo)/sizeof(t->conteudo[0]);
    for(i = 0; i < tam; i++){
        if(car == t->conteudo[i]){
            return 1;
        }
    }
    return 0;
}

void Percorre(tNo *t, char car, FILE *stream)
{
   tNo *aux = t;

   while(aux->esq && aux->dir){
      if(Busca(car, aux->esq)){
         printf("1");
         fprintf(stream, "%d", 1);
         aux = aux->esq;
      }else{
         printf("0");
         fprintf(stream, "%d", 0);
         aux = aux->dir;
     }
   }
}



