struct dest_t {
  int is_bot;
  int index;
};

struct rb_t {
  void (^destroy)();
  int (^is_complete)();
  int (^high)();
  int (^low)();
  void (^add)(int value);
  int a_set;
  int b_set;
  int a;
  int b;
  struct dest_t high_destination;
  struct dest_t low_destination;
};

struct rb_t *rb_create(size_t count);
