#include <stdio.h>
#include "LE_ARQUIVO.h"

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
