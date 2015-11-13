#include "../tokens.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>




typedef struct TestCase TestCase;
struct TestCase {
  char** input;
  int ilength;

  Token** tokens;
  int olength;
};

static TestCase case0 = (TestCase){
  .input = (char*[]){"(", ")", ";blah blah blah"},
  .ilength = 3,

  .tokens = (Token*[]) {
    &(Token){.tt = TLP},
    &(Token){.tt = TRP}
  },
  .olength = 2
};

static TestCase case1 = (TestCase){
  .input = (char*[]){"(", "+", "[", "1", "]", "{", "123", "\"Hello!\"", "}", ")"},
  .ilength = 10,

  .tokens = (Token*[]) {
    &(Token){.tt = TLP},
    &(Token){.tt = TSYM, .val=&(TokVal){.str="+"}},
    &(Token){.tt = TLSQR},
    &(Token){.tt = TINT, .val=&(TokVal){.i=1}},
    &(Token){.tt = TRSQR},
    &(Token){.tt = TLCUR},
    &(Token){.tt = TINT, .val=&(TokVal){.i=123}},
    &(Token){.tt = TSTR, .val=&(TokVal){.str="Hello!"}},
    &(Token){.tt = TRCUR},
    &(Token){.tt = TRP}
  },
  .olength = 10
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
  for (i = 0; i < tc->ilength-1; i++) {
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
  Token** tokens = malloc(sizeof(Token) * tc->olength);
  int i;
  for (i = 0; i < tc->olength; i++) {
    printf("\"");
    if (tc->tokens[i]->val != NULL) {
      switch(tc->tokens[i]->tt) {
      case TINT:
        tokens[i] = tok_create(tc->tokens[i]->tt, tc->tokens[i]->val->i, NULL);
        break;
      case TSTR:
        //TODO: add quotes here to end and begninning
        tokens[i] = tok_create(tc->tokens[i]->tt, 0, tc->tokens[i]->val->str);
        break;
      default:
        tokens[i] = tok_create(tc->tokens[i]->tt, 0, tc->tokens[i]->val->str);
        break;
      }
    }else {
      tokens[i] = tok_create(tc->tokens[i]->tt, 0, NULL);
    }
    tok_print(tokens[i]);
    printf("\", ");
  }
  printf("\n\n");


  for (int i = 0; i < tc->olength; i++) {
    tok_free(tokens[i]);
  }

  free(tokens);
}

void test_parse(TestCase* tc) {
  printf("** INPUT: ");
  tc_print(tc);
  printf("\n");

  printf("** GOT:   ");

  Token** tokens = malloc(sizeof(Token) * tc->olength);
  int i;
  for (i = 0; i < tc->olength; i++) {
    printf("\"");
    tokens[i] = tok_parse(tc->input[i]);

    tok_assert_equals(tokens[i], tc->tokens[i]);
    /* assert(tok_equals(tokens[i], tc->tokens[i])); */


    tok_print(tokens[i]);
    printf("\", ");
  }
  printf("\n\n");


  for (int i = 0; i < tc->olength; i++) {
    tok_free(tokens[i]);
  }

  free(tokens);
}


int main (int argc, char* argv[]) {
  printf("* TESTING TOKEN CREATION\n");
  test(test_creation);
  printf("* TESTING TOKEN PARSING\n");
  test(test_parse);
  printf("* SUCCESS!\n");
  return 0;
}
