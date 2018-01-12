/****
 *
 * Título: Lendo Linhas (Praticamente) Ilimitadas
 *
 * Autor: Ulysses de Oliveira
 *
 * Data de Criação: 11/08/2012
 * Última modificação: 11/08/2012
 *
 * Descrição: Lê linhas de tamanho arbitrário num arquivo de
 *            texto e via teclado, e apresenta-as na tela
 *
 * Entrada: O conteúdo do arquivo de texto especificado e um texto
 *          introduzido via teclado
 *
 * Saída: v. Exemplo de Execução
 *
 ****/

#include <stdio.h>   /* Entrada e saída   */
#include <stdlib.h>  /* Alocação dinâmica */

   /* Nome do arquivo usado nos testes do programa */
#define NOME_ARQ      "AnedotaBulgara.txt"

   /* Tamanho do acréscimo do bloco usado para conter */
   /* uma linha a cada chamada de realloc()           */
#define TAMANHO_BLOCO 256

/****
 *
 * LeLinhaIlimitada(): Lê uma linha de tamanho arbitrário num
 *                     stream de texto e armazena os caracteres
 *                     lidos num array alocado dinamicamente
 *
 * Parâmetros:
 *      tam (saída) - se não for NULL, apontará para uma variável
 *                    que armazenará o tamanho do string
 *                    constituído pelos caracteres da linha
 *      stream (entrada) - stream de texto no qual será feita a
 *                         leitura
 *
 * Retorno: Endereço do array contendo a linha lida. NULL, se
 *          ocorrer erro ou o final do arquivo for atingido
 *          antes da leitura de qualquer caractere
 *
 * Observações:
 *       1. O stream deve estar associado a um arquivo de texto
 *          aberto em modo de texto que permita leitura
 *       2. O caractere '\n' não é incluído no string resultante
 *          da leitura
 *       3. O primeiro parâmetro pode ser NULL. Nesse caso, o
 *          tamanho do string não será armazenado
 *
 ****/
