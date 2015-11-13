#ifndef TOKENS_H
#define TOKENS_H

typedef union TokVal TokVal;
union TokVal {
  int i;
  char* str;
  //macro?
};

//TODO Implement more token types
typedef enum TokenType {
  TLP,
  TRP,
  TLSQR,
  TRSQR,
  TLCUR,
  TRCUR,

  TINT,
  TSYM,
  TSTR,
  TKWRD,
} TokenType;

typedef struct Token {
  TokenType tt;
  TokVal* val;
} Token;

Token* tok_create(TokenType tt, int i, char* str); // can leave latter args NULL

Token* tok_parse(char* str);
void tok_free(Token* tok);

//Must check ret != NULL
void tok_asprint(Token* tok, char** ret);
void tok_print(Token* tok);

int tok_equals(Token* a, Token* b);
void tok_assert_equals(Token* a, Token* b);

#endif
