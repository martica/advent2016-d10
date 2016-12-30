#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "linkedlist.h"
#include "robot.h"
#include "wrappedarray.h"
#include "wrappedstring.h"

LinkedList *read_file(char *filename) {
  FILE *input_file_handle = fopen(filename, "r");

  LinkedList *lines = ll_create();

  char line[256];
  while (fgets(line, 255, input_file_handle) != NULL) {
    String *string = String_create(line);
    lines->add(string);
  }
  fclose(input_file_handle);

  return lines;
}

void skip_words(int count) {
  for (int i = 0; i < count; i++) {
    strtok(NULL, " ");
  }
}

struct dest_t get_destination() {
  skip_words(3);
  return (struct dest_t){.is_bot = strcmp("bot", strtok(NULL, " ")) == 0,
                         .index = (unsigned int) atoi(strtok(NULL, " "))};
}

void parse_lines(LinkedList *lines, Array *robots, LinkedList *command_list) {
  while (!lines->is_empty()) {
    String *line = lines->pop();

    if (strcmp("bot", strtok(line->get_value(), " ")) == 0) {
      unsigned int bot = (unsigned int) atoi(strtok(NULL, " "));
      Robot *robot = rb_create();
      robots->set_item(bot, robot);
      RELEASE(robot);
      robot->set_destinations(get_destination(), get_destination());
    } else {
      int value = atoi(strtok(NULL, " "));
      skip_words(3);
      unsigned int bot = (unsigned int) atoi(strtok(NULL, " "));
      command_list->add(cmd_create(value, bot));
    }
    RELEASE(line);
  }
}

void apply_commands(Array *robots, LinkedList *commands, int outputs[]) {
  while (!commands->is_empty()) {
    struct cmd_t *cmd = commands->pop();
    printf("cmd %d -> %d\n", cmd->value, cmd->destination);

    Robot *robot = robots->get_item(cmd->destination);
    robot->add(cmd->value);
    struct rb_state robot_state = robot->state();
    if (robot_state.is_complete) {
      for (int i = 0; i < 2; i++) {
        struct rb_output output = robot_state.outputs[i];
        if (output.destination.is_bot) {
          commands->add(cmd_create(output.value, output.destination.index));
        } else {
          outputs[output.destination.index] = output.value;
        }
      }
    }
    RELEASE(cmd);
  }
}

int main(int argc, char **argv) {
  int outputs[21];

  LinkedList *lines = read_file("d10.txt");

  Array *robots = Array_create();
  LinkedList *commands = ll_create();

  parse_lines(lines, robots, commands);
  RELEASE(lines);

  apply_commands(robots, commands, outputs);

  RELEASE(robots);
  RELEASE(commands);

  for (int j = 0; j < 21; j++) {
    printf("%d: %d\n", j, outputs[j]);
  }

  printf("%d\n", outputs[0] * outputs[1] * outputs[2]);

  return 0;
}
