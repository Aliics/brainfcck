#pragma once

#include <stdio.h>
#include <stdlib.h>

#define vec_decl(name, T)                                                      \
  struct name##_vec {                                                          \
    int capacity;                                                              \
    int len;                                                                   \
    T *data;                                                                   \
  };                                                                           \
  struct name##_vec *name##_vec_new(int capacity);                             \
  void name##_vec_free(struct name##_vec *v);                                  \
  void name##_vec_push(struct name##_vec *v, T n);                             \
  T name##_vec_get(struct name##_vec *v, int i);                               \
  void name##_vec_reset(struct name##_vec *v);                                 \
  void name##_vec_remove_at(struct name##_vec *v, int i);

#define vec_def(name, T)                                                       \
  struct name##_vec *name##_vec_new(int capacity) {                            \
    struct name##_vec *v =                                                     \
        (struct name##_vec *)malloc(sizeof(struct name##_vec));                \
    v->capacity = capacity;                                                    \
    v->len = 0;                                                                \
    v->data = (T *)malloc(capacity * sizeof(T));                               \
    return v;                                                                  \
  }                                                                            \
                                                                               \
  void name##_vec_free(struct name##_vec *v) {                                 \
    if (v == NULL)                                                             \
      return;                                                                  \
    free(v->data);                                                             \
    free(v);                                                                   \
  }                                                                            \
                                                                               \
  void name##_vec_push(struct name##_vec *v, T n) {                            \
    if (v->len >= v->capacity) {                                               \
      v->capacity += 8;                                                        \
      T *grow = (T *)realloc(v->data, v->capacity * sizeof(T));                \
      if (grow == NULL) {                                                      \
        free(v->data);                                                         \
        fprintf(stderr, "Capacity growing failed\n");                          \
        exit(EXIT_FAILURE);                                                    \
      }                                                                        \
      v->data = grow;                                                          \
    }                                                                          \
                                                                               \
    v->data[v->len++] = n;                                                     \
  }                                                                            \
                                                                               \
  T name##_vec_get(struct name##_vec *v, int i) {                              \
    if (i < 0 || v->len <= i) {                                                \
      fprintf(stderr, "Attempt to index name##_vec out of bounds: %d\n", i);   \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
                                                                               \
    return v->data[i];                                                         \
  }                                                                            \
                                                                               \
  void name##_vec_reset(struct name##_vec *v) {                                \
    v->capacity = 0;                                                           \
    v->len = 0;                                                                \
  }                                                                            \
                                                                               \
  void name##_vec_remove_at(struct name##_vec *v, int i) {                     \
    if (i < 0 || v->len <= i) {                                                \
      fprintf(stderr, "Attempt to index name##_vec out of bounds: %d\n", i);   \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
                                                                               \
    --v->len;                                                                  \
    for (; i < v->len; ++i) {                                                  \
      v->data[i] = v->data[i + 1];                                             \
    }                                                                          \
  }
