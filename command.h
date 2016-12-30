typedef struct cmd_t {
  void (^destroy)();
  int value;
  int destination;
} Command;

Command *cmd_create(int value, int destination);
