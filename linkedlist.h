struct ll_entry {
  struct ll_entry *next;
  void *data;
};

struct ll_t {
  void (^destroy)();
  void (^add)(void *object);
  void *(^pop)();
  int (^is_empty)();
  struct ll_entry *head;
  struct ll_entry *tail;
};

struct ll_t *ll_create();
