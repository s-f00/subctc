#include "scanner.h"

void scan(const char *filename) {
  printf("scanner function\n");
};


void appendToken(tList *list, token *t) { 
  t->prev = list->tail;   // Updating t prev ptr
  list->tail->next = t;   // Updating tail next ptr
  list->tail = t;         // Updating tail ptr
  list->tail->next = NULL;
}

// Prints out tokenList in added order
void printTokenList(tList *list) {
  token *curr = list->head;
  int count = 0;
  while (curr != NULL) {
    tokenType type = curr->type;
    switch (type) {
      case PUNCTUATOR:
        printf("[%d] TYPE: PUNCTUATOR, VALUE: %s\n", count, curr->value);
        break;
      case KEYWORD:
        printf("[%d] TYPE: KEYWORD, VALUE: %s\n", count, curr->value);
        break;
      case STRING:
        printf("[%d] TYPE: STRING, VALUE: %s\n", count, curr->value);
        break;
      case OPERATOR:
        printf("[%d] TYPE: OPERATOR, VALUE: %s\n", count, curr->value);
        break;
      case IDENTIFIER:
        printf("[%d] TYPE: IDENTIFIER, VALUE: %s\n", count, curr->value);
        break;
    }
    curr = curr->next;
    count++;
  }
  printf("Print complete\n");
}
