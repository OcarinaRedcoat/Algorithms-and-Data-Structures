#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  char command;
  init();  // before enter the loop of commands starts the head of the tree at
           // NULL
  while (1) {
    command = getchar();
    if (command == '\n') continue;
    switch (command) {
      case 'a':
        command_a();
        getchar();
        break;
      case 'l':
        command_l();
        getchar();
        break;
      case 'm':
        command_m();
        getchar();
        break;
      case 'r':
        command_r();
        getchar();
        break;
      case 'x':
        command_x();
        return EXIT_SUCCESS;
        break;
      default:
        puts("ERRO: Comando desconhecido.\n");
    }
  }
  return EXIT_FAILURE;
}