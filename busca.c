#include <stdio.h>

int BuscaCar(char *car, tNo t)
{
   int tam,
       i;

   tam = sizeof(t.conteudo)/sizeof(t.conteudo[0]);

   for(i = 0; i < tam; i++){
      if(*car == t.conteudo[i]){
         return 1;
      }
   }
   return 0;
}

int Percorre(tNo *t, char *car, char *cod)
{
   tNo *aux = t;
   while(aux->esq || aux->dir){
      if(Busca(car, t->esq)){
         cod = 1;
         Percorre(t->esq, car, cod);
      }else{
         cod = 0;
         Percorre(t->dir, car, cod);
      }
   }
}
int main(void)
{


   return 0;
}
