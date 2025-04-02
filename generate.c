#include "generate.h"
#include "instruct.h"
#include "main.h"
#include "vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *generate(struct instruct_vec *instructs) {
  int output_len = 19 + 17 + 26 + 14 + 10 + 1;
  char *output = malloc(output_len + 1); // extra +1 for \0

  strcpy(output, "#include <stdio.h>\n"        // 19
                 "int main(void) {\n"          // 17
                 "int cells[1 << 16] = {0};\n" // 26
                 "int cell = 0;\n");           // 14

  char buffer[64] = {0};
  struct instruct inst;
  vec_for(instructs, i) {
    inst = instruct_vec_get_unsafe(instructs, i);
    switch (inst.type) {
    case INST_MOVE_RIGHT:
      sprintf(buffer, "cell += %d;\n", inst.data.move_right_amount);
      break;
    case INST_MOVE_LEFT:
      sprintf(buffer, "cell -= %d;\n", inst.data.move_left_amount);
      break;
    case INST_INC:
      sprintf(buffer, "cells[cell] += %d;\n", inst.data.inc_amount);
      break;
    case INST_DEC:
      sprintf(buffer, "cells[cell] -= %d;\n", inst.data.dec_amount);
      break;
    case INST_LOOP_START:
      sprintf(buffer, "while (cells[cell]) {\n");
      break;
    case INST_LOOP_END:
      sprintf(buffer, "}\n");
      break;
    case INST_WRITE:
      sprintf(buffer, "printf(\"%%c\", cells[cell]);\n");
      break;
    case INST_READ:
      sprintf(buffer, "cells[cell] = getchar();\n");
      break;
    }
    output_len += strlen(buffer);
    char *grow = realloc(output, output_len + 1);
    if (grow == NULL) {
      free(output);
      fprintf(stderr, "Could not grow compiled output data\n");
      exit(EXIT_FAILURE);
    }
    output = grow;
    strcat(output, buffer);
  }

  strcat(output, "return 0;\n" // 10
                 "}");         // 1

  return output;
}
