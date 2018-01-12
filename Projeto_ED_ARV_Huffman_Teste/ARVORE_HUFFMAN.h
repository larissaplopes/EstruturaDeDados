#ifndef ARVORE_HUFFMAN_H
#define ARVORE_HUFFMAN_H
#define ASCII 256

typedef struct no{
   char *conteudo;
   int quantidade;
   struct no *esq,
             *dir;
}tNo;

typedef tNo* tAHuffman;

tNo elementoNeutro;

extern int criaElemNulo(tNo *nulo);
extern int criaFolhas(tAHuffman *arv);
extern void CriaRaiz(tNo *filho1, tNo *filho2);
extern void Percorre(tNo *t, char *car, char *vetorCod, int *tam, int *i);
extern int Busca(char *car, tNo *t);

#endif // ARVORE_HUFFMAN_H
