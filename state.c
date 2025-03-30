#include "state.h"
#include "instruct.h"
#include "main.h"
#include "tokens.h"

struct state *state_new() {
  struct state *s = malloc(sizeof(struct state));
  s->comment_buffer = int_vec_new(256);
  s->prev_c = -1; // Ensure that it won't somehow match.
  s->move_right_amount = s->move_left_amount = s->inc_amount = s->dec_amount =
      0;
  return s;
}

void state_free(struct state *s) {
  if (s == NULL)
    return;
  int_vec_free(s->comment_buffer);
  free(s);
}

void state_process_token(struct state *s, char c,
                         struct instruct_vec *instructs) {
  if (s->prev_c != c) {
    switch (s->prev_c) {
    case TK_MOVE_RIGHT:
      instruct_vec_push(instructs, instruct_move_right(s->move_right_amount));
      break;
    case TK_MOVE_LEFT:
      instruct_vec_push(instructs, instruct_move_left(s->move_left_amount));
      break;
    case TK_INC_CELL:
      instruct_vec_push(instructs, instruct_inc(s->inc_amount));
      break;
    case TK_DEC_CELL:
      instruct_vec_push(instructs, instruct_dec(s->dec_amount));
      break;
    }

    s->move_right_amount = s->move_left_amount = s->inc_amount = s->dec_amount =
        0;
  }

  switch (c) {
  case TK_MOVE_RIGHT:
    int_vec_reset(s->comment_buffer);
    ++s->move_right_amount;
    break;
  case TK_MOVE_LEFT:
    int_vec_reset(s->comment_buffer);
    ++s->move_left_amount;
    break;
  case TK_INC_CELL:
    int_vec_reset(s->comment_buffer);
    ++s->inc_amount;
    break;
  case TK_DEC_CELL:
    int_vec_reset(s->comment_buffer);
    ++s->dec_amount;
    break;
  case TK_LOOP_START:
    int_vec_reset(s->comment_buffer);
    instruct_vec_push(instructs, instruct_loop_start());
    break;
  case TK_LOOP_END:
    int_vec_reset(s->comment_buffer);
    instruct_vec_push(instructs, instruct_loop_end());
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

  s->prev_c = c;
}
