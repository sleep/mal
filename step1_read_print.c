#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "reader.h"
#include "linkedlist.h"


// Takes string, returns input ast
LNode* READ(char* input) {
  Reader* r = r_create(input);
  LNode* root = parse(r);
  r_free(r);
  return root;
}

// Takes input ast, returns output ast
LNode* EVAL(LNode* input_ast) {
  LNode* output_ast = input_ast;
  //pass through
  return output_ast;
}

char* PRINT(LNode* ast) {
  char* str;
  ln_asprint(ast, &str);
  return str;
}

void rep(char* input) {
  LNode* in_ast = READ(input);
  if (in_ast != NULL) {

    LNode* out_ast = EVAL(in_ast);
    if (out_ast != NULL) {

      char* str = PRINT(out_ast);
      if (str != NULL) {
        printf("%s", str);

        free(str);

      }else {
        printf("Error printing!\n");
      }

      ln_free_recur(out_ast);

    } else {
      printf("Error evaluation!\n");
    }

    ln_free_recur(in_ast);

  } else {
    printf("Error parsing!\n");
  }
}


int main(int argc, char* argv[]) {
  char* input;

  while (1) {
    input = readline("user> ");

    if (!input) {
      break;
    }
    add_history(input);

    rep(input);

    free(input);
  }
  return 0;
}
