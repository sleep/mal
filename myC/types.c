#include "types.h"

#include "tokens.h"
#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


//returns partially valid LNode...
LNode* ln_create(Type T) {
  LNode* n = malloc(sizeof(LNode));
  assert(n != NULL);
  n->type = T;
  n->val = malloc(sizeof(Val));
  n->next = NULL;
  return n;
}


// normal types

LNode* ln_create_int(int val) {
  LNode* n = ln_create(INT);
  n->val->i = val;
  return n;
}

LNode* ln_create_str(char* val) {
  LNode* n = ln_create(STRING);
  n->val->str = strdup(val);
  return n;
}

LNode* ln_create_list(LList* val) {
  LNode* n = ln_create(LIST);
  n->val->list = val;
  return n;
}
LNode* ln_create_tok(Token* val) {
  LNode* n = ln_create(TOKEN);
  n->val->tok= val;
  return n;
}


// mal types

LNode* ln_create_mnum(int val) {
  LNode* n = ln_create(MNUM);
  n->val->i = val;
  return n;
}

LNode* ln_create_mstr(char* val) {
  LNode* n = ln_create(MSTR);
  n->val->str = strdup(val); // do we want to dup?
  return n;
}

LNode* ln_create_msym(char* val) {
  LNode* n = ln_create(MSYM);
  n->val->str = strdup(val); //do we want to dup?
  return n;
}


LNode* ln_create_mlist(LList* val) {
  LNode* n = ln_create(MLIST);
  n->val->list = val;
  return n;
}



void ln_check(LNode* node) {
  assert(node != NULL);
  /* assert(node->type != NULL); //assume initialized */
  assert(node->val != NULL);

  switch(node->type) {
  case INT:
    break;
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

    //Mal types:

  case MNUM:
    break;
  case MSTR:
    //check is string?
    assert(node->val->str != NULL);
    break;
  case MSYM:
    //check is string?
    assert(node->val->str != NULL);
    break;
  case MLIST:
    //check is valid list?
    assert(node->val->list != NULL);
    break;
  }
}

void ln_free_recur(LNode* node) {
  assert(node != NULL);
  switch(node->type) {
  case LIST:
    ll_free_recur(node->val->list);
    break;
  case TOKEN:
    tok_free(node->val->tok);
    break;
  case MLIST:
    ll_free_recur(node->val->list);
    break;
  default: break;
  }
  ln_free(node);
}

void ln_free(LNode* node) {
  assert(node != NULL);

  switch(node->type) {
  case STRING:
    free(node->val->str);
    break;
  case MSTR:
    free(node->val->str);
    break;
  case MSYM:
    free(node->val->str);
    break;
  case MNUM:
  default: break;
  }
  free(node->val);
  free(node);
}


void ln_asprint(LNode* node, char** ret) {
  switch(node->type) {
  case INT:
    asprintf(ret, "%d", node->val->i);
    break;
  case STRING:
    asprintf(ret, "\"%s\"", node->val->str);
    break;
  case LIST:
    ll_asprint(node->val->list, ret);
    break;
  case TOKEN:
    tok_asprint(node->val->tok, ret);
    break;

  case MNUM:
    asprintf(ret, "%d", node->val->i);
    break;
  case MSTR:
    asprintf(ret, "\"%s\"", node->val->str);
    break;
  case MSYM:
    asprintf(ret, "%s", node->val->str);
    break;
  case MLIST:
    ll_asprint(node->val->list, ret);
    break;
  default:
    asprintf(ret, "?");
    break;
  }
}

void ln_print(LNode* node) {
  char* str;
  ln_asprint(node, &str);
  if (str != NULL) {
    printf("%s", str);
    free(str);
  }else {
    printf("Error! out of memory!\n");
  }
}