char *LeLinhaIlimitada(int *tam, FILE *stream)
{
   char *ar = NULL,   /* Ponteiro para um array alocado */
                      /* dinamicamente que conterá os   */
                      /* caracteres lidos               */
        *p; /* Usado em chamada de realloc() */
   int   tamanho = 0, /* Tamanho do array alocado */
         c,  /* Armazenará cada caractere lido */
         i; /* Índice do próximo caractere */
            /* a ser inserido no array     */

      /* Lê caracteres a partir da posição corrente do      */
      /* indicador de posição do arquivo e armazena-os num  */
      /* array. A leitura encerra quando '\n' é encontrado, */
      /* o final do arquivo é atingido ou ocorre erro.      */
   for (i = 0; ; ++i) {
         /* Lê o próximo caractere no arquivo */
      c = fgetc(stream);

         /* Se ocorreu erro de leitura, libera o  */
         /* bloco eventualmente alocado e retorna */
      if (ferror(stream)) {
         free(ar); /* Libera o bloco apontado por 'ar' */
         return NULL; /* Ocorreu erro de leitura */
      }

         /* Verifica se array está completo. O maior valor que i*/
         /* poderia assumir deveria ser tamanho - 1. Mas, como  */
         /* ao final, o caractere '\0' deverá ser inserido,     */
         /* limita-se o valor de i a tamanho - 2.               */
      if (i > tamanho - 2) { /* Limite atingido */
            /* Tenta redimensionar o array */
         p = realloc(ar, tamanho + TAMANHO_BLOCO);

            /* Se o redimensionamento não foi     */
            /* possível, libera o bloco e retorna */
         if (!p) {
            free(ar); /* Libera o bloco apontado por 'ar' */
            return NULL; /* Ocorreu erro de alocação */
         }

            /* Redimensionamento foi OK. Então, faz-se */
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

      ar[i] = c; /* Acrescenta o último caractere lido ao array */
   }

      /* Se nenhum caractere foi lido, libera */
      /* o espaço alocado e retorna NULL      */
   if (feof(stream) && !i) {
      free(ar); /* Libera o bloco apontado por 'ar' */
      return NULL; /* Nenhum caractere foi armazenado no array */
   }

      /* Insere o caractere terminal de string. Neste    */
      /* instante, deve haver espaço para ele porque o   */
      /* array foi sempre redimensionado deixando um     */
      /* espaço a mais para o onipresente caractere '\0' */
   ar[i] = '\0';

      /* Atualiza o valor apontando pelo parâmetro */
      /* 'tam', se ele não for NULL                */
   if (tam) {
         /* i é o índice do caractere terminal do */
         /* string e corresponde ao seu tamanho   */
      *tam = i;
   }

            /*                                     */
            /* >>> NB: O tamanho do string não <<< */
            /* >>>     inclui o caractere '\0' <<< */
            /*                                     */

      /* Tenta ajustar o tamanho do array para não */
      /* haver desperdício de memória. Como i é o  */
      /* tamanho do string, o tamanho do array que */
      /* o contém deve ser i + 1.                  */
   p = realloc(ar, i + 1);

      /*                                                 */
      /* Se a realocação foi bem sucedida, retorna-se p. */
      /* Caso contrário, 'ar' ainda aponta para um bloco */
      /* válido. Talvez, haja desperdício de memória,    */
      /* mas, aqui, é melhor retornar 'ar' do que NULL.  */
      /*                                                 */
   return p ? p : ar;
}

/****
 *
 * main(): Lê linhas de tamanho arbitrário num arquivo de texto e
 *         via teclado, e apresenta-as na tela
 *
 * Parâmetros: Nenhum
 *
 * Retorno: 0, se não ocorrer nenhum erro; 1, em caso contrário.
 *
 ****/
int main(void)
{
   FILE *stream;
   char *linha; /* Apontará para cada linha lida */
   int   tamanho,  /* Tamanho de cada linha lida */
         nLinhas = 0; /* Número de linhas do arquivo */

      /* Tenta abrir para leitura em modo texto o arquivo */
      /* cujo nome é dado pela constante NOME_ARQ         */
   stream = fopen(NOME_ARQ, "r");

      /* Se o arquivo não foi aberto, encerra o programa */
   if (!stream) {
      printf("\n\t>>> Arquivo nao pode ser aberto\n");
      return 1; /* Arquivo não foi aberto */
   }

            /*                                        */
            /* Lê o conteúdo do arquivo linha a linha */
            /* informando o tamanho de cada linha     */
            /*                                        */

   printf("\n\t\t*** Conteudo do Arquivo ***\n");

      /* O laço encerra quando 'linha' assumir  */
      /* NULL, o que acontece quando todo o     */
      /* arquivo for lido ou ocorrer algum erro */
   while ( (linha = LeLinhaIlimitada(&tamanho, stream)) ) {
         /* Escreve o número da linha */
      printf("\n>>> Linha %d: ", nLinhas + 1);
         /* Apresenta a linha seguida por seu tamanho */
      printf("%s (%d caracteres)\n", linha, tamanho);

      free(linha); /* Libera o espaço ocupado pela linha */

      ++nLinhas; /* Mais uma linha foi lida */
   }

      /* Informa quantas linhas foram lidas no arquivo */
   printf("\n\t>>> O arquivo possui %d linhas\n", nLinhas);

      /* Fecha-se o arquivo, pois ele não é mais necessário */
   fclose(stream);

         /*                                            */
         /* Lê um string de tamanho ilimitado em stdin */
         /*                                            */

   printf("\n\t>>> Digite um texto de qualquer tamanho:\n\t> ");
   linha = LeLinhaIlimitada(&tamanho, stdin);

   printf("\n\t>>> Texto introduzido:\n\"%s\"\n", linha);
   printf( "\n\t>>> Tamanho do texto digitado: %d caracteres\n",
           tamanho );

   free(linha); /* Libera espaço ocupado pelo string lido */

   return 0;
}

/******************* Exemplo de Execução ******************

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
