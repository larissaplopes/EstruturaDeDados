#include <stdio.h>
#include <stdlib.h>
#include "ARVORE_HUFFMAN.h"

int criaElemNulo(tNo *nulo) {
	if(!(nulo->conteudo = malloc(sizeof(tNo))))
		return 0;
	else
		nulo->conteudo = '\0';
	nulo->quantidade = 0;
	nulo->esq = nulo->dir = NULL;
	return 1;
}

int criaFolhas(tAHuffman *arv) {
    int i;
	for(i = 0; i < ASCII; i++){
        arv[i] = NULL;
        arv[i] = malloc(sizeof(tNo));
        if(!arv[i])
            return 0;
		arv[i]->conteudo = malloc(sizeof(char));
		if(!arv[i]->conteudo)
			return 0;
		arv[i]->conteudo = i;
		arv[i]->quantidade = 0;
		arv[i]->esq = NULL;
		arv[i]->dir = NULL;
	}
	return 1;
}

void CriaRaiz(tNo *filho1, tNo *filho2) {
    int i;
    int tamParcial = (sizeof(filho1->conteudo)/sizeof(filho1->conteudo[0]));
    int tamanho = ((sizeof(filho1->conteudo)/sizeof(filho1->conteudo[0]))
        + sizeof(filho2->conteudo)/sizeof(filho2->conteudo[0]));
	tNo *novoNo = NULL;
	novoNo = malloc(sizeof(tNo));
	if(!novoNo)
        exit(1);
    novoNo->conteudo = malloc(tamanho*sizeof(char));
	if(!novoNo->conteudo){
		exit(1);
	}
	for(i = 0; i < tamanho; i++){
		if(i < sizeof(filho1->conteudo)/sizeof(filho1->conteudo[0]))
			novoNo->conteudo[i] = filho1->conteudo[i];
        else
			novoNo->conteudo[i] = filho2->conteudo[i - tamParcial];
    }
	novoNo->quantidade = filho1->quantidade + filho2->quantidade;
	novoNo->esq = filho1;
	novoNo->dir = filho2;
    filho1 = &elementoNeutro;
	filho2 = novoNo;
}
int Busca(char *car, tNo *t) {
    int tam, i;
    tam = sizeof(t->conteudo)/sizeof(t->conteudo[0]);
    for(i = 0; i < tam; i++){
        if(*car == t->conteudo[i]){
            return 1;
        }
    }
    return 0;
}

void Percorre(tNo *t, char *car, char *vetorCod, int *tam, int *i)
{

   tNo *aux = t;
	char *auxrealloc;
   while(aux->esq || aux->dir){
		if(Busca(car, aux->esq)){
			if(*i >= *tam){
				tam += ASCII;
				auxrealloc = realloc(vetorCod, tam);
				if(!auxrealloc){
					printf("PROBLEMA");
				}
				vetorCod = auxrealloc;
			}
         vetorCod[(*i)++] = 1;
         Percorre(aux->esq, car, vetorCod, tam, i);
      }else{
			if(*i >= *tam){
				tam += ASCII;
				auxrealloc = realloc(vetorCod, tam);
				if(!auxrealloc){
					printf("PROBLEMA");
				}
				vetorCod = auxrealloc;
			}
         vetorCod[(*i)++] = 0;
         Percorre(aux->dir, car, vetorCod, tam, i);
      }
   }
}
