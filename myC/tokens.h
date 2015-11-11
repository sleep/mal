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
  /* TLSQR, */
  /* TRSQR, */
  /* TCUR, */
  /* TRCUR, */

  /* TAT, */
  /* TBANG, */


  TNUM,
  TSTR,
  TSYM,

} TokenType;

typedef struct Token {
  TokenType tt;
  TokVal* val;
} Token;

Token* tok_create(TokenType tt, int i, char* str); // can leave latter args NULL

Token* tok_parse(char* str);
void tok_free(Token* tok);
void tok_print(Token* tok);
int tok_equals(Token* a, Token* b);
void tok_assert_equals(Token* a, Token* b);

#endif
