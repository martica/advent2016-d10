#include <Block.h>
#include <stdlib.h>

#include "command.h"
#include "object.h"

void cmd_init(Object *object, int value, int destination) {
  Command *command = (Command *)object;

  *command = (Command) {
      .value = value,
      .destination = destination
  };
}

Command *cmd_create(int value, int destination) {
  return CREATE(Command, (^(Object *o) { cmd_init(o, value, destination);}));
}
