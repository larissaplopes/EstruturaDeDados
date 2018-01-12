#include <stdio.h>

typedef struct no{
   char *conteudo;
   int quantidade;
   struct no *esq,
             *dir;
}tNo;

void Cria_Folhas(tNo *ar)
{
   int i;
   for(i = 0; i < ASCII; i++){
      *ar[i]->conteudo = malloc(char);
      if(!(*ar[i]->conteudo)){
         printf("Impossivel criar os nos folhas");
         return 0;
      }
      *ar[i]->conteudo = i;
      *ar[i]->quantidade = 0;
      *ar[i]->esq = NULL;
      *ar[i]->dir = NULL;
   }
}

int main(void)
{


   return 0;
}
