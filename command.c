#include <stdlib.h>
#include <Block.h>

#include "command.h"

struct cmd_t *cmd_create(int value, int destination) {
  struct cmd_t *cmd = calloc(sizeof(struct cmd_t), 1);
  cmd->value = value;
  cmd->destination = destination;
  cmd->destroy = Block_copy(^ {});
  return cmd;
}
