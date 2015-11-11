#include "types.h"

#include "tokens.h"
#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>



LNode* ln_create_str(char* val) {
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

LNode* ln_create_tok(Token* val) {
  LNode* n = malloc(sizeof(LNode));
  assert(n != NULL);

  n->type = TOKEN;
  n->val = malloc(sizeof(Val));
  n->val->tok = val;
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
  case TOKEN:
    // check if valid list?
    assert(node->val->tok != NULL);
    break;
  default:
    break;
  }
}

void ln_free_recur(LNode* node) {
  if (node->type == LIST) {
    ll_free_recur(node->val->list);
  }
  if (node->type == TOKEN) {
    tok_free(node->val->tok);
  }
  ln_free(node);
}

void ln_free(LNode* node) {
  assert(node != NULL);
  if (node->type == STRING) {
    free(node->val->str);
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
  case TOKEN:
    tok_print(node->val->tok);
    break;
  default:
    printf("?");
    break;
  }
}
