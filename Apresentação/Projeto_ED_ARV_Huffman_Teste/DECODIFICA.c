#include <stdio.h>
#include <stdlib.h>
#include "DECODIFICA.h"

void Decodifica(tNo *t, char *vetorCod)
{
	  tNo *aux = t;
	  int i = 0;
	  while (aux->esq != NULL || aux->dir != NULL){

	  		 if (vetorCod[i] == '1'){
	  		 	 i++;
	  		 	 aux = aux->esq;
  			 }else{
				 i++;
 		 		 aux = aux->dir;
		    }
	  }

}
