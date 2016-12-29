#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "linkedlist.h"
#include "robot.h"
#include "destructor.h"

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
  for(int i=0; i<count; i++) {
    strtok(NULL, " ");
  }
}

void get_destination(struct dest_t *destination) {
  skip_words(3);
  destination->is_bot = strcmp("bot", strtok(NULL, " ")) == 0;
  destination->index = atoi(strtok(NULL, " "));
}

int main(int argc, char **argv) {
  int size = 0;
  char **lines = read_file("d10.txt", &size);

  struct rb_t *robots = rb_create(256);
  int outputs[21];
  struct ll_t *command_list = ll_create();

  for (int i = 0; i < size; i++) {
    if (strcmp("bot", strtok(lines[i], " ")) == 0) {
      int bot = atoi(strtok(NULL, " "));
      get_destination(&robots[bot].low_destination);
      get_destination(&robots[bot].high_destination);
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

    struct rb_t *robot = &robots[cmd->destination];
    robot->add(cmd->value);
    if (robot->is_complete()) {
      if (robot->high_destination.is_bot) {
        command_list->add(
               cmd_create(robot->high(), robot->high_destination.index));
      } else {
        outputs[robot->high_destination.index] = robot->high();
      }
      if (robot->low_destination.is_bot) {
        command_list->add(
               cmd_create(robot->low(), robot->low_destination.index));
      } else {
        outputs[robot->low_destination.index] = robot->low();
      }
    }
    DESTROY(cmd);
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
