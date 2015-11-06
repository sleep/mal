#include <stdio.h>
#include <stdlib.h>

char* READ(char* input) {
  return input;
}
char* EVAL(char* input) {
  return input;
}
char* PRINT(char* input) {
  return input;
}

char* rep(char* input) {
  return PRINT(EVAL(READ(input)));
}


int main(int argc, char* argv[]) {
  size_t bytes_read;
  size_t size = 10;
  char* line = malloc(size * sizeof(char));

  while (1) {
    fprintf(stdout, "user> ");
    bytes_read = getline(&line, &size, stdin);

    if (bytes_read == -1) {
      exit(0);
    } else {
      fprintf(stdout, "%s", line);
    }
  }

  //TODO: move to gnu readline
}
