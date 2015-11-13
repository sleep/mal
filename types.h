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


  MINT,
  MSTR,
  MSYM,
  MKWRD,

  MLIST,
  MVEC,
  MMAP,


} Type;



typedef struct LNode_ LNode;
typedef struct LList_ LList;

typedef union Val_ Val;

union Val_ {
  int i;
  char* str;
  LList* list;
  Token* tok;
};



struct LNode_ {
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



LNode* ln_create_mint(int val);
LNode* ln_create_mstr(char* val);
LNode* ln_create_msym(char* val);
LNode* ln_create_mkwrd(char* val);

LNode* ln_create_mlist(LList* val);
LNode* ln_create_mvec(LList* val); // TODO: Implement mvec
LNode* ln_create_mmap(LList* val); // TODO: Implement mmap

void ln_check(LNode* node);
void ln_free(LNode* node);
void ln_free_recur(LNode* node);

//Must check ret != NULL
void ln_asprint(LNode*, char** ret);
void ln_print(LNode* node);

#endif
