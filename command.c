#include <stdlib.h>

#include "command.h"

void cmd_init(Object *object, int value, unsigned int destination) {
  Command *command = (Command *)object;

  command->value = value;
  command->destination = destination;
}

Command *cmd_create(int value, unsigned int destination) {
  return CREATE(Command, (^(Object *o) { cmd_init(o, value, destination);}));
}
