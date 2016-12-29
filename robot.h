struct dest_t {
  int is_bot;
  int index;
};

struct rb_t {
  int a_set;
  int b_set;
  int a;
  int b;
  struct dest_t high_destination;
  struct dest_t low_destination;
};

struct rb_t *rb_create(size_t count);

void rb_add_value(struct rb_t *rb, int new);

int rb_complete(struct rb_t *rb);
int rb_high(struct rb_t *rb);
int rb_low(struct rb_t *rb);

void rb_destroy(struct rb_t *robot);
