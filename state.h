#pragma once

#include "vec.h"
#include "instruct.h"
#include "main.h"

struct state {
  struct int_vec *comment_buffer;
};

struct state *state_new();
void state_free(struct state *s);
void state_process_token(struct state *s, char c, struct instruct_vec *instructs);
