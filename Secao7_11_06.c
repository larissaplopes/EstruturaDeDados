/****
 *
 * Título: Bubble Sort
 *
 * Autor: Ulysses de Oliveira
 *
 * Data de Criação: 16/06/2012
 * Última modificação: 16/06/2012
 *
 * Descrição: Implementação do método de ordenação da bolha
 *
 * Entrada: Nada
 *
 * Saída: Um array antes e depois da ordenação
 *
 ****/

#include <stdio.h>

/****
 *
 * BubbleSort(): Ordena em ordem crescente um array de
 *               elementos do tipo int utilizando o
 *               método de ordenação da bolha (Bubble Sort)
 *
 * Parâmetros:
 *      ar (entrada e saída) - array que será ordenado
 *      nElementos (entrada) - número de elementos do array
 *
 * Retorno: Nada
 *
 * Observação: Esse é o método de ordenação mais simples
 *             de entender (e explicar), mas ele é um
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
       ordenado = 0; /* Informará se o array está   */
                     /* ordenado. É importante que  */
                     /* essa variável seja iniciada */
                     /* com zero (v. abaixo).       */

   /******************************************************/
   /*                                                    */
   /* Supõe-se que inicialmente o array está ordenado    */
   /* fazendo-se 'ordenado = 1'. Então, se forem         */
   /* encontrados dois elementos fora de ordem, atribui- */
   /* se novamente zero a 'ordenado', trocam-se os       */
   /* elementos de posição e recomeça-se a verificação   */
   /* de ordem do array.                                 */
   /*                                                    */
   /******************************************************/

      /* O laço encerra quando a variável */
      /* 'ordenado' for diferente de 0    */
   while (!ordenado) {
         /* Supõe que o array está ordenado */
      ordenado = 1;

      /*************************************************/
      /*                                               */
      /* Compara cada elemento do array com o elemento */
      /* seguinte. Se for encontrado um elemento menor */
      /* do que seu antecessor, os dois elementos      */
      /* trocam de posição e o array é considerado     */
      /* fora de ordem (i.e., 'ordenado' assume zero). */
      /*                                               */
      /*************************************************/

      for (i = 0; i < nElementos - 1; i++){
            /* Compara cada elemento com */
            /* o elemento seguinte       */
         if (ar[i]->quantidade > ar[i+1]->quantidade){
               /* Pelo menos dois elementos */
               /* estão fora de ordem       */
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
 * main(): Testa a função BubbleSort()
 *
 * Parâmetros: Nenhum
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

      /* Apresenta o array antes da ordenação */
   printf("\n\t>>> Array Original <<<\n\n\t> ");
   for (i=0; i < tamanho; i++) {
      printf("%d   ", array[i]);
   }

      /* Ordena o array */
   BubbleSort(array, tamanho);

      /* Apresenta o array depois da ordenação */
   printf("\n\n\t>>> Array Ordenado <<<\n\n\t> ");
   for (i=0; i < tamanho; i++) {
      printf("%d   ", array[i]);
   }

   return 0;
}

/******************* Exemplo de Execução ******************

        >>> Este programa ordena um array de
        >>> inteiros usando o metodo da bolha.

        >>> Array Original <<<

        > 12   55   21   1   6   8   17   220   5   83

        >>> Array Ordenado <<<

        > 1   5   6   8   12   17   21   55   83   220

**********************************************************/
