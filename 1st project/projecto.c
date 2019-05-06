/* Projeto 1 IAED
        Francisco Lopes 88078
        Ricardo Caetano 87699 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constantes
#define INITIAL_ACTIVITY 0
#define DIM_MSG 140
#define MAX_MSG 10000
#define DIM_USER 3
#define MAX_USER 1000

// estrutura
typedef struct {
  int size;
  int user;
  char msg[DIM_MSG + 1];
} Message;

// variaveis globais
Message message[MAX_MSG];
int activity[MAX_USER];
int counter = 0;
int sortList[MAX_MSG];

// prototipos
int forum();
void execute_A();
void execute_L();
void execute_U();
void execute_O();
void execute_T();
void execute_S();
void execute_C();
void execute_X();
void message_all();
int user_activity(int);
int message_size(char s[]);
void message_user(int, int);
int less(int v, int a);

int main() {
  // inicializar lista sort
  int i;
  for (i = 0; i < MAX_MSG; i++) {
    sortList[i] = i;
  }
  return forum();
}

int forum() {
  // funcao que recebe os comandos e executa cada comando chamando a funcao
  int i;
  char command;
  for (i = 0; i < MAX_USER; i++) {
    activity[i] = INITIAL_ACTIVITY;
  }
  while (1) {
    command = getchar();
    switch (command) {
      case 'A':       //##########################
        execute_A();  //#####################
        break;        //###################################################
      case 'L':       //#####################
        execute_L();  //##########################
        getchar();
        break;
      case 'U':
        execute_U();
        getchar();
        break;
      case 'O':
        execute_O();
        getchar();
        break;
      case 'T':
        execute_T();
        getchar();
        break;
      case 'S':
        execute_S();
        getchar();
        break;
      case 'C':
        execute_C();
        getchar();
        break;
      case 'X':
        execute_X();
        return EXIT_SUCCESS;
      default:
        printf("ERRO: Comando desconhecido.\n");
    }
  }
  return EXIT_FAILURE;
}

void execute_A() {
  // funcao que adiciona uma mensagem, guarda a actividade de um utilizador, o
  // tamanho da mensagem, e conta o numero de mensgens totais
  scanf("%d", &message[counter].user);
  getchar();
  message_all();
  message[counter].size = message_size(message[counter].msg);
  activity[message[counter].user]++;
  counter++;
}

void execute_L() {
  // lista todas as mensagens
  int counter_aux;
  printf("*TOTAL MESSAGES:%d\n", counter);
  for (counter_aux = 0; counter_aux < counter; counter_aux++)
    printf("%d:%s\n", message[counter_aux].user, message[counter_aux].msg);
}

void execute_U() {
  // lista todas as mensagens introduzidas por um dado utilizador
  int selected_user, counter_user_messages, counter_aux, index,
      i = 0, user_text[MAX_MSG];
  scanf("%d", &selected_user);
  // guarda o index das mensagens de um utilizador do vector global que contem
  // todas as mensagens num vector
  for (counter_aux = 0; counter_aux < counter; counter_aux++) {
    if (selected_user == message[counter_aux].user) {
      user_text[i] = counter_aux;
      i++;
    }
  }
  counter_user_messages = user_activity(selected_user);
  printf("*MESSAGES FROM USER:%d\n", selected_user);
  // no vetor user_text que contem os index das mensagens de un dado utilizdor
  // da print de todas elas
  for (i = 0; i < counter_user_messages; i++) {
    index = user_text[i];
    printf("%s\n", message[index].msg);
  }
}

void execute_O() {
  // lista as mensagens mais longas
  int i, size_max = 0;
  // guarda em size max o numero de caracteres da maior mensagem
  for (i = 0; i < counter; i++) {
    if (size_max < message[i].size) size_max = message[i].size;
  }
  // da print das mensagens que tem esse numero de caracteres
  for (i = 0; i < counter; i++) {
    if (size_max == message[i].size)
      printf("*LONGEST SENTENCE:%d:%s\n", message[i].user, message[i].msg);
  }
}

void execute_T() {
  // escreve o utilizador mais activo na escrita de mensagens
  int i, max_activity = 0, j = 0, user_index[MAX_USER];
  for (i = 0; i < MAX_USER; i++) {
    if (activity[i] > max_activity) max_activity = activity[i];
  }
  for (i = 0; i < MAX_USER; i++) {
    if (activity[i] == max_activity) {
      user_index[j] = i;
      j++;
    }
  }
  for (i = 0; i < j; i++) {
    printf("*MOST ACTIVE USER:%d:%d\n", user_index[i], max_activity);
  }
}

void execute_S() {
  // ordena as mensagens por ordem alfabetica, utilizando o insertion sort, no
  // entanto nao se ordena a estrutura mensagem, mas sim os indices das mensagens
  // num array (sortList) ordenando-os dependendo do valor obtido na funcao less
  int i, j;
  for (i = 1; i < counter; i++) {
    int v = sortList[i];
    j = i - 1;

    while (j >= 0 && less(v, sortList[j])) {
      sortList[j + 1] = sortList[j];
      j--;
    }
    sortList[j + 1] = v;
  }
  printf("*SORTED MESSAGES:%d\n", counter);
  // imprime as mensagens percorrendo a sortList, onde as mensagens ja estao
  // ordenadas
  for (i = 0; i < counter; i++)
    printf("%i:%s\n", message[sortList[i]].user, message[sortList[i]].msg);
}

void execute_C() {
  // Escreve o número de ocorrências de uma palavra.
  // Usa a strtok de modo a conseguir comparar a palavra selecionada com todas
  // as palavras de todas as strings
  char words[DIM_MSG + 1], testWord[DIM_MSG + 1], *word;
  int i, counter_aux = 0;
  scanf("%s", words);
  for (i = 0; i < counter; i++) {
    strcpy(testWord, message[i].msg);
    word = strtok(testWord, " .,;\t\n\0");
    while (word != NULL) {
      if (strcmp(word, words) == 0) counter_aux++;
      word = strtok(NULL, " .,;\t\n\0");
    }
  }
  printf("*WORD %s:%d\n", words, counter_aux);
}

void execute_X() { printf("%d\n", counter); }

int user_activity(int sel_user) {
  // funcao auxiliar que determina a actividade de um dado utilizador
  int counter_aux, sel_user_msg = 0;
  for (counter_aux = 0; counter_aux < counter; counter_aux++) {
    if (sel_user == message[counter_aux].user) sel_user_msg++;
  }
  return sel_user_msg;
}

void message_all() {
  // funcao que devolve todos os caracteres de uma mensagem
  int c, i;
  char s[DIM_MSG + 1];
  c = getchar();
  for (i = 0; i < DIM_MSG + 1 && c != '\n'; i++) {
    s[i] = c;
    c = getchar();
  }
  s[i] = '\0';
  for (i = 0; s[i] != '\0'; i++) {
    message[counter].msg[i] = s[i];
  }
  message[counter].msg[i++] = '\0';
}

int message_size(char s[]) {
  // funcao que devolve o numero de caracteres de uma mensagems
  int c = 0, i;
  for (i = 0; s[i] != '\0'; i++) c++;
  return c;
}

int less(int v, int a) {
  // funcao que compara as mensagens alfabeticamente
  // retorna 1 se for para trocar as mensagens, 0 se nao for
  if (strcmp(message[v].msg, message[a].msg) < 0) return 1;
  if (strcmp(message[v].msg, message[a].msg) > 0) return 0;
  // se as mensagens forem iguais, ficam ordenadas pelo user
  if (strcmp(message[v].msg, message[a].msg) == 0) {
    if (message[v].user < message[a].user)
      return 1;
    else
      return 0;
  }
  return 0;
}