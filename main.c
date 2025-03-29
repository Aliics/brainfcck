#include "main.h"
#include "state.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

vec_def(int, int)
vec_def(instruct, struct instruct)

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "No file argument given.\n");
    return EXIT_FAILURE;
  }

  char *f_name = argv[1];
  FILE *f = fopen(f_name, "r");

  struct instruct_vec *instructs = instruct_vec_new(8);

  struct state *s = state_new();

  char f_buffer[256];
  while ((fgets(f_buffer, 256, f)) != NULL) {
    char c;
    int i = 0;
    while ((c = f_buffer[i++]) != '\0') {
      state_process_token(s, c, instructs);
    }
  }

  state_free(s);
  instruct_vec_free(instructs);
  fclose(f);

  return EXIT_SUCCESS;
}
