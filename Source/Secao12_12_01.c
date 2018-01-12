/****
 *
 * T�tulo: Lendo Linhas (Praticamente) Ilimitadas
 *
 * Autor: Ulysses de Oliveira
 *
 * Data de Cria��o: 11/08/2012
 * �ltima modifica��o: 11/08/2012
 *
 * Descri��o: L� linhas de tamanho arbitr�rio num arquivo de
 *            texto e via teclado, e apresenta-as na tela
 *
 * Entrada: O conte�do do arquivo de texto especificado e um texto
 *          introduzido via teclado
 *
 * Sa�da: v. Exemplo de Execu��o
 *
 ****/

#include <stdio.h>   /* Entrada e sa�da   */
#include <stdlib.h>  /* Aloca��o din�mica */

   /* Nome do arquivo usado nos testes do programa */
#define NOME_ARQ      "AnedotaBulgara.txt"

   /* Tamanho do acr�scimo do bloco usado para conter */
   /* uma linha a cada chamada de realloc()           */
#define TAMANHO_BLOCO 256

/****
 *
 * LeLinhaIlimitada(): L� uma linha de tamanho arbitr�rio num
 *                     stream de texto e armazena os caracteres
 *                     lidos num array alocado dinamicamente
 *
 * Par�metros:
 *      tam (sa�da) - se n�o for NULL, apontar� para uma vari�vel
 *                    que armazenar� o tamanho do string
 *                    constitu�do pelos caracteres da linha
 *      stream (entrada) - stream de texto no qual ser� feita a
 *                         leitura
 *
 * Retorno: Endere�o do array contendo a linha lida. NULL, se
 *          ocorrer erro ou o final do arquivo for atingido
 *          antes da leitura de qualquer caractere
 *
 * Observa��es:
 *       1. O stream deve estar associado a um arquivo de texto
 *          aberto em modo de texto que permita leitura
 *       2. O caractere '\n' n�o � inclu�do no string resultante
 *          da leitura
 *       3. O primeiro par�metro pode ser NULL. Nesse caso, o
 *          tamanho do string n�o ser� armazenado
 *
 ****/
char *LeLinhaIlimitada(int *tam, FILE *stream)
{
   char *ar = NULL,   /* Ponteiro para um array alocado */
                      /* dinamicamente que conter� os   */
                      /* caracteres lidos               */
        *p; /* Usado em chamada de realloc() */
   int   tamanho = 0, /* Tamanho do array alocado */
         c,  /* Armazenar� cada caractere lido */
         i; /* �ndice do pr�ximo caractere */
            /* a ser inserido no array     */

      /* L� caracteres a partir da posi��o corrente do      */
      /* indicador de posi��o do arquivo e armazena-os num  */
      /* array. A leitura encerra quando '\n' � encontrado, */
      /* o final do arquivo � atingido ou ocorre erro.      */
   for (i = 0; ; ++i) {
         /* L� o pr�ximo caractere no arquivo */
      c = fgetc(stream);

         /* Se ocorreu erro de leitura, libera o  */
         /* bloco eventualmente alocado e retorna */
      if (ferror(stream)) {
         free(ar); /* Libera o bloco apontado por 'ar' */
         return NULL; /* Ocorreu erro de leitura */
      }

         /* Verifica se array est� completo. O maior valor que i*/
         /* poderia assumir deveria ser tamanho - 1. Mas, como  */
         /* ao final, o caractere '\0' dever� ser inserido,     */
         /* limita-se o valor de i a tamanho - 2.               */
      if (i > tamanho - 2) { /* Limite atingido */
            /* Tenta redimensionar o array */
         p = realloc(ar, tamanho + TAMANHO_BLOCO);

            /* Se o redimensionamento n�o foi     */
            /* poss�vel, libera o bloco e retorna */
         if (!p) {
            free(ar); /* Libera o bloco apontado por 'ar' */
            return NULL; /* Ocorreu erro de aloca��o */
         }

            /* Redimensionamento foi OK. Ent�o, faz-se */
            /* 'ar' apontar para o novo bloco.         */
         ar = p;

            /* O array aumentou de tamanho */
         tamanho = tamanho + TAMANHO_BLOCO;
      }

         /* Se final do arquivo for atingido ou o caractere */
         /* '\n' for lido,  encerra-se a leitura            */
      if (feof(stream) || c == '\n') {
         break; /* Leitura encerrada */
      }

      ar[i] = c; /* Acrescenta o �ltimo caractere lido ao array */
   }

      /* Se nenhum caractere foi lido, libera */
      /* o espa�o alocado e retorna NULL      */
   if (feof(stream) && !i) {
      free(ar); /* Libera o bloco apontado por 'ar' */
      return NULL; /* Nenhum caractere foi armazenado no array */
   }

      /* Insere o caractere terminal de string. Neste    */
      /* instante, deve haver espa�o para ele porque o   */
      /* array foi sempre redimensionado deixando um     */
      /* espa�o a mais para o onipresente caractere '\0' */
   ar[i] = '\0';

      /* Atualiza o valor apontando pelo par�metro */
      /* 'tam', se ele n�o for NULL                */
   if (tam) {
         /* i � o �ndice do caractere terminal do */
         /* string e corresponde ao seu tamanho   */
      *tam = i;
   }

            /*                                     */
            /* >>> NB: O tamanho do string n�o <<< */
            /* >>>     inclui o caractere '\0' <<< */
            /*                                     */

      /* Tenta ajustar o tamanho do array para n�o */
      /* haver desperd�cio de mem�ria. Como i � o  */
      /* tamanho do string, o tamanho do array que */
      /* o cont�m deve ser i + 1.                  */
   p = realloc(ar, i + 1);

      /*                                                 */
      /* Se a realoca��o foi bem sucedida, retorna-se p. */
      /* Caso contr�rio, 'ar' ainda aponta para um bloco */
      /* v�lido. Talvez, haja desperd�cio de mem�ria,    */
      /* mas, aqui, � melhor retornar 'ar' do que NULL.  */
      /*                                                 */
   return p ? p : ar;
}

