#include "object.h"

typedef struct cmd_t {
  Object header;
  int value;
  unsigned int destination;
} Command;

Command *cmd_create(int value, unsigned int destination);
