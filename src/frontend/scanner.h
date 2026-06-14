#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/* Token type source: https://www.geeksforgeeks.org/c/tokens-in-c/
 *
 *  PUNCTUATOR = {"[]", "()", "{}", ",", ";", "*", "=", "&"}
 *  KEYWORD = {int, char, void, if, else, for, while, return}
 *  STRING = "{sequence of ASCII chars}\0"
 *  OPERATOR = Arithmetic: {+,-,*,/}
 *             Relational: {<,>,<=, >=, ==, !=}
 *             Logical:    {&&, ||, !}
 *             Bitwise:    {&, |, ^, <<, >>}
 *  CONST = {const}
 *  IDENTIFIER = Begins with char[A:z | _],
 *               Followed by {char[A:z], char[0:9], _}
 *
*/

typedef enum {
  PUNCTUATOR,     
  KEYWORD,
  STRING,
  OPERATOR,
  CONST,
  IDENTIFIER,
} tokenType;

typedef struct token {
  tokenType type;     // type from tokenType enum
  char *value;        // String value of token
  size_t line_num;    // Line number token is found on (unnecessary?)
  // Token List pointers
  struct token *next;
  struct token *prev;
} token;

typedef struct tList {
  token *head;
  token *tail;
} tList;

tList *tokenList;

void scan(const char *filename);
void generate_string_token(char *buffer, int *buffer_index, token *t);
void appendToken(tList *list, token *);
void printToken(token *t);
