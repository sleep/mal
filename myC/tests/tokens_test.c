#include "../tokens.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>




typedef struct TestCase TestCase;
struct TestCase {
  char** input;
  Token** tokens;
  int length;
};

static TestCase case0 = (TestCase){
  .input = (char*[]){"(", ")"},
  .tokens = (Token*[]) {
    &(Token){.tt = TLP},
    &(Token){.tt = TRP}
  },
  .length = 2
};

static TestCase case1 = (TestCase){
  .input = (char*[]){"(", "+", "(", "1", ")", "(", "123", "\"Hello!\"", ")", ")"},
  .tokens = (Token*[]) {
    &(Token){.tt = TLP},
    &(Token){.tt = TSYM, .val=&(TokVal){.str="+"}},
    &(Token){.tt = TLP},
    &(Token){.tt = TNUM, .val=&(TokVal){.i=1}},
    &(Token){.tt = TRP},
    &(Token){.tt = TLP},
    &(Token){.tt = TNUM, .val=&(TokVal){.i=123}},
    &(Token){.tt = TSTR, .val=&(TokVal){.str="Hello!"}},
    &(Token){.tt = TRP},
    &(Token){.tt = TRP}
  },
  .length = 10
};



static TestCase* cases[] = {&case0, &case1};

typedef void (*TestFunc) (TestCase*);

void test(TestFunc test_func) {
  for (int i = 0; i < sizeof(cases)/sizeof(TestCase*); i++) {
    test_func(cases[i]);
  }
}

void tc_print(TestCase* tc) {
  int i;
  for (i = 0; i < tc->length-1; i++) {
    printf("\"%s\", ", tc->input[i]);
  }
  printf("\"%s\"", tc->input[i]);
}

void test_creation(TestCase* tc) {
  printf("** INPUT: ");
  tc_print(tc);
  printf("\n");

  printf("** GOT:   ");
  // create and print
  Token** tokens = malloc(sizeof(Token) * tc->length);
  int i;
  for (i = 0; i < tc->length; i++) {
    printf("\"");
    if (tc->tokens[i]->val != NULL) {
      if (tc->tokens[i]->tt == TNUM){

        tokens[i] = tok_create(tc->tokens[i]->tt, tc->tokens[i]->val->i, NULL);
      }else {
        tokens[i] = tok_create(tc->tokens[i]->tt, 0, tc->tokens[i]->val->str);
      }
    }else {
      tokens[i] = tok_create(tc->tokens[i]->tt, 0, NULL);
    }
    tok_print(tokens[i]);
    printf("\", ");
  }
  printf("\n\n");


  for (int i = 0; i < tc->length; i++) {
    tok_free(tokens[i]);
  }

  free(tokens);
}

void test_parse(TestCase* tc) {
  printf("** INPUT: ");
  tc_print(tc);
  printf("\n");

  printf("** GOT:   ");

  Token** tokens = malloc(sizeof(Token) * tc->length);
  int i;
  for (i = 0; i < tc->length; i++) {
    printf("\"");
    tokens[i] = tok_parse(tc->input[i]);
    //TODO: make tests for proper token copying, each way (type, val)
    tok_print(tokens[i]);
    printf("\", ");
  }
  printf("\n\n");


  for (int i = 0; i < tc->length; i++) {
    tok_free(tokens[i]);
  }

  free(tokens);
}


//TODO: test token equals


int main (int argc, char* argv[]) {
  printf("* TESTING TOKEN CREATION\n");
  test(test_creation);
  printf("* TESTING TOKEN PARSING\n");
  test(test_parse);
  printf("* SUCCESS!\n");
  return 0;
}
