#include <stdio.h>

int main(int argc, char* argv[]) {
  
  if (argc == 1) {
    printf("ERROR: MISSING SOURCE FILE\n");
    return 1;
  }

  const char *filename = argv[1];
  scan(filename);
  
  printf("build.c exited\n");
  return 0;
}
