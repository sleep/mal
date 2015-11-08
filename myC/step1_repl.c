#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/* #include "reader.c" */
#include "linkedlist.c"

// Takes string, returns input ast
char* READ(char* input) {
  /* char** tokens = tokenizer(input); */
  return input;
}

// Takes input ast, returns output ast (bc homoiconic)
char* EVAL(char* input_ast) {
  char* output_ast = input_ast;
  return output_ast;
}
char* PRINT(char* ast) {
  char* output = ast;
  return output;
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
