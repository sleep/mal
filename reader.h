#include "linkedlist.h"

#ifndef READER_H
#define READER_H

LList* tokenize(char* input);

typedef struct Reader_ Reader;
struct Reader_ {
  LList* tokens;
  LNode* curr;
  int pos;
};

Reader* r_create(char* input);

void r_free(Reader* r);
void r_check(Reader* r);
Token* r_peek(Reader* r);
Token* r_next(Reader* r);



LNode* parse(Reader* r);
LNode* parse_list(Reader* r);
LNode* parse_vec(Reader* r);
LNode* parse_map(Reader* r);
LNode* parse_atom(Reader* r);

#endif

// TODO: make things private
// TODO: make tests require .c files...
