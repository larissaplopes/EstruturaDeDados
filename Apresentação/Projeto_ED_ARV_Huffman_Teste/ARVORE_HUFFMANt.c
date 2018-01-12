#include <stdio.h>
#include <stdlib.h>
#include "ARVORE_HUFFMAN.h"

int criaElemNulo(tNo *nulo) {
	if(!(nulo->conteudo = malloc(sizeof(tNo)))){
      printf("PROBLEMA!");
		return 0;
	}else{
      nulo->quantidade = 0;
      nulo->esq = nulo->dir = NULL;
	return 1;
	}
}

int criaFolhas(tAHuffman *arv) {
    int i;
	for(i = 0; i < ASCII; i++){
        arv[i] = malloc(sizeof(tNo));
        if(!arv[i])
            return 0;
		arv[i]->conteudo = malloc(sizeof(char));
		if(!arv[i]->conteudo)
			return 0;
		arv[i]->conteudo[0] = i;
		arv[i]->quantidade = 0;
		arv[i]->esq = NULL;
		arv[i]->dir = NULL;
	}
	return 1;
}

void CriaRaiz(tAHuffman *t) {

    int i,
        tamParcial = (sizeof(t[contador]->conteudo)/sizeof(t[contador]->conteudo[0])),
        tamanho = ((sizeof(t[contador]->conteudo)/sizeof(t[contador]->conteudo))
                   + sizeof(t[contador + 1]->conteudo)/sizeof(t[contador + 1]->conteudo));

	tNo *novoNo;

	novoNo = malloc(sizeof(tNo));
	if(!novoNo)
        exit(1);
    novoNo->conteudo = malloc(tamanho*sizeof(char));

	if(!novoNo->conteudo){
		exit(1);
	}

	for(i = 0; i < tamanho; i++){
		if(i < sizeof(t[contador]->conteudo)/sizeof(t[contador]->conteudo[0]))
			novoNo->conteudo[i] = t[contador]->conteudo[i];
        else
			novoNo->conteudo[i] = t[contador + 1]->conteudo[i - tamParcial];
   }

	novoNo->quantidade = t[contador]->quantidade + t[contador + 1]->quantidade;
	novoNo->esq = t[contador];
	novoNo->dir = t[contador + 1];
   t[contador] = &elementoNeutro;
	t[contador + 1] = novoNo;
}

int Busca(char car, tNo *t) {
    int tam, i;
    tam = sizeof(t->conteudo)/sizeof(t->conteudo[0]);
    for(i = 0; i < tam; i++){
        if(car == t->conteudo[i]){
            return 1;
        }
    }
    return 0;
}

void Percorre(tNo *t, char car, char *vetorCod, int *tam, int *i)
{
   tNo *aux = t;
   while(aux->esq && aux-dir){
      if(Busca(car, aux->esq)){
         vetorCod[*i++] = 1;
      }
   }
   if(aux->esq && aux->dir){
      if(Busca(car, aux->esq)){
         vetorCod[*i++] = 1;
      }else{
         vetorCod[*i++] = 0;
      }
   }
}

void Percorre(tNo *t, char car, char *vetorCod, int *tam, int *i)
{
   tNo *aux = t;
	char *auxrealloc;

      if(aux->esq && aux->dir){
            if(Busca(car, aux->esq)){
               if(*i == *tam){
                  tam += ASCII;
                  auxrealloc = (char *)realloc(vetorCod, tam);
                  if(!auxrealloc){
                     printf("PROBLEMA");
                  }
                  vetorCod = auxrealloc;
               }
                  vetorCod[(*i)++] = 1;
                  Percorre(aux->esq, car, vetorCod, tam, i);
            }else{
               if(*i == *tam){
                  tam += ASCII;
                  auxrealloc = (char *)realloc(vetorCod, tam);
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

void Percorre(tNo *t, char car)
{
   tNo *aux = t;
	int i;

      while(aux->esq && aux->dir){
            if(Busca(car, aux->esq)){
              printf("1");
              aux = aux->esq;
            }else{
              printf("0");
              aux = aux->dir;
            }
   }
}

