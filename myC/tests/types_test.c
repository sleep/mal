#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../types.h"
#include "../linkedlist.h"

void ln_test_str() {
  printf("\n** Testing LNode of strings\n");
  LNode* head = ln_create_str("Hello");
  ln_check(head);
  ln_print(head);
  printf("\n");

  head->next = ln_create_str("Abcdefghijklmnopqrstuvwxyz");
  ln_check(head);
  ln_check(head->next);
  ln_print(head->next);
  printf("\n");

  ln_free(head->next);
  ln_free(head);
}

void ln_test_list() {
  printf("\n** Testing LNode of lists\n");
  LList* list1 = ll_create();
  LList* list2 = ll_create();

  LNode* head = ln_create_list(list1);
  ln_check(head);
  ln_print(head);
  printf("\n");

  head->next = ln_create_list(list2);
  ln_check(head);
  ln_check(head->next);
  ln_print(head->next);
  printf("\n");

  ll_free(list1);
  ll_free(list2);

  ln_free(head->next);
  ln_free(head);
}


int main(int argc, char* argv[]) {
  printf("\n* Testing LNode\n");
  ln_test_str();
  ln_test_list();
  return 0;
}

//TODO: test other parts of types
