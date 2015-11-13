#include "tokens.h"

#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "assert.h"
#include "ctype.h"

Token* tok_create(TokenType tt, int i, char* str) {
  Token* tok = malloc(sizeof(Token));
  tok->tt = tt;


  int j;
  // fill values, if exists
  switch(tt) {
  case TINT:
    tok->val = malloc(sizeof(TokVal));
    tok->val->i = i;
    break;
  case TSYM:
    tok->val = malloc(sizeof(TokVal));
    tok->val->str = strdup(str);
    break;
  case TKWRD:
    tok->val = malloc(sizeof(TokVal));
    tok->val->str = malloc(strlen(str) + 1 - 1);
    for (j = 0; j < strlen(str)-1; j++) {
      tok->val->str[j] = str[j+1];
    }
    tok->val->str[j] = '\0';
    break;
  case TSTR:
    tok->val = malloc(sizeof(TokVal));
    //manual copy... spent a whole hour debugging sprintf/sscanf
    tok->val->str = malloc(strlen(str) + 1 - 2);
    for (j = 0; j < strlen(str)-2; j++) {
      tok->val->str[j] = str[j+1];
    }
    tok->val->str[j] = '\0';

    break;
  default:
    break;
  }

  return tok;
}

void tok_free(Token* tok) {
  switch(tok->tt) {
  case TINT:
    free(tok->val);
    break;
  case TKWRD:
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
  if (tok == NULL) {
    asprintf(ret, "EOF");
    return;
  }
  switch(tok->tt) {
  case TINT:
    asprintf(ret, "%d", tok->val->i);
    break;
  case TKWRD:
    asprintf(ret, ":%s", tok->val->str);
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
  case TLSQR:
    asprintf(ret, "[");
    break;
  case TRSQR:
    asprintf(ret, "]");
    break;
  case TLCUR:
    asprintf(ret, "{");
    break;
  case TRCUR:
    asprintf(ret, "}");
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
  if (str[0] == ';') return NULL; //reject comments

  if (str[0] == '(') return tok_create(TLP, 0, NULL);
  if (str[0] == ')') return tok_create(TRP, 0, NULL);
  if (str[0] == '{') return tok_create(TLCUR, 0, NULL);
  if (str[0] == '}') return tok_create(TRCUR, 0, NULL);
  if (str[0] == '[') return tok_create(TLSQR, 0, NULL);
  if (str[0] == ']') return tok_create(TRSQR, 0, NULL);

  if (str[0] == ':') return tok_create(TKWRD, 0, str);
  if (str[0] == '"') return tok_create(TSTR, 0, str);

  if (isdigit(str[0])){
    int i = 0;
    sscanf(str, "%d", &i);
    return tok_create(TINT, i, NULL);
  }

  // else
  return tok_create(TSYM, 0, str);
}

int tok_equals(Token* a, Token* b) {
  if (a->tt != b->tt) return 0;

  switch(a->tt) {
  case TINT:
    assert(a->val != NULL && b->val != NULL);
    return a->val->i == b->val->i;
    break;
  case TKWRD:
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
  case TINT:
    assert(a->val != NULL && b->val != NULL);
    assert(a->val->i == b->val->i);
    break;
  case TKWRD:
    assert(a->val != NULL && b->val != NULL);
    assert(strlen(a->val->str) == strlen(b->val->str));
    assert(strcmp(a->val->str, b->val->str) == 0);
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
