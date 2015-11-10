#include "reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>
#include <assert.h>

#include "linkedlist.h"


// Tokenizer

//OPTIMIZATION: don't recompile pcre each time

static const char*  strRegex = "[\\s ,]*(~@|[\\[\\]{}()'`~@]|\"(?:[\\\\].|[^\\\\\"])*\"|;.*|[^\\s \\[\\]{}()'\"`~@,;]*)";
/* static const char* strRegex = "(\\w+)"; */

LList* tokenizer(char* input) {

  const char* pcreErrorStr;
  int pcreErrorOffset;
  pcre* re = pcre_compile(strRegex, 0, &pcreErrorStr, &pcreErrorOffset, NULL);
  int rc = 1; //return value of exec
  const char* tok;

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
      pcre_get_substring(input, oVec, rc, match_no, &tok);
      if (strlen(tok) < 1) {
        pcre_free_substring(tok);
        break;
      }
      /* printf("Start: %2d    Matches:%2d\n", start, rc); */
      /* printf("Match (%2d/%2d): (%2d, %2d): '%s'\n", match_no, rc -1, oVec[match_no*2], oVec[match_no*2+1], tok); */

      LNode* ln = ln_create_str(tok);
      ll_push(tokens, ln);
      pcre_free_substring(tok);

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
  r->tokens = tokenizer(input);
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

LNode* r_peek(Reader* r) {
  return r->curr;
}

LNode* r_next(Reader* r) {
  if (r->pos == -1) {
    return NULL;
  }
  if (r->pos == r->tokens->length) {
    return NULL; //end
  }
  assert(r->pos >=0 && r->pos < r->tokens->length);

  LNode* output = r->curr;
  r->curr = output->next;
  r->pos += 1;
  return output;
}




/* //TODO: move AST to another file */
LNode* parse(Reader* r) {

  LNode* curr;
  while(curr = r_next(r), curr != NULL) {
  }
  r_free(r);

  //dummy
  LNode* ln = malloc(sizeof(LNode));
  return ln;
}

// recursive descent parser
LNode* parse_list(Reader* r) {
  return (LNode*) NULL;
}

LNode* parse_atom(Reader* r) {
  return (LNode*) NULL;
}
