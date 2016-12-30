#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "object.h"
#include "linkedlist.h"
#include "robot.h"

char **read_file(char *filename, int *out_size) {
  FILE *input_file_handle = fopen(filename, "r");

  size_t size = 40;
  char **lines = calloc(sizeof(char *), size);

  char line[256];
  int offset = 0;
  while (fgets(line, 255, input_file_handle) != NULL) {
    lines[offset] = strndup(line, 255);
    offset++;
    if (offset == size) {
      size *= 2;
      lines = realloc(lines, size * sizeof(char *));
    }
  }
  fclose(input_file_handle);

  if (out_size) *out_size = offset;
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
                         .index = atoi(strtok(NULL, " "))};
}

int main(int argc, char **argv) {
  int size = 0;
  char **lines = read_file("d10.txt", &size);

  Robot **robots = calloc(256, sizeof(Robot *));
  for (int i=0; i<256; i++) {
    robots[i] = rb_create();
  }
  int outputs[21];
  LinkedList *command_list = ll_create();

  for (int i = 0; i < size; i++) {
    if (strcmp("bot", strtok(lines[i], " ")) == 0) {
      int bot = atoi(strtok(NULL, " "));
      robots[bot]->set_destinations(get_destination(), get_destination());
    } else {
      int value = atoi(strtok(NULL, " "));
      skip_words(3);
      int bot = atoi(strtok(NULL, " "));
      command_list->add(cmd_create(value, bot));
    }
  }

  while (!command_list->is_empty()) {
    struct cmd_t *cmd = command_list->pop();
    printf("cmd %d -> %d\n", cmd->value, cmd->destination);

    Robot *robot = robots[cmd->destination];
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
    DESTROY(cmd);
  }

  for (int i=0; i<256; i++) {
    DESTROY(robots[i]);
  }
  free(robots);
  DESTROY(command_list);
  for (int i = 0; i < size; i++) {
    free(lines[i]);
  }
  free(lines);

  for (int j = 0; j < 21; j++) {
    printf("%d: %d\n", j, outputs[j]);
  }

  printf("%d\n", outputs[0] * outputs[1] * outputs[2]);

  return 0;
}
