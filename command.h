struct cmd_t {
  void (^destroy)();
  int value;
  int destination;
};

struct cmd_t *cmd_create(int value, int destination);

void cmd_destroy(struct cmd_t *cmd);
