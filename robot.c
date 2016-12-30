#include <Block.h>
#include <stdlib.h>
#include <sys/param.h>

#include "robot.h"
#include "object.h"

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

  *robot = (Robot) {
      .add = Block_copy(^(int value) { rb_add_value(robot, value); }),
      .state = Block_copy(^() { return rb_get_state(robot); }),
      .set_destinations = Block_copy(
          ^(struct dest_t low, struct dest_t high) {
            rb_set_destinations(robot, low, high);
          }),
      .destroy = Block_copy(^() {
        Block_release(robot->add);
        Block_release(robot->state);
        Block_release(robot->set_destinations);
      })};
}

Robot *rb_create() {
  return CREATE(Robot, (^(Object *o) { rb_init(o); }));
}

