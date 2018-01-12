#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    char conteudo;
    struct no *esq,
              *dir;
}tNo;

typedef struct arvoreBi{
    tNo raiz;
    int n;
}tAB;

int InsereEsq(tAB *aB, char vPai, char vFilho)
{
    tNo *p;

    /* Este if faz uso da propriedade */
    /* de curto-circuito dos opera-   */
    /* dores logicos, neste caso, OU  */

         /* Verifica se ja existe */
         /* o dado a ser inserido */
    if( ( busca(aB->raiz, vFilho)  ||
         /* Verifica a existencia */
         /* do pai                */
          !(p = busca(aB->raiz, vPai) ) ||
         /* Verifica se o no-filho   */
         /* sinistro esta preenchido */
          p->esq ||
         /* Verifica se o no-filho   */
         /* foi alocado corretamente */
          !(p->esq = malloc( sizeof(tNo) ) )
         ) ) {

        return 0;

    }else{
        p->esq->conteudo = vFilho;
        p->esq->esq = p->esq->dir = NULL;
        aB->n++;
        return 1;
    }
}
