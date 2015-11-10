#include "linkedlist.h"

#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


LNode* ln_create_str(char const * val) {
  LNode* n = malloc(sizeof(LNode));
  assert(n != NULL);

  n->type = STRING;
  n->val = malloc(sizeof(Val));
  n->val->str = strdup(val);
  n->next = NULL;
  return n;
}

LNode* ln_create_list(LList* val) {
  LNode* n = malloc(sizeof(LNode));
  assert(n != NULL);

  n->type = LIST;
  n->val = malloc(sizeof(Val));
  n->val->list = val;
  n->next = NULL;
  return n;
}


void ln_check(LNode* node) {
  assert(node != NULL);
  /* assert(node->type != NULL); //assume initialized */
  assert(node->val != NULL);

  switch(node->type) {
  case STRING:
    //check is string?
    assert(node->val->str != NULL);
    break;
  case LIST:
    // check if valid list?
    assert(node->val->list != NULL);
    break;
  default:
    break;
  }
}

void ln_free(LNode* node) {
  switch(node->type) {
  case STRING:
    free(node->val->str);
    break;
  case LIST:
    free(node->val->list);
    break;
  default:
    break;
  }
  free(node->val);
  free(node);
}


void ln_print(LNode* node) {
  switch(node->type) {
  case STRING:
    printf("\"%s\"", node->val->str);
    break;
  default:
    printf("?");
    break;
  }
}






LList* ll_create(){
  LList* list = malloc(sizeof(LList));
  assert(list != NULL);
  list->head = NULL;
  list->length = 0;
  return list;
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
    printf("()");
    return;
  }
  LNode* curr = list->head;
  printf("(");
  for (int i = 0; i < list->length -1; i++) {
    ln_print(curr);
    curr = curr->next;
    printf(" ");
  }
  ln_print(curr);
  printf(")");
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

// private
void ll_push(LList* list, LNode* node) {
  assert(node->next == NULL); //assert node is atomic

  if (list->length == 0) {
    list->head = node;
    list->length = 1;
  }else {
    LNode* tail = ll_get(list, list->length - 1);

    tail->next = node;
    list->length += 1;
  }
}


// remove from end, returning pointer to element
LNode* ll_pop(LList* list) {
  assert(list->length > 0);

  if (list->length == 1) {
    LNode* output = list->head;
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

void ll_unshift(LList* list, LNode* node) {
  assert(node->next == NULL); //assert node has no connections
  if (list->length == 0) {
    list->head = node;
    list->length = 1;
  }else {
    LNode* newhead = node;
    newhead->next = list->head;

    list->head = newhead;
    list->length += 1;
  }
}
