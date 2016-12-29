#include <stdlib.h>
#include <sys/param.h>

#include "robot.h"

struct rb_t *rb_create(size_t count) {
  return calloc(count, sizeof(struct rb_t));
}

int rb_complete(struct rb_t *rb) { return rb->a_set && rb->b_set; }

int rb_high(struct rb_t *rb) { return MAX(rb->a, rb->b); }

int rb_low(struct rb_t *rb) { return MIN(rb->a, rb->b); }

void rb_add_value(struct rb_t *rb, int new) {
  if (rb->a_set == 1) {
    rb->b = new;
    rb->b_set = 1;
  } else {
    rb->a = new;
    rb->a_set = 1;
  }
}

void rb_destroy(struct rb_t *rb) { free(rb); }
