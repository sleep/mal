#include "tokens.h"

#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "assert.h"
#include "ctype.h"

Token* tok_create(TokenType tt, int i, char* str) {
  Token* tok = malloc(sizeof(Token));
  tok->tt = tt;


  // fill values, if exists
  switch(tt) {
  case TNUM:
    tok->val = malloc(sizeof(TokVal));
    tok->val->i = i;
    break;
  case TSYM:
    tok->val = malloc(sizeof(TokVal));
    tok->val->str = strdup(str);
    break;
  case TSTR:
    tok->val = malloc(sizeof(TokVal));
    //manual copy... spent a whole hour debugging sprintf/sscanf
    tok->val->str = malloc(strlen(str) + 1 - 2);
    int i;
    for (i = 0; i < strlen(str)-2; i++) {
      tok->val->str[i] = str[i+1];
    }
    tok->val->str[i] = '\0';

    break;
  default:
    break;
  }

  return tok;
}

void tok_free(Token* tok) {
  switch(tok->tt) {
  case TNUM:
    free(tok->val);
    break;
  case TSYM:
  case TSTR:
    free(tok->val->str);
    free(tok->val);
    break;
  default:
    break;
  }
  free(tok);
}

void tok_asprint(Token* tok, char** ret) {
  assert(tok !=NULL);
  switch(tok->tt) {
  case TNUM:
    asprintf(ret, "%d", tok->val->i);
    break;
  case TSTR:
    asprintf(ret, "\"%s\"", tok->val->str);
    break;
  case TSYM:
    asprintf(ret, "%s", tok->val->str);
    break;
  case TLP:
    asprintf(ret, "(");
    break;
  case TRP:
    asprintf(ret, ")");
    break;
  default:
    asprintf(ret, "???");
    break;
  }
  //TODO: finish print tokens part
}

void tok_print(Token* tok) {
  char* str;
  tok_asprint(tok, &str);
  if (str != NULL) {
    printf("%s", str);
    free(str);
  }else {
    printf("Error! Ran out of memory!\n");
  }
}


//takes regex output and returns Tokens
Token* tok_parse(char* str) {
  if (str[0] == '(') return tok_create(TLP, 0, NULL);
  if (str[0] == ')') return tok_create(TRP, 0, NULL);

  if (str[0] == '"') return tok_create(TSTR, 0, str);

  if (isdigit(str[0])){
    int i = 0;
    sscanf(str, "%d", &i);
    return tok_create(TNUM, i, NULL);
  }


  // else
  return tok_create(TSYM, 0, str);
}

int tok_equals(Token* a, Token* b) {
  if (a->tt != b->tt) return 0;

  switch(a->tt) {
  case TNUM:
    assert(a->val != NULL && b->val != NULL);
    return a->val->i == b->val->i;
    break;
  case TSTR:
  case TSYM:
    assert(a->val != NULL && b->val != NULL);
    return ((strlen(a->val->str) == strlen(b->val->str)) ||(strcmp(a->val->str, b->val->str) == 0));
  default: return 1;
  }
}


void tok_assert_equals(Token* a, Token* b) {
  assert(a->tt == b->tt);

  switch(a->tt) {
  case TNUM:
    assert(a->val != NULL && b->val != NULL);
    assert(a->val->i == b->val->i);
    break;
  case TSTR:
    assert(a->val != NULL && b->val != NULL);
    assert(strlen(a->val->str) == strlen(b->val->str));
    assert(strcmp(a->val->str, b->val->str) == 0);
    break;
  case TSYM:
    assert(a->val != NULL && b->val != NULL);
    assert(strlen(a->val->str) == strlen(b->val->str));
    assert(strcmp(a->val->str, b->val->str) == 0);
    break;
  default: break;
  }
}
