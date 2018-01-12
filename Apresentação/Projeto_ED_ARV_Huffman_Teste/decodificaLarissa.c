	codigo = fopen("cod.txt", "r");

	arquivo2 = leArquivo(codigo);

	aux = arAscii[contador];

	printf("\n");
	for(i = 0; i < strlen(arquivo2)+1; i++){
      if(aux->esq && aux->dir){
         if(arquivo2[i] == '1'){
            aux = aux->esq;
         }else{
            aux = aux->dir;
         }
      }else{
         printf("%c", aux->conteudo[0]);
         aux = arAscii[contador];
      }
	}
