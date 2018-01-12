#include "SELECTION_SORT.h"

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
