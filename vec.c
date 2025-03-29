#include "vec.h"
#include <stdio.h>
#include <stdlib.h>

struct int_vec *int_vec_new(int capacity) {
  struct int_vec *v = (struct int_vec *)malloc(sizeof(struct int_vec));
  v->capacity = capacity;
  v->len = 0;
  v->data = (int *)malloc(capacity * sizeof(int));
  return v;
}

void int_vec_free(struct int_vec *v) {
  if (v == NULL)
    return;
  free(v->data);
  free(v);
}

void int_vec_push(struct int_vec *v, int n) {
  if (v->len >= v->capacity) {
    v->capacity += 8;
    int *grow = realloc(v->data, v->capacity * sizeof(int));
    if (grow == NULL) {
      free(v->data);
      fprintf(stderr, "Capacity growing failed\n");
      exit(EXIT_FAILURE);
    }
    v->data = grow;
  }

  v->data[v->len++] = n;
}

int int_vec_get(struct int_vec *v, int i) {
  if (i < 0 || v->len <= i) {
    fprintf(stderr, "Attempt to index int_vec out of bounds: %d\n", i);
    exit(EXIT_FAILURE);
  }

  return v->data[i];
}

void int_vec_reset(struct int_vec *v) {
  v->capacity = 0;
  v->len = 0;
}

void int_vec_remove_at(struct int_vec *v, int i) {
  if (i < 0 || v->len <= i) {
    fprintf(stderr, "Attempt to index int_vec out of bounds: %d\n", i);
    exit(EXIT_FAILURE);
  }

  --v->len;
  for (; i < v->len; ++i) {
    v->data[i] = v->data[i + 1];
  }
}
