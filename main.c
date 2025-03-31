#include "main.h"
#include "generate.h"
#include "instruct.h"
#include "state.h"
#include "vec.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

vec_def(int, int)
vec_def(instruct, struct instruct) 

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "No file argument given.\n");
    return EXIT_FAILURE;
  }

  int debug_inst = argc >= 3 && strcmp(argv[2], "-d") == 0;

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

  if (debug_inst) {
    char inst_str[64];
    vec_for(instructs, i) {
      instruct_sprint(instruct_vec_get_unsafe(instructs, i), inst_str);
      printf("%s\n", inst_str);
    }
  }

  char *output = generate(instructs);
  printf("%s\n", output);

  free(output);
  state_free(s);
  instruct_vec_free(instructs);
  fclose(f);

  return EXIT_SUCCESS;
}
