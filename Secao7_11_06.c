/****
 *
 * T�tulo: Bubble Sort
 *
 * Autor: Ulysses de Oliveira
 *
 * Data de Cria��o: 16/06/2012
 * �ltima modifica��o: 16/06/2012
 *
 * Descri��o: Implementa��o do m�todo de ordena��o da bolha
 *
 * Entrada: Nada
 *
 * Sa�da: Um array antes e depois da ordena��o
 *
 ****/

#include <stdio.h>

/****
 *
 * BubbleSort(): Ordena em ordem crescente um array de
 *               elementos do tipo int utilizando o
 *               m�todo de ordena��o da bolha (Bubble Sort)
 *
 * Par�metros:
 *      ar (entrada e sa�da) - array que ser� ordenado
 *      nElementos (entrada) - n�mero de elementos do array
 *
 * Retorno: Nada
 *
 * Observa��o: Esse � o m�todo de ordena��o mais simples
 *             de entender (e explicar), mas ele � um
 *             dos mais ineficientes.
 *
 ****/
void BubbleSort(tAHuffman ar[], int nElementos)
{
   tAHuffman aux;

   aux = malloc(sizeof(tAHuffman));
   if(!aux){
      printf("Problema!");
   }
   int i,
       ordenado = 0; /* Informar� se o array est�   */
                     /* ordenado. � importante que  */
                     /* essa vari�vel seja iniciada */
                     /* com zero (v. abaixo).       */

   /******************************************************/
   /*                                                    */
   /* Sup�e-se que inicialmente o array est� ordenado    */
   /* fazendo-se 'ordenado = 1'. Ent�o, se forem         */
   /* encontrados dois elementos fora de ordem, atribui- */
   /* se novamente zero a 'ordenado', trocam-se os       */
   /* elementos de posi��o e recome�a-se a verifica��o   */
   /* de ordem do array.                                 */
   /*                                                    */
   /******************************************************/

      /* O la�o encerra quando a vari�vel */
      /* 'ordenado' for diferente de 0    */
   while (!ordenado) {
         /* Sup�e que o array est� ordenado */
      ordenado = 1;

      /*************************************************/
      /*                                               */
      /* Compara cada elemento do array com o elemento */
      /* seguinte. Se for encontrado um elemento menor */
      /* do que seu antecessor, os dois elementos      */
      /* trocam de posi��o e o array � considerado     */
      /* fora de ordem (i.e., 'ordenado' assume zero). */
      /*                                               */
      /*************************************************/

      for (i = 0; i < nElementos - 1; i++){
            /* Compara cada elemento com */
            /* o elemento seguinte       */
         if (ar[i]->quantidade > ar[i+1]->quantidade){
               /* Pelo menos dois elementos */
               /* est�o fora de ordem       */
            ordenado = 0;

               /* Troca elementos adjacentes */
            aux = ar[i];
            ar[i] = ar[i+1];
            ar[i+1] = aux;
         }  /* if */
      } /* for */
   } /* while */
}

/****
 *
 * main(): Testa a fun��o BubbleSort()
 *
 * Par�metros: Nenhum
 *
 * Retorno: Zero
 *
 ****/
int main(void)
{
   int array[] = {12, 55, 21, 1, 6, 8, 17, 220, 5, 83},
       i, tamanho;

      /* Apresenta o programa */
   printf( "\n\t>>> Este programa ordena um array de"
           "\n\t>>> inteiros usando o metodo da bolha.\n" );

      /* Calcula do tamanho do array */
   tamanho = sizeof(array)/sizeof(array[0]);

      /* Apresenta o array antes da ordena��o */
   printf("\n\t>>> Array Original <<<\n\n\t> ");
   for (i=0; i < tamanho; i++) {
      printf("%d   ", array[i]);
   }

      /* Ordena o array */
   BubbleSort(array, tamanho);

      /* Apresenta o array depois da ordena��o */
   printf("\n\n\t>>> Array Ordenado <<<\n\n\t> ");
   for (i=0; i < tamanho; i++) {
      printf("%d   ", array[i]);
   }

   return 0;
}

/******************* Exemplo de Execu��o ******************

        >>> Este programa ordena um array de
        >>> inteiros usando o metodo da bolha.

        >>> Array Original <<<

        > 12   55   21   1   6   8   17   220   5   83

        >>> Array Ordenado <<<

        > 1   5   6   8   12   17   21   55   83   220

**********************************************************/
