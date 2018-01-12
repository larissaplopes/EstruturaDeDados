#ifndef ARVORE_HUFFMAN_H
#define ARVORE_HUFFMAN_H

#include <stdio.h>
#define ASCII 256

typedef struct no{
   char *conteudo;
   int quantidade;
   int codFilhos;
   struct no *esq,
             *dir;
}tNo;

typedef tNo* tAHuffman;

tNo elementoNeutro;
int contador;

extern int criaElemNulo(tNo *nulo);
extern int criaFolhas(tAHuffman *arv);
extern void CriaRaiz(tAHuffman *t);
extern void Percorre(tNo *t, char car, FILE* stream);
extern int Busca(char car, tNo *t);

#endif // ARVORE_HUFFMAN_H
