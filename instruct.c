#include "instruct.h"

struct instruct instruct_move_right(int n) {
  return (struct instruct){
      .type = INST_MOVE_RIGHT,
      .data.move_right_amount = n,
  };
}

struct instruct instruct_move_left(int n) {
  return (struct instruct){
      .type = INST_MOVE_LEFT,
      .data.move_left_amount = n,
  };
}

struct instruct instruct_inc(int n) {
  return (struct instruct){
      .type = INST_INC,
      .data.inc_amount = n,
  };
}

struct instruct instruct_dec(int n) {
  return (struct instruct){
      .type = INST_DEC,
      .data.dec_amount = n,
  };
}

struct instruct instruct_write() {
  return (struct instruct){
      .type = INST_WRITE,
  };
}

struct instruct instruct_loop_start() {
  return (struct instruct){
      .type = INST_LOOP_START,
  };
}

struct instruct instruct_loop_end() {
  return (struct instruct){
      .type = INST_LOOP_END,
  };
}

struct instruct instruct_read() {
  return (struct instruct){
      .type = INST_READ,
  };
}
