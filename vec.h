#pragma once

#include <stdlib.h>

struct int_vec {
  int capacity;
  int len;

  int *data;
};

struct int_vec *int_vec_new(int capacity);
void int_vec_free(struct int_vec* v);

void int_vec_push(struct int_vec* v, int n);
int int_vec_get(struct int_vec* v, int i);

void int_vec_reset(struct int_vec *v);
void int_vec_remove_at(struct int_vec *v, int i);
