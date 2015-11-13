#include "reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>
#include <assert.h>

#include "types.h"
#include "tokens.h"
#include "linkedlist.h"



// Tokenizer

//OPTIMIZATION: don't recompile pcre each time

static const char*  strRegex = "[\\s ,]*(~@|[\\[\\]{}()'`~@]|\"(?:[\\\\].|[^\\\\\"])*\"|;.*|[^\\s \\[\\]{}()'\"`~@,;]*)";
/* static const char* strRegex = "(\\w+)"; */

LList* tokenize(char* input) {

  const char* pcreErrorStr;
  int pcreErrorOffset;
  pcre* re = pcre_compile(strRegex, 0, &pcreErrorStr, &pcreErrorOffset, NULL);
  int rc = 1; //return value of exec
  const char* tokstr;

  int oVec[30]; //positions of exec result

  if (re == NULL) {
    printf("ERROR: Could not compile mal regex\n");
    exit(1);
  }

  int iter = 0;
  int start = 0;
  LList* tokens = ll_create();
  while (iter < 100) {
    rc = pcre_exec(re,
                   NULL,
                   input,
                   strlen(input),
                   start,
                   0,
                   oVec,
                   sizeof(oVec)/sizeof(int));


    if (rc <= 0) { //Error!
      if (rc < 0) {
        printf("ERROR! No match?? %d\n", rc);
      }
      if (rc == 0) {
        printf("ERROR! String too long!!");
      }
      break;
    }else {

      int match_no = 1;
      pcre_get_substring(input, oVec, rc, match_no, &tokstr);
      if (strlen(tokstr) < 1) {
        pcre_free_substring(tokstr);
        break;
      }
      /* printf("Start: %2d    Matches:%2d\n", start, rc); */
      /* printf("Match (%2d/%2d): (%2d, %2d): '%s'\n", match_no, rc -1, oVec[match_no*2], oVec[match_no*2+1], tok); */

      char* unconsted = strdup(tokstr);
      Token* tok = tok_parse(unconsted);
      if (tok != NULL) {
        LNode* ln = ln_create_tok(tok);
        ll_push(tokens, ln);
      }
      free(unconsted);
      pcre_free_substring(tokstr);

      start = oVec[match_no*2+1];
      iter +=1;
    }
  }

  pcre_free(re);
  return tokens;
}

// Reader




Reader* r_create(char* input) {
  Reader* r = malloc(sizeof(Reader));
  r->tokens = tokenize(input);
  assert(r->tokens != NULL);

  if (r->tokens->length == 0) {
    r->curr = NULL;
    r->pos = -1;
  } else {
    r->curr = ll_get(r->tokens, 0);
    r->pos = 0;
  }
  return r;
}

void r_free(Reader* r) {
  ll_free_recur(r->tokens);
  free(r);
}

void r_check(Reader* r) {
  //check existence
  assert(r != NULL);
  assert(r->tokens != NULL);

  //check zero-length condition
  if (r->tokens->length == 0) {
    assert(r->curr == NULL);
    assert(r->pos = -1);
  }

  //check non-zero length condition
  if (r->tokens->length > 0) {
    assert(r->pos >= 0 && r->pos <= r->tokens->length);

    // check end condition
    if(r->pos == r->tokens->length) {
      assert(r->curr == NULL);
    }else {
      // check non-end condition

      ll_check(r->tokens);
      //check inclusion of curr element
      int found = 0;
      LNode* curr = r->curr;
      for (int i = 0 ; i < r->tokens->length; i++) {
        if (curr == r->curr) {
          found = 1;
          break;
        }
        curr = curr->next;
      }
      assert(found);
    }
  }
}

Token* r_peek(Reader* r) {
  if ((r->pos == -1) || (r->pos == r->tokens->length)) {
    return NULL; // return NULL if empty, or at end;
  }
  assert(r->pos >=0 && r->pos < r->tokens->length);

  return r->curr->val->tok;
}

Token* r_next(Reader* r) {
  if ((r->pos == -1) || (r->pos == r->tokens->length)) {
    return NULL; // return NULL if empty, or at end;
  }
  assert(r->pos >=0 && r->pos < r->tokens->length);

  LNode* outputNode = r->curr;

  r->curr = outputNode->next;
  r->pos += 1;
  return outputNode->val->tok;
}


//@private
//returns 1 if next token is of the expected type, 0 if not.
int r_accept(Reader* r, TokenType expected) {
  Token* next = r_next(r);
  if (next == NULL) return 0;
  return next->tt == expected;
}




/* //TODO: move AST to another file */
LNode* parse(Reader* r) {
  Token* curr = r_peek(r);
  if (curr == NULL) return NULL;

  switch(curr->tt) {
  case TLP:
    return parse_list(r);
  case TLSQR:
    return parse_vec(r);
  case TLCUR:
    return parse_map(r);

  case TRP:
    printf("; unexpected token ");
    tok_print(curr);
    printf("\n");
    return (LNode*) NULL;
  case TRSQR:
    return (LNode*) NULL;
  case TRCUR:
    return (LNode*) NULL;

  default:
    return parse_atom(r);
  }
}

// recursive descent parser
LNode* parse_list(Reader* r) {
  if (r_accept(r, TLP)) {
    Token* curr;

    LList* list = ll_create();
    LNode* output = ln_create_list(list);

    while(curr = r_peek(r), curr != NULL) {
      if (curr->tt == TRP) {
        r_accept(r, TRP);
        return output; //yay!
      }

      LNode* atom = parse(r);
      ll_push(list, atom);
    }

    //Reach end, error parsing
    //TODO: return error code?

    printf("; expected ')', got");
    tok_print(curr);
    printf("\n");
    ln_free_recur(output);
    return (LNode*) NULL;
  }
  printf("; fatal: expected '('");
  exit(1);
}

// recursive descent parser
LNode* parse_vec(Reader* r) {
  if (r_accept(r, TLSQR)) {
    Token* curr;

    LList* list = ll_create();
    LNode* output = ln_create_list(list);

    while(curr = r_peek(r), curr != NULL) {
      if (curr->tt == TRSQR) {
        r_accept(r, TRSQR);
        return output; //yay!
      }

      LNode* atom = parse(r);
      ll_push(list, atom);
    }

    //Reach end, error parsing
    //TODO: return error code?

    printf("; expected ']', got EOF\n");
    ln_free_recur(output);
    return (LNode*) NULL;
  }
  printf("; fatal: expected '['");
  exit(1);
}

// recursive descent parser
LNode* parse_map(Reader* r) {
  if (r_accept(r, TLCUR)) {
    Token* curr;

    LList* list = ll_create();
    LNode* output = ln_create_list(list);

    while(curr = r_peek(r), curr != NULL) {
      if (curr->tt == TRCUR) {
        r_accept(r, TRCUR);
        return output; //yay!
      }

      LNode* atom = parse(r);
      ll_push(list, atom);
    }

    //Reach end, error parsing
    //TODO: return error code?

    printf("; expected '}', got EOF\n");
    ln_free_recur(output);
    return (LNode*) NULL;
  }
  printf("; fatal: expected '{'");
  exit(1);
}

LNode* parse_atom(Reader* r) {
  Token* curr = r_next(r);
  assert(curr != NULL);

  switch(curr->tt) {
  case TINT:
    return ln_create_mint(curr->val->i);
  case TKWRD:
    return ln_create_mkwrd(curr->val->str);
  case TSYM:
    return ln_create_msym(curr->val->str);
  case TSTR:
    return ln_create_mstr(curr->val->str);
  default:
    printf("; unexpected token %s\n", curr->val->str);
    return (LNode*) NULL;
  }
}
