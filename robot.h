struct dest_t {
  int is_bot;
  int index;
};

struct rb_output {
  struct dest_t destination;
  int value;
};

struct rb_state {
  int is_complete;
  struct rb_output outputs[2];
};

typedef struct rb_t {
  void (^destroy)();
  struct rb_state (^state)();
  void (^set_destinations)(struct dest_t low, struct dest_t high);
  void (^add)(int value);
  int a_set;
  int b_set;
  int a;
  int b;
  struct dest_t high_destination;
  struct dest_t low_destination;
} Robot;

Robot *rb_create();
