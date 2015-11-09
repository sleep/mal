#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "types.h"


LNode* ln_create(const char* val) {
  LNode* n = malloc(sizeof(LNode));
  assert(n != NULL);

  n->val = strdup(val);
  n->next = NULL;

  return n;
}

void ln_free(LNode* node) {
  assert(node->val != NULL);
  free(node->val);
  free(node);
}

void ln_set(LNode* node, const char* val) {
  free(node->val);
  node->val = strdup(val);
}

void ln_print(LNode* head) {
  assert(head != NULL);
  printf("%s\n", head->val);
}










LList* ll_create(){
  LList* list = malloc(sizeof(LList));
  assert(list != NULL);
  list->head = NULL;
  list->length = 0;
  return list;
}

void ll_free(LList* list) {
  //assert existence
  assert(list != NULL);

  // Free elements

  // use for loop?
  if (list->length > 0) {

    //INVARIANT: curr is non-NULL
    LNode* curr = list->head;
    LNode* child = curr->next;

    while (child != NULL) {
      ln_free(curr);
      curr = child;
      child = curr->next;
    }

    // INVARIANT: child == NULL
    ln_free(curr);
  }

  //Free list
  free(list);
}

void ll_print(LList* list) {
  if (list->length == 0) {
    printf("[]\n");
    return;
  }
  LNode* curr = list->head;
  printf("[");
  for (int i = 0; i < list->length -1; i++) {
    printf("\"%s\", ", curr->val);
    curr = curr->next;
  }
  printf("\"%s\"]\n", curr->val);
}


void ll_check(LList* list) {
  // check existence
  assert(list != NULL);

  //check length is positive
  assert(list->length >= 0);

  // Check length is correct:
  if (list->length > 0) {
    //Check conditions for non-zero length:
    // aka, check if length-1th child is a leaf
    assert(list->head != NULL);

    LNode* curr = list->head;

    for (int i = 1; i< list->length; i++) {
      curr = curr->next;
    }
    assert(curr->next == NULL);
  } else {
    // check conditions for zero-length:
    // aka check if head is equal to nulist pointer
    assert(list->head == NULL);
  }
}


LNode* ll_get(LList* list, int index) {
  assert(index >= 0 && index < list->length);

  LNode* curr = list->head;
  for (int i = 0; i < index; i++) {
    curr = curr->next;
  }
  return curr;
}

// MUTATORS
// add to end
void ll_push(LList* list, const char* elem) {

  if (list->length == 0) {
    list->head = ln_create(elem);
    list->length = 1;
  }else {
    LNode* tail = ll_get(list, list->length - 1);

    tail->next = ln_create(elem);
    list->length += 1;
  }
}


// remove from end, returning pointer to element
LNode* ll_pop(LList* list) {
  assert(list->length > 0);


  if (list->length == 1) {
    LNode* output =  list->head;
    list->head = NULL;
    list->length = 0;
    return output;
  }


  //INVARIANT: list->length >= 2

  LNode* parent = ll_get(list, list->length - 2);
  LNode* output = parent->next;

  parent->next = NULL;
  list->length -= 1;

  return output;
}

LNode* ll_shift(LList* list) {
  assert(list->length > 0);

  if (list->length == 1) {
    LNode* output = list->head;
    list->head = NULL;
    list->length = 0;
    return output;
  }

  //INVARIANT: list->length >= 2
  LNode* output = list->head;
  list->head = output->next;
  list->length -= 1;
  return output;
}

void ll_unshift(LList* list, const char* elem) {
  if (list->length == 0) {
    list->head = ln_create(elem);
    list->length = 1;
  }else {
    LNode* newhead = ln_create(elem);
    newhead->next = list->head;

    list->head = newhead;
    list->length += 1;
  }
}
