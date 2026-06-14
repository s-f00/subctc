#include <string.h>
#include "scanner.h"

size_t line_number = 0;

void scan(const char *filename) {
  FILE *source;
  // Opening file in read only mode
  // Fails if compiler is located in separate directory from source
  source = fopen(filename, "r");
  if (source == NULL) {
    printf("UNABLE TO OPEN FILE\n");
    return 1;
  }

  fseek(source, 0, SEEK_END);   // SEEK_END = end pos of file
  int length = ftell(source);
  rewind(source);               // sets pos back to start of file

  char buffer[length];
  fread(buffer, sizeof(char), length, source);    // loading source data into buffer as an array of characters
  fclose(filename);   // source no longer needed so close it

  buffer[length] = "\0";    // buffer is now a string, EOF => \0
  int buffer_index = 0;

  // tokenList allocation
  tokenList = (tList *) malloc(sizeof(tList));
  if (tokenList == NULL) {
    printf("TOKENLIST ALLOCATION FAILURE\n");
    return 1;
  }
  else {
    tokenList->head = NULL;
    tokenList->tail = NULL;
  }

  // When checking strings make sure the ptr address and index are updated past the string delimiter
  // Try and figure out if it's possible to strtok_r through the whole file for grabbing t->value(s)
  while (buffer[buffer_index] != "\0") {
    token *t = malloc(sizeof(token));
    /* SCANNER CONTROL FLOW */
    if (buffer[buffer_index] == "\"") {
      generate_string_token(buffer, &buffer_index, t);
    }
    else if (buffer[buffer_index] == "\n") {
      line_number++;
    }
    // Append token to list
    appendToken(tokenList, t);
  }

  printf("scanner generation complete\n");
}

void generate_string_token(char *buffer, int *buffer_index, token *t) {
  t->type = STRING;
  
}

void appendToken(tList *list, token *t) { 
  if (list->head != NULL) {
    t->prev = list->tail;   // Updating t->prev
    list->tail->next = t;   // Updating tail->next
    list->tail = t;         // Updating tail ptr
    list->tail->next = NULL; 
  }
  else {
    list->head = t;
    t->prev = NULL;
    t->next = NULL;
  }
}

// Prints out tokenList in added order
void printToken(token *t) {
  tokenType type = t->type;
  switch (type) {
    case PUNCTUATOR:
      printf("TYPE: PUNCTUATOR, VALUE: %s\n", t->value);
      break;
    case KEYWORD:
      printf("TYPE: KEYWORD, VALUE: %s\n", t->value);
      break;
    case STRING:
      printf("TYPE: STRING, VALUE: %s\n", t->value);
      break;
    case OPERATOR:
      printf("TYPE: OPERATOR, VALUE: %s\n", t->value);
      break;
    case CONST:
      printf("TYPE: CONST, VALUE: %s\n", t->value);
      break;
    case IDENTIFIER:
      printf("TYPE: IDENTIFIER, VALUE: %s\n", t->value);
      break;
  }
}
