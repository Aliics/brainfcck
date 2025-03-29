#include "state.h"
#include "instruct.h"
#include "tokens.h"

struct state *state_new() {
  struct state *s = malloc(sizeof(struct state));
  s->comment_buffer = int_vec_new(256);
  return s;
}

void state_free(struct state *s) {
  if (s == NULL)
    return;
  int_vec_free(s->comment_buffer);
  free(s);
}

void state_process_token(struct state *s, char c, struct instruct_vec *instructs) {
  switch (c) {
  case TK_MOVE_RIGHT:
    int_vec_reset(s->comment_buffer);
    instruct_vec_push(instructs, instruct_move_right(1));
    break;
  case TK_MOVE_LEFT:
    int_vec_reset(s->comment_buffer);
    instruct_vec_push(instructs, instruct_move_left(1));
    break;
  case TK_INC_CELL:
    int_vec_reset(s->comment_buffer);
    instruct_vec_push(instructs, instruct_inc(1));
    break;
  case TK_DEC_CELL:
    int_vec_reset(s->comment_buffer);
    instruct_vec_push(instructs, instruct_inc(1));
    break;
  case TK_LOOP_START:
    int_vec_reset(s->comment_buffer);
    break;
  case TK_LOOP_END:
    int_vec_reset(s->comment_buffer);
    break;
  case TK_WRITE:
    int_vec_reset(s->comment_buffer);
    instruct_vec_push(instructs, instruct_write());
    break;
  case TK_READ:
    int_vec_reset(s->comment_buffer);
    instruct_vec_push(instructs, instruct_read());
    break;
  default:
    int_vec_push(s->comment_buffer, c);
    break;
  }
}