/****
 *
 * main(): L� linhas de tamanho arbitr�rio num arquivo de texto e
 *         via teclado, e apresenta-as na tela
 *
 * Par�metros: Nenhum
 *
 * Retorno: 0, se n�o ocorrer nenhum erro; 1, em caso contr�rio.
 *
 ****/
int main(void)
{
   FILE *stream;
   char *linha; /* Apontar� para cada linha lida */
   int   tamanho,  /* Tamanho de cada linha lida */
         nLinhas = 0; /* N�mero de linhas do arquivo */

      /* Tenta abrir para leitura em modo texto o arquivo */
      /* cujo nome � dado pela constante NOME_ARQ         */
   stream = fopen(NOME_ARQ, "r");

      /* Se o arquivo n�o foi aberto, encerra o programa */
   if (!stream) {
      printf("\n\t>>> Arquivo nao pode ser aberto\n");
      return 1; /* Arquivo n�o foi aberto */
   }

            /*                                        */
            /* L� o conte�do do arquivo linha a linha */
            /* informando o tamanho de cada linha     */
            /*                                        */

   printf("\n\t\t*** Conteudo do Arquivo ***\n");

      /* O la�o encerra quando 'linha' assumir  */
      /* NULL, o que acontece quando todo o     */
      /* arquivo for lido ou ocorrer algum erro */
   while ( (linha = LeLinhaIlimitada(&tamanho, stream)) ) {
         /* Escreve o n�mero da linha */
      printf("\n>>> Linha %d: ", nLinhas + 1);
         /* Apresenta a linha seguida por seu tamanho */
      printf("%s (%d caracteres)\n", linha, tamanho);

      free(linha); /* Libera o espa�o ocupado pela linha */

      ++nLinhas; /* Mais uma linha foi lida */
   }

      /* Informa quantas linhas foram lidas no arquivo */
   printf("\n\t>>> O arquivo possui %d linhas\n", nLinhas);

      /* Fecha-se o arquivo, pois ele n�o � mais necess�rio */
   fclose(stream);

         /*                                            */
         /* L� um string de tamanho ilimitado em stdin */
         /*                                            */

   printf("\n\t>>> Digite um texto de qualquer tamanho:\n\t> ");
   linha = LeLinhaIlimitada(&tamanho, stdin);

   printf("\n\t>>> Texto introduzido:\n\"%s\"\n", linha);
   printf( "\n\t>>> Tamanho do texto digitado: %d caracteres\n",
           tamanho );

   free(linha); /* Libera espa�o ocupado pelo string lido */

   return 0;
}

/******************* Exemplo de Execu��o ******************

                *** Conteudo do Arquivo ***

>>> Linha 1: Anedota Bulgara (15 caracteres)

>>> Linha 2: Carlos Drummond de Andrade (26 caracteres)

>>> Linha 3:  (0 caracteres)

>>> Linha 4: Era uma vez um czar naturalista (31 caracteres)

>>> Linha 5: que cacava homens. (18 caracteres)

>>> Linha 6: Quando lhe disseram que tambem se (33 caracteres)

>>> Linha 7: cacam borboletas e andorinhas, (30 caracteres)

>>> Linha 8: ficou muito espantado (21 caracteres)

>>> Linha 9: e achou uma barbaridade (23 caracteres)

        >>> O arquivo possui 9 linhas

        >>> Digite um texto de qualquer tamanho:
        > Pedro de Alcantara Francisco Antonio Joao Carlos
Xavier de Paula Miguel Rafael Joaquim Jose Gonzaga Pascoal
Cipriano Serafim de Braganca e Bourbon

        >>> Texto introduzido:
"Pedro de Alcantara Francisco Antonio Joao Carlos Xavier de
Paula Miguel Rafael Joaquim Jose Gonzaga Pascoal Cipriano
Serafim de Braganca e Bourbon"

        >>> Tamanho do texto digitado: 146 caracteres

**********************************************************/
