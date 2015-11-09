#include <stdio.h>
#include <stdlib.h>
#include <pcre.h>
#include <assert.h>
#include "linkedlist.c"


//TODO: don't recompile pcre each time

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
    printf("ERROR: Could not compile mal");
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

      ll_push(tokens, tok);
      pcre_free_substring(tok);

      start = oVec[match_no*2+1];
      iter +=1;
    }
  }

  pcre_free(re);
  return tokens;
}


typedef struct Reader Reader;
struct Reader {
  LList* tokens;
  LNode* curr;
  int pos;
};

void r_checkInvariants(Reader* r) {
  //check existence
  assert(r != NULL);
  assert(r->tokens != NULL);
  //check zero condition
  if (r->tokens->length == 0) {
    assert(r->curr == NULL);
    assert(r->pos = -1);
  }
  if (r->tokens->length > 0){
    assert(r->curr != NULL);
    assert(r->pos >= 0);
    assert(r->pos < r->tokens->length);

    //check inclusion of curr element
    /* int index = 0; */
    LNode* curr = ll_get(r->tokens, 0);
    for (int i = 0 ; i < r->tokens->length; i++) {
      if (curr == r->curr) {
        return;
      }
      curr = curr->next;
    }
    assert(0);
  }

}




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
  ll_free(r->tokens);
  free(r);
}

int r_hasNext(Reader* r) {
  assert(r->tokens->length > 0);
  return r->pos < r->tokens->length -1;
}

LNode* r_peek(Reader* r) {
  return r->curr;
}

// Must check have next before we go next
LNode* r_next(Reader* r) {
  assert(r_hasNext(r));

  LNode* output = r->curr;
  r->curr = output->next;
  r->pos += 1;
  return output;
  
}





