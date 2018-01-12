#include <stdio.h>


/* precisa ser somado +1 */
int ContaElemento(tAHuffman *t, int cont)
{
   int i;
   for(i = cont; t[i]->quantidade == t[i + 1]->quantidade; i++);
   return i;
}

void selectionSort(tAHuffman *arv, int numElem) {
    tNo *aux;
    int pos, i, j;

    for(i = 0; i < numElem - 1; i++){
        pos = i;
        for(j = i + 1; j < numElem; j++){
            if(arv[pos]->quantidade > arv[j]->quantidade)
                pos = j;
        }
        if(pos != i){
            aux = arv[i];
            arv[i] = arv[pos];
            arv[pos] = aux;
        }
    }
}

void ReorganizaElementos(tAHuffman *t, int cont)
{
   int i,
       verifica = 0,
       inicio;
   for(i = cont; i < ASCII - 1; i++){
      if(verifica == t[cont]->quantidade){
            continue;
      }else{
         ContaElemento(/* PREENCHER */);
         selectionSort(/* PREENCHER */);
      }
   }
}

int main(void)
{

   return 0;
}
