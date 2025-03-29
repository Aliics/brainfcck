#include "tokens.h"
#include "vec.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "No file argument given.\n");
    return EXIT_FAILURE;
  }

  char *f_name = argv[1];
  FILE *f = fopen(f_name, "r");

  struct int_vec *comment_buffer = int_vec_new(256);

  char f_buffer[256];
  while ((fgets(f_buffer, 256, f)) != NULL) {
    char c;
    int i = 0;
    while ((c = f_buffer[i++]) != '\0') {
      switch (c) {
      case TK_MOVE_RIGHT:
        int_vec_reset(comment_buffer);
        break;
      case TK_MOVE_LEFT:
        int_vec_reset(comment_buffer);
        break;
      case TK_INC_CELL:
        int_vec_reset(comment_buffer);
        break;
      case TK_DEC_CELL:
        int_vec_reset(comment_buffer);
        break;
      case TK_LOOP_START:
        int_vec_reset(comment_buffer);
        break;
      case TK_LOOP_END:
        int_vec_reset(comment_buffer);
        break;
      case TK_WRITE:
        int_vec_reset(comment_buffer);
        break;
      case TK_READ:
        int_vec_reset(comment_buffer);
        break;
      default:

        break;
      }
    }
  }

  int_vec_free(comment_buffer);
  fclose(f);

  return EXIT_SUCCESS;
}
