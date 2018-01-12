#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void MergeSort(tAHuffman *v, int p, int r)
{
   int q;

   if(p < r){
      q = (int)(p + r)/2.0f;
      MergeSort(v, p, q);
      MergeSort(v, q + 1, r);
      Merge(v, p, q, r);
   }
}

int Merge(int* v, int p, int q, int r)
{
   int i,
       j,
       k,
       n1 = q - p + 1;
       n2 = r - q;
   tNo *esq,
       *dir;

   if(!(esq = malloc((n1 + 1)*sizeof(tNo))) || !(dir = malloc((n2 + 1)*sizeof(tNo)))){
      printf("Problema na alocacao.");
      exit(1);
   }
   for(i = 0; i < n1; i++){
      esq[i]->quantidade = *v[p + i]->quantidade;
   }
   for(j = 0; j < n2; j++){
      dir[i]->quantidade = *v[q + 1 + j]->quantidade;
   }
   esq[n1]->quantidade = INT_MAX;
   dir[n2]->quantidade = INT_MAX;
   i = j = 0;
   for(k = p; k <= r; k++){
      if(esq[i]->quantidade <= dir[j]->quantidade){
         *v[k]->quantidade = esq[i];
         i++;
      }else{
         *v[k] = dir[j];
         j++;
      }
   }
   free(esq);
   free(dir);
}
int main(void)
{


   return 0;
}
