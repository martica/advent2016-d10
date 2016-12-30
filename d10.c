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

int main(int argc, char **argv) {
  int outputs[21];

  LinkedList *lines = read_file("d10.txt");

  Array *robots = Array_create(256);
  for (unsigned int i=0; i<256; i++) {
    Robot *robot = rb_create();
    robots->set_item(i, (Object *) robot);
    RELEASE(robot);
  }

  LinkedList *command_list = ll_create();


  while (!lines->is_empty()) {
    String *line = lines->pop();

    if (strcmp("bot", strtok(line->get_value(), " ")) == 0) {
      unsigned int bot = (unsigned int) atoi(strtok(NULL, " "));
      ((Robot *)robots->get_item(bot))->set_destinations(get_destination(), get_destination());
    } else {
      int value = atoi(strtok(NULL, " "));
      skip_words(3);
      unsigned int bot = (unsigned int) atoi(strtok(NULL, " "));
      command_list->add(cmd_create(value, bot));
    }
    RELEASE(line);
  }
  RELEASE(lines);

  while (!command_list->is_empty()) {
    struct cmd_t *cmd = command_list->pop();
    printf("cmd %d -> %d\n", cmd->value, cmd->destination);

    Robot *robot = (Robot *)robots->get_item(cmd->destination);
    robot->add(cmd->value);
    struct rb_state robot_state = robot->state();
    if (robot_state.is_complete) {
      for (int i = 0; i < 2; i++) {
        struct rb_output output = robot_state.outputs[i];
        if (output.destination.is_bot) {
          command_list->add(cmd_create(output.value, output.destination.index));
        } else {
          outputs[output.destination.index] = output.value;
        }
      }
    }
    RELEASE(cmd);
  }

  RELEASE(robots);
  RELEASE(command_list);

  for (int j = 0; j < 21; j++) {
    printf("%d: %d\n", j, outputs[j]);
  }

  printf("%d\n", outputs[0] * outputs[1] * outputs[2]);

  return 0;
}
