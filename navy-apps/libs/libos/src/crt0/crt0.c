#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int main(int argc, char* argv[], char* envp[]);
extern char** environ;

void call_main(uintptr_t* args) {
  char* empty[] = { NULL };
  uintptr_t argc = *args;

  printf("call_main,argc:%d\n", argc);
  char** argv = args + 1;
  char** envp = args + argc + 2;

  for (size_t i = 0; i < argc; i++) {
    printf("argv%d:%s\n", i, argv[i]);
  }

  while (*envp != NULL) {
    printf("envp:%s\n", *(envp++));
  }

  environ = empty;
  exit(main(argc, argv, envp));
  assert(0);
}
