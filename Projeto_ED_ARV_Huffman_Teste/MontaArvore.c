#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ASCII 256
#define TAMANHO_BLOCO 256

typedef struct no{
	char *conteudo;
	int quantidade;
	struct no *esq,
				*dir;
}tNo;

typedef tNo* tAHuffman;

tNo elementoNeutro;

int contador;

void CriaElemNulo(tNo *nulo) {
	if(!(nulo->conteudo = malloc(sizeof(tNo))))
		printf("\nProblema na alocacao");
	else
		nulo->conteudo = '\0';  
	nulo->quantidade = 0;
	nulo->esq = nulo->dir = NULL;
}

void Cria_Folhas(tAHuffman *ar) {
	int i;
	for(i = 0; i < ASCII; i++){
		*ar[i]->conteudo = malloc(sizeof(char));
		if(!(*ar[i])) 
			printf("Impossivel criar os nos folhas");
		ar[i]->conteudo = i;
		ar[i]->quantidade = 0;
		ar[i]->esq = NULL;
		ar[i]->dir = NULL;
	}	
}


int CriaRaiz(tNo *filho1, tNo *filho2) {
	tNo *novoNo;
	int tamanho;
	int tamParcial = (sizeof(filho1->conteudo)/sizeof(filho1->conteudo[0]));
	int i;
	tamanho = ((sizeof(filho1->conteudo)/sizeof(filho1->conteudo[0])) + sizeof(filho2->conteudo) + sizeof(filho2->conteudo[0]));
    novoNo->conteudo = realloc(novoNo->conteudo, tamanho);
	if(!novoNo->conteudo)
		return 0;
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
	return 1;
}


char *LeArquivo(FILE *stream) {
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

//int AchaCaractere(char *arquivo, )

int main(void) {
	int i;
	char *arquivo, car;
	tAHuffman arAscii[256], raiz;
	FILE *f = fopen("teste.txt", "r");
	
	arquivo = LeArquivo(f);
	for(i = 0; i < strlen(arquivo); i++){
		car = arquivo[i];
		++arAscii[car]->quantidade;
	}

	MergeSort();

	for(i = 0; i < ASCII; i++){
		if(arAscii[i]->quantidade){
			break;
		}
	}

	contador = i;

	for(; contador < ASCII - 1; contador++){
		CriaRaiz(arAscii[contador], arAscii[contador + 1]);
	}
	raiz = arAscii[contador];
	return 0;
}
