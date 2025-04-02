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

vec_def(int, int);
vec_def(instruct, struct instruct);

struct cli_options {
  int show_help;
  int debug_inst;
  int log_output;
  char *input_filename;
  char *output_filename;
};

void cli_options_free(struct cli_options o) {
  if (o.input_filename != NULL)
    free(o.input_filename);
  if (o.output_filename != NULL)
    free(o.output_filename);
}

struct cli_options get_options(int argc, char **argv) {
  struct cli_options o = {};

  if (argc < 2)
    return o;

  if (argc == 2) {
    // Just an input file was provided.
    o.input_filename = argv[1];
    return o;
  }

  for (int i = 1; i < argc; ++i) {
    char *a = argv[i];
    if (strcmp(a, "-h") == 0) {
      o.show_help = 1;
      return o;
    }

    if (strcmp(a, "-d") == 0) {
      o.debug_inst = 1;
      continue;
    }

    if (strcmp(a, "-l") == 0) {
      o.log_output = 1;
      continue;
    }

    if (strcmp(a, "-i") == 0 && argc > i + 1) {
      o.input_filename = malloc(strlen(argv[++i]) + 1);
      strcpy(o.input_filename, argv[i]);
      continue;
    }

    if (strcmp(a, "-o") == 0 && argc > i + 1) {
      o.output_filename = malloc(strlen(argv[++i]) + 1);
      strcpy(o.output_filename, argv[i]);
      continue;
    }

    fprintf(stderr, "Invalid argument: \"%s\"\n", a);
    exit(EXIT_FAILURE);
  }

  return o;
}

int main(int argc, char **argv) {
  struct cli_options o = get_options(argc, argv);

  if (o.show_help) {
    printf("brainfcck INPUT_FILE|ARGS\n\n"
           "-h\tShow this help message\n"
           "-d\tDebug instructions\n"
           "-l\tLog compiled output\n"
           "-i STR\tExplicitly provide an input file\n"
           "-o STR\tProvide an output file name\n");

    return EXIT_SUCCESS;
  }
  if (o.input_filename == NULL) {
    fprintf(stderr, "No input file argument given.\n");
    return EXIT_FAILURE;
  }

  FILE *f = fopen(o.input_filename, "r");
  if (f == NULL) {
    fprintf(stderr, "No such file: \"%s\"\n", o.input_filename);
    return EXIT_FAILURE;
  }

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

  if (o.debug_inst) {
    printf("INSTRUCTIONS:\n");
    char inst_str[64];
    vec_for(instructs, i) {
      instruct_sprint(instruct_vec_get_unsafe(instructs, i), inst_str);
      printf("%s\n", inst_str);
    }
  }

  char *output_c = generate(instructs);
  if (o.log_output) {
    printf("COMPILED OUTPUT:\n");
    printf("%s\n", output_c);
  }

  char *output_f = o.output_filename ? o.output_filename : "bf_compiled";
  char *output_c_f = malloc(strlen(output_f) + 3); // +2 for .c +1 for \0

  sprintf(output_c_f, "%s.c", output_f);
  FILE *c_f = fopen(output_c_f, "w+");
  fprintf(c_f, "%s", output_c);
  fclose(c_f);

  // +7 for cc -o and spaces and +1 for \0
  char *cmd = malloc(strlen(output_f) + strlen(output_c_f) + 8);
  sprintf(cmd, "cc -o %s %s", output_f, output_c_f);
  system(cmd);

  free(cmd);
  free(output_c_f);
  free(output_c);
  state_free(s);
  instruct_vec_free(instructs);
  fclose(f);
  cli_options_free(o);

  return EXIT_SUCCESS;
}
