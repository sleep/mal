#include "tokens.h"

#ifndef TYPES_H
#define TYPES_H


// we separate mal types from non-mal types in case
// we want to implement additional functionality
// for objects of mal data types, yet not
// bog down the objects of native types

typedef enum {
  INT,
  STRING,
  LIST,
  TOKEN,


  MNUM,
  MSTR,
  MSYM,
  MLIST
  /* M_KEYWORD, */
  /* M_VECTOR,  */
  /* M_HASHMAP*/
} Type;



typedef struct LNode LNode;
typedef struct LList LList;

typedef union Val Val;

union Val {
  int i;
  char* str;
  LList* list;
  Token* tok;
};



struct LNode {
  Type type;
  LNode* next;
  Val* val;
  //add additional data types as needed...
  // yes, not the most memory efficient, but whatev...
};

LNode* ln_create_int(int val);
LNode* ln_create_str(char* val);
LNode* ln_create_list(LList* val);
LNode* ln_create_tok(Token* val);

LNode* ln_create_mnum(int val);
LNode* ln_create_mstr(char* val);
LNode* ln_create_msym(char* val);
LNode* ln_create_mlist(LList* val);

void ln_check(LNode* node);
void ln_free(LNode* node);
void ln_free_recur(LNode* node);
void ln_print(LNode* node);

#endif
