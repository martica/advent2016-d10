#include <stdlib.h>

#include "command.h"

Command *cmd_create(int value, unsigned int destination) {
  Command *command = CREATE(Command, NULL);

  command->value = value;
  command->destination = destination;

  return command;
}
