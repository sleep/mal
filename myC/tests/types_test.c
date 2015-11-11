#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../types.h"
#include "../linkedlist.h"

void ln_test_int() {
  printf("\n** Testing LNode of ints\n");
  LNode* head = ln_create_int(347);
  ln_check(head);
  ln_print(head);
  printf("\n");

  head->next = ln_create_int(262);
  ln_check(head);
  ln_check(head->next);
  ln_print(head->next);
  printf("\n");

  ln_free(head->next);
  ln_free(head);
}


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
  ln_print(head);
  ln_print(head->next);
  printf("\n");



  ll_free(list1);
  ll_free(list2);

  ln_free(head->next);
  ln_free(head);
}

void ln_test_nested_lists() {
  printf("\n** Testing Nested Lists\n");

  LList* root_c = ll_create();
  LNode* root = ln_create_list(root_c);

  LList* father_c= ll_create();
  LNode* father = ln_create_list(father_c);

  LNode* hello = ln_create_str("hello");

  ll_push(root_c, hello);
  ll_push(root_c, father);

  LNode* one = ln_create_str("1");
  LNode* two = ln_create_str("2");
  LNode* three = ln_create_str("3");
  ll_push(root_c, one);
  ll_push(root_c, two);
  ll_push(root_c, three);

  ln_print(root);
  printf("\n");

  printf("*** Freeing recursively\n");
  ln_free_recur(root);
}

void ln_test_mnum() {
  printf("\n** Testing LNode of mal number\n");
  LNode* head = ln_create_mnum(347);
  ln_check(head);
  ln_print(head);
  printf("\n");

  head->next = ln_create_mnum(262);
  ln_check(head);
  ln_check(head->next);
  ln_print(head->next);
  printf("\n");

  ln_free(head->next);
  ln_free(head);
}
void ln_test_mstr() {
  printf("\n** Testing LNode of mal strings\n");
  LNode* head = ln_create_mstr("Hello");
  ln_check(head);
  ln_print(head);
  printf("\n");

  head->next = ln_create_mstr("Abcdefghijklmnopqrstuvwxyz");
  ln_check(head);
  ln_check(head->next);
  ln_print(head->next);
  printf("\n");

  ln_free(head->next);
  ln_free(head);
}

void ln_test_msym() {
  printf("\n** Testing LNode of mal symbols\n");
  LNode* head = ln_create_msym("Hello");
  ln_check(head);
  ln_print(head);
  printf("\n");

  head->next = ln_create_msym("Abcdefghijklmnopqrstuvwxyz");
  ln_check(head);
  ln_check(head->next);
  ln_print(head->next);
  printf("\n");

  ln_free(head->next);
  ln_free(head);
}


void ln_test_mlist() {
  printf("\n** Testing Mal Lists\n");

  LList* root_c = ll_create();
  LNode* root = ln_create_mlist(root_c);

  LList* father_c= ll_create();
  LNode* father = ln_create_mlist(father_c);

  LNode* hello = ln_create_mstr("hello");

  ll_push(root_c, hello);
  ll_push(root_c, father);

  LNode* one = ln_create_mstr("1");
  LNode* two = ln_create_mstr("2");
  LNode* three = ln_create_mstr("3");
  ll_push(root_c, one);
  ll_push(root_c, two);
  ll_push(root_c, three);

  ln_print(root);
  printf("\n");

  printf("*** Freeing recursively\n");
  ln_free_recur(root);
}


int main(int argc, char* argv[]) {
  printf("\n* Testing LNode\n");
  ln_test_int();
  ln_test_str();
  ln_test_list();
  ln_test_nested_lists();

  ln_test_mnum();
  ln_test_mstr();
  ln_test_msym();
  ln_test_mlist();

  return 0;
}

//TODO: Test mal types...
