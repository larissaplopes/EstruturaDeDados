void MergeSort(tAHuffman *V, int inicio, int fim){
	  int meio;
	  if(inicio<fim){
  	  			 meio = floor((inicio + fim)/2);
  	  			 MergeSort(V, inicio, meio);
  	  			 MergeSort(V, meio + 1, fim);
  	  			 Merge(V, inicio, meio, fim);
	  }
}

void Merge(tAHuffman *V, int inicio, int meio, int fim){
	 tAHuffman *temp;
	 int p1, p2, tamanho, i, j, k;
	 int fim1 = 0, fim2 = 0;
	 tamanho = fim - inicio + 1;
	 p1 = inicio;
	 p2 = meio + 1;
	 temp = calloc(tamanho, sizeof(tAHuffman));
	 if(temp){
 	 			for(i = 0; i < tamanho; i++){
						if(!fim1 && !fim2){
 									if(V[p1]->quantidade < V[p2]->quantidade){
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


