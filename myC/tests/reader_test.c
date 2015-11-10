#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../reader.h"


typedef struct TestCase TestCase;
struct TestCase {
  char* input;
  char** expectedToks;
  int expectedNumToks;
};

static TestCase case0 = {"", NULL, 0};

static char* case1_expectedToks[] = {"(", "+", "(", "1", ")", "(", "123", ")", ")"};
static TestCase case1 = {"(+ (1) (123))", case1_expectedToks, 9};


static TestCase* cases[] = {&case0, &case1};


typedef void (*TestFunc) (TestCase*);

void test(TestFunc test_func) {
  for (int i = 0; i < sizeof(cases)/sizeof(TestCase*); i++) {
    test_func(cases[i]);
  }
}



// Tokenizer

void tc_printExpected(TestCase* tc) {
  if (tc->expectedNumToks == 0) {
    printf("()");
    return;
  }

  int i;
  printf("(");
  for(i = 0; i < tc->expectedNumToks -1; i++) {
    printf("\"%s\" ", tc->expectedToks[i]);
  }
  printf("\"%s\")", tc->expectedToks[i]);
}

void test_tokenizer(TestCase* tc) {
  printf("** Input: %s\n", tc->input);
  printf("** Expecting: ");
  tc_printExpected(tc);
  printf("\n");

  LList* tokens = tokenizer(tc->input);
  assert(tokens->length == tc->expectedNumToks);
  printf("** Got:       ");
  ll_print(tokens);


  LNode* curr = tokens->head;
  for (int i = 0; i < tc->expectedNumToks; i++, curr=curr->next) {
    assert(strcmp(curr->val->str, tc->expectedToks[i]) == 0);
  }
  assert(curr == NULL);

  ll_free_recur(tokens);

  printf("\n");
}



// Reader

void test_reader(TestCase* tc) {
  printf("** Input: %s\n", tc->input);
  Reader* r = r_create(tc->input);
  LNode* n;

  printf("** Expecting: ");
  tc_printExpected(tc);
  printf("\n");

  if (tc->expectedNumToks == 0) {

  }
  printf("** Got:       (");

  int count = 0;

  while (r_check(r), n = r_next(r), n !=NULL) {
    r_check(r);

    printf("\"%s\" ", n->val->str);
    assert(strcmp(n->val->str, tc->expectedToks[count]) == 0);

    count += 1;
    r_check(r);
  }
  if (count > 0) {
    printf("\b\b");
  }
  printf(")\n");
  assert(count == tc->expectedNumToks);

  r_free(r);
  printf("\n");
}


// Main

int main(int argc, char* argv[]) {
  printf("\n* Testing tokenizer:\n");
  test(test_tokenizer);

  printf("\n* Testing reader:\n");
  test(test_reader);

  printf("\n* Success!\n");
  return 0;
}
