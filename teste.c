#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAMANHO_BLOCO 256
#define ASCII 256

typedef struct no{
   char *conteudo;
   int quantidade;
   struct no *esq;
   struct no *dir;
}tNo;

typedef tNo *tAHuffman;

void MergeSort(tAHuffman *V, int inicio, int fim){
	  int meio;
	  if(inicio<fim){
  	  			 meio = floor((inicio + fim)/2);
  	  			 MergeSort(V, inicio, meio);
  	  			 MergeSort(V, meio + 1, fim);
  	  			 MergeS(V, inicio, meio, fim);
	  }
}

void MergeS(tAHuffman *V, int inicio, int meio, int fim){
	 tAHuffman *temp;
	 int p1, p2, tamanho, i, j, k;
	 int fim1 = 0, fim2 = 0;
	 tamanho = fim - inicio + 1;
	 p1 = inicio;
	 p2 = meio + 1;
	 temp = calloc(tamanho, sizeof(tAHuffman));
	 if(temp){
 	 			for(i = 0; i < tamanho; i++){
						if(!fim1 && !fim2){
 									if(V[p1]->quantidade < V[p2]->quantidade){
												temp[i] = V[p1++];
 									}else{
 										temp[i] = V[p2++];
 									}
 									if(p1 > meio){
					 						fim1 = 1;
							  		}
							  		if(p2 > fim){
							  				fim2 = 1;
							  		}
					  }else{
					  		  if(!fim1){
				  		  	  				temp[i] = V[p1++];
							  }else{
							  		  temp[i] = V[p2++];
							  }
					  }
 	 			}
	 			for(j = 0, k = inicio; j < tamanho; j++, k++){
	 				V[k] = temp[j];
	 			}
	 }
	 free(temp);
}

char* leArquivo(FILE *stream) {
	char *ar = NULL, *p;
	int tamanho = 0, c, i;
	for (i = 0; ; ++i) {
		c = fgetc(stream);
		if (ferror(stream)) {
			free(ar);
			return NULL;
		}
		if (i > tamanho - 2) {
			p = realloc(ar, tamanho + TAMANHO_BLOCO);
			if (!p) {
				free(ar);
				return NULL;
			}
			ar = p;
			tamanho = tamanho + TAMANHO_BLOCO;
		}
		if (feof(stream))
			break;
		ar[i] = c;
	}
	if (feof(stream) && !i) {
		free(ar);
		return NULL;
	}
	ar[i] = '\0';
	p = realloc(ar, i + 1);
	return p ? p : ar;
}


int criaElemNulo(tNo *nulo) {
	if(!(nulo->conteudo = malloc(sizeof(tNo))))
		return 0;
	else
		nulo->conteudo = '\0';
	nulo->quantidade = 0;
	nulo->esq = nulo->dir = NULL;
	return 1;
}

int Cria_Folhas(tAHuffman *ar) {
    int i;
	for(i = 0; i < ASCII; i++){
        ar[i] = NULL;
        ar[i] = malloc(sizeof(tNo));
        if(!ar[i])
            return 0;
		ar[i]->conteudo = malloc(sizeof(char));
		if(!ar[i]->conteudo)
			return 0;
		ar[i]->conteudo = i;
		ar[i]->quantidade = 0;
		ar[i]->esq = NULL;
		ar[i]->dir = NULL;
	}
	return 1;
}

tNo* criaRaiz(tNo *filho1, tNo *filho2) {
    int i;
    int tamParcial = (sizeof(filho1->conteudo)/sizeof(filho1->conteudo[0]));
    int tamanho = ((sizeof(filho1->conteudo)/sizeof(filho1->conteudo[0]))
        + sizeof(filho2->conteudo) + sizeof(filho2->conteudo[0]));
	tNo *novoNo = NULL, *elementoNeutro = NULL;
	criaElemNulo(elementoNeutro);
	novoNo = malloc(sizeof(tNo));
	if(!novoNo)
        return NULL;
    novoNo->conteudo = realloc(novoNo->conteudo, tamanho);
	if(!novoNo->conteudo)
		return NULL;
	for(i = 0; i < tamanho; i++){
		if(i < sizeof(filho1->conteudo)/sizeof(filho1->conteudo[0]))
			novoNo->conteudo[i] = filho1->conteudo[i];
        else
			novoNo->conteudo[i] = filho2->conteudo[i - tamParcial];
    }
	novoNo->quantidade = filho1->quantidade + filho2->quantidade;
	novoNo->esq = filho1;
	novoNo->dir = filho2;
    filho1 = elementoNeutro;
    filho2 = novoNo;
	return novoNo;
}

int main() {
    char *str, car;
    tAHuffman ar[256];
    FILE *f = fopen("teste.txt", "r");
    str = leArquivo(f);
    Cria_Folhas(ar);
    for(int i = 0; i <= strlen(str); i++){
		car = str[i];
		++ar[car]->quantidade;
	}
    for(int i = 0; i < 256; i++){
        printf("\n%c %d", ar[i]->conteudo, ar[i]->quantidade);
    }
    printf("\n\n ORDENACAO \n\n");
    MergeSort(ar, 0, 255);
    printf("\n");
    for(int i = 0; i < 256; i++){
        printf("\n%c %d", ar[i]->conteudo, ar[i]->quantidade);
    }
    return 0;
}
