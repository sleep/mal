#ifndef TYPES_H
#define TYPES_H

typedef enum {
  STRING,
  LIST,


  MT_LIST,
  MT_SYMBOL,
  MT_NUMBER,
  /* M_KEYWORD, */
  /* M_VECTOR,  */
  /* M_HASHMAP*/
} Type; //MalType



typedef struct LNode LNode;
typedef struct LList LList;

typedef union Val Val;
union Val {
  int i;
  char* str;
  LList* list;
};



struct LNode {
  Type type;
  LNode* next;
  Val* val;
};

LNode* ln_create_str(char const * val);
LNode* ln_create_list(LList* val);

void ln_check(LNode* node);
void ln_free(LNode* node);
void ln_free_recur(LNode* node);
void ln_print(LNode* node);
#endif
