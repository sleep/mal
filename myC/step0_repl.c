#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char* READ(char* input) {
  return input;
}
char* EVAL(char* input) {
  return input;
}
char* PRINT(char* input) {
  return input;
}

char* rep(char* input) {
  return PRINT(EVAL(READ(input)));
}


int main(int argc, char* argv[]) {
  char* input;

  while (1) {
    input = readline("user> ");
    if (!input) {
      break;
    }
    add_history(input);

    printf("%s\n", input);

    free(input);
  }
  return 0;

  //TODO: move to gnu readline
}
