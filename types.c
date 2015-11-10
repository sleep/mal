#include "types.h"

#include "linkedlist.h"

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
    free(node->val->str); //we only free strings, since they are presumed to be copied from stack
    break;
  case LIST:
    // a list will have to be manually freed, since it can exist outside of a list node
    /* free(node->val->list); */
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
  case LIST:
    ll_print(node->val->list);
    break;
  default:
    printf("?");
    break;
  }
}
