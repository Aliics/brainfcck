#include "instruct.h"
#include <stdio.h>

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

void instruct_sprint(struct instruct inst, char *dest) {
  switch (inst.type) {
  case INST_MOVE_RIGHT:
    sprintf(dest, "move_right=%d", inst.data.move_right_amount);
    break;
  case INST_MOVE_LEFT:
    sprintf(dest, "move_left=%d", inst.data.move_left_amount);
    break;
  case INST_INC:
    sprintf(dest, "inc=%d", inst.data.inc_amount);
    break;
  case INST_DEC:
    sprintf(dest, "dec=%d", inst.data.dec_amount);
    break;
  case INST_LOOP_START:
    sprintf(dest, "loop_start");
    break;
  case INST_LOOP_END:
    sprintf(dest, "loop_end");
    break;
  case INST_WRITE:
    sprintf(dest, "write");
    break;
  case INST_READ:
    sprintf(dest, "read");
    break;
  }
}
