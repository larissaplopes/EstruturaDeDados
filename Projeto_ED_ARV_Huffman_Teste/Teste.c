#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void mergee(int *V, int inicio, int meio, int fim){
	 int *temp, p1, p2, tamanho, i, j, k;
	 int fim1 = 0, fim2 = 0;
	 tamanho = fim - inicio + 1;
	 p1 = inicio;
	 p2 = meio + 1;
	 temp = (int*) malloc(tamanho*sizeof(int));
	 if(temp != NULL){
 	 			for(i = 0; i < tamanho; i++){
						if(!fim1 && !fim2){
 									if(V[p1] < V[p2]){
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

void mergeSort(int *V, int inicio, int fim){
	  int meio;
	  if(inicio<fim){
  	  			 meio = floor((inicio + fim)/2);
  	  			 mergeSort(V, inicio, meio);
  	  			 mergeSort(V, meio + 1, fim);
  	  			 mergee(V, inicio, meio, fim);
	  }
}

/*int main(void){
	int vetor[10] = {1, 3, 7, 5, 8, 6, 4, 2, 9, 0};
	int inicio = 0;
	int fim = 9;
	int i;

	mergeSort(vetor, inicio, fim);

	for(i = 0; i < 10; i++){
		printf("%d ", vetor[i]);
	}
	return 0;
}*/
