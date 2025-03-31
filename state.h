#pragma once

#include "instruct.h"
#include "main.h"
#include "vec.h"
#include "tokens.h"

struct state {
  char prev_c;

  struct int_vec *comment_buffer;

  int move_right_amount;
  int move_left_amount;
  int inc_amount;
  int dec_amount;
};

struct state *state_new();
void state_free(struct state *s);
void state_process_token(struct state *s, char c,
                         struct instruct_vec *instructs);
