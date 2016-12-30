#include "object.h"

typedef struct cmd_t {
  Object header;
  int value;
  int destination;
} Command;

Command *cmd_create(int value, int destination);
