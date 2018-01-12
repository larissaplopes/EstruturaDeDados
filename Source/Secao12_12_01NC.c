#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME_ARQ      "AnedotaBulgara.txt"
#define TAMANHO_BLOCO 256

char *LeLinhaIlimitada(FILE *stream)
{
   char *ar = NULL,
        *p;
   int   tamanho = 0,
         c,
         i;

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

      if (feof(stream) || c == '\n') {
         break;
      }

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

int main(void)
{
   FILE *stream;
   char *linha;

   stream = fopen(NOME_ARQ, "r");

   if (!stream) {
      printf("\n\t>>> Arquivo nao pode ser aberto\n");
      return 1;
   }
   printf("\n\t\t*** Conteudo do Arquivo ***\n");

   linha = LeLinhaIlimitada(stream);

   for(int i; i < strlen(linha)+1; i++){
      printf("%c", linha+i);
   }
   free(linha);

   return 0;
}
