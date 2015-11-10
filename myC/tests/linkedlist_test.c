#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../linkedlist.h"
#include "../types.h"



void ll_test_pushpop() {
  LNode* hello = ln_create_str("Hello");
  LNode* space = ln_create_str(" ");
  LNode* abc = ln_create_str("Abcdefghijklmnopqrstuvwxyz");

  LList* list = ll_create();
  ll_check(list);
  ll_push(list, hello);
  ll_check(list);

  assert(strcmp(ll_get(list, 0)->val->str, "Hello") == 0);

  ll_push(list, space);
  ll_check(list);
  assert(strcmp(ll_get(list, 0)->val->str, "Hello") == 0);
  assert(strcmp(ll_get(list, 1)->val->str, " ") == 0);

  ll_push(list, abc);
  ll_check(list);
  ll_print(list);
  printf("\n");

  assert(strcmp(ll_get(list, 0)->val->str, "Hello") == 0);
  assert(strcmp(ll_get(list, 1)->val->str, " ") == 0);
  assert(strcmp(ll_get(list, 2)->val->str, "Abcdefghijklmnopqrstuvwxyz") == 0);

  // pop
  LNode* expect_abc= ll_pop(list);
  ll_check(list);
  printf("Popped \"%s\" off linked list\n", expect_abc->val->str);
  ll_print(list);
  printf("\n");
  printf("Length of list: %d\n", list->length);
  ln_free(expect_abc);

  LNode* expect_space = ll_pop(list);
  ll_check(list);
  printf("Popped \"%s\" off linked list\n", expect_space->val->str);
  ll_print(list);
  printf("\n");

  printf("Length of list: %d\n", list->length);
  ln_free(expect_space);

  LNode* expect_hello = ll_pop(list);
  ll_check(list);
  printf("Popped \"%s\" off linked list\n", expect_hello->val->str);
  ll_print(list);
  printf("\n");

  printf("Length of list: %d\n", list->length);
  ln_free(expect_hello);


  ll_free(list);
}

void ll_test_shiftunshift() {
  LNode* hello = ln_create_str("Hello");
  LNode* space = ln_create_str(" ");
  LNode* abc = ln_create_str("Abcdefghijklmnopqrstuvwxyz");

  LList* list = ll_create();
  ll_check(list);
  ll_unshift(list, abc);
  ll_check(list);

  assert(strcmp(ll_get(list, 0)->val->str, "Abcdefghijklmnopqrstuvwxyz") == 0);

  ll_unshift(list, space);
  ll_check(list);
  assert(strcmp(ll_get(list, 0)->val->str, " ") == 0);
  assert(strcmp(ll_get(list, 1)->val->str, "Abcdefghijklmnopqrstuvwxyz") == 0);

  ll_unshift(list, hello);
  ll_check(list);
  ll_print(list);
  printf("\n");

  assert(strcmp(ll_get(list, 0)->val->str, "Hello") == 0);
  assert(strcmp(ll_get(list, 1)->val->str, " ") == 0);
  assert(strcmp(ll_get(list, 2)->val->str, "Abcdefghijklmnopqrstuvwxyz") == 0);

  // pop
  LNode* expect_hello = ll_shift(list);
  ll_check(list);
  printf("Shifted \"%s\" off linked list\n", expect_hello->val->str);
  ll_print(list);
  printf("\n");
  printf("Length of list: %d\n", list->length);
  ln_free(expect_hello);

  LNode* expect_space = ll_shift(list);
  ll_check(list);
  printf("Shifted \"%s\" off linked list\n", expect_space->val->str);
  ll_print(list);
  printf("\n");
  printf("Length of list: %d\n", list->length);
  ln_free(expect_space);

  LNode* expect_abc = ll_shift(list);
  ll_check(list);
  printf("Shifted \"%s\" off linked list\n", expect_abc->val->str);
  ll_print(list);
  printf("\n");
  printf("Length of list: %d\n", list->length);
  ln_free(expect_abc);



  ll_free(list);
}



int main(int argc, char* argv[]) {

  printf("\n* Testing ll_create\n");
  // createLList
  LList* list = ll_create();
  ll_check(list);
  ll_free(list);

  printf("\n* Testing ll_push, ll_pop\n");
  ll_test_pushpop();

  printf("\n* Testing ll_unshift, ll_shift\n");
  ll_test_shiftunshift();

  return 0;
}
