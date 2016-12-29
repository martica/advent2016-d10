#include <stdlib.h>
#include <sys/param.h>
#include <Block.h>

#include "robot.h"

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

struct rb_t *rb_create(size_t count) {
  struct rb_t *robots = calloc(count, sizeof(struct rb_t));

  for (int i=0; i<count; i++) {
    struct rb_t *robot = &robots[i];
    robot->add = Block_copy(^(int value) { rb_add_value(robot, value); });
    robot->is_complete = Block_copy(^() { return rb_complete(robot); });
    robot->high = Block_copy(^() { return rb_high(robot); });
    robot->low = Block_copy(^() { return rb_low(robot); });
    robot->destroy = Block_copy(^() {});
  }

  return robots;
}
