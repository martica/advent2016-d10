#include <Block.h>
#include <stdlib.h>
#include <sys/param.h>

#include "robot.h"

void rb_add_value(Robot *rb, int new) {
  if (!rb->a_set) {
    rb->a = new;
    rb->a_set = 1;
  } else {
    rb->b = new;
    rb->b_set = 1;
  }
}

struct rb_state rb_get_state(Robot *rb) {
  return (struct rb_state){
      .is_complete = rb->a_set && rb->b_set,
      .outputs = {
          {
              .destination = rb->high_destination,
              .value = MAX(rb->a, rb->b)
          },
          {
              .destination = rb->low_destination,
              .value = MIN(rb->a, rb->b)
          }}};
}

void rb_set_destinations(Robot *rb, struct dest_t low, struct dest_t high) {
  rb->low_destination = low;
  rb->high_destination = high;
}

void rb_init(Object *object) {
  Robot *robot = (Robot *)object;

  robot->add = METHOD(robot, ^(int value) { rb_add_value(robot, value); });
  robot->state = METHOD(robot, ^ {return rb_get_state(robot);});
  robot->set_destinations = METHOD(
      robot,
      ^(struct dest_t low, struct dest_t high) {
        rb_set_destinations(robot, low, high);
      });
}

Robot *rb_create() {
  return CREATE(Robot, (^(Object *o) { rb_init(o); }));
}

