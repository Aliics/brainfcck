#pragma once

#include "vec.h"
#include "instruct.h"
#include "main.h"

struct state {
  char prev_c;

  struct int_vec *comment_buffer;

  int move_amount;
  int change_amount;
};

struct state *state_new();
void state_free(struct state *s);
void state_process_token(struct state *s, char c, struct instruct_vec *instructs);
