#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "reader.c"
/* #include "linkedlist.c" */

LList * strings;

// Takes string, returns input ast
char* READ(char* input) {
  LList* tokens = tokenizer(input);
  ll_print(tokens);
  ll_free(tokens);

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
  strings = ll_create();

  while (1) {
    input = readline("user> ");

    if (!input) {
      break;
    }
    add_history(input);

    READ(input);

    free(input);
  }
  return 0;
}
