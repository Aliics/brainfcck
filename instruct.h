#pragma once

enum instruct_type {
  INST_MOVE_RIGHT,
  INST_MOVE_LEFT,
  INST_INC,
  INST_DEC,
  INST_WRITE,
  INST_READ,
};

struct instruct {
  enum instruct_type type;
  union {
    int inc_amount;
    int dec_amount;
    int move_right_amount;
    int move_left_amount;
  } data;
};

struct instruct instruct_move_right(int n);
struct instruct instruct_move_left(int n);
struct instruct instruct_inc(int n);
struct instruct instruct_dec(int n);
struct instruct instruct_write();
struct instruct instruct_read();
