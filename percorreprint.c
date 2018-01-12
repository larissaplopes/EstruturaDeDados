void Percorre(tNo *t, char car)
{
   tNo *aux = t;
	int i = 0;

      while(aux->esq && aux->dir){
            if(Busca(car, aux->esq)){
               printf("1");
               aux = aux->esq;
            }else{
               printf("0");
               aux = aux->dir;
            }
   }
}