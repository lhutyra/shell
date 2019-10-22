#include "command.h"

#include <stdlib.h>

void command_constructor(command_t *command) {
  command->argv = NULL;
  command->size = 0;
}

void command_destructor(command_t *command) {
  for (size_t i = 0; i < command->size; i++) {
    free(command->argv[i]);
  }
  free(command->argv);
  command->size = 0;
}

void command_resize(command_t *command, size_t size) {
  // TODO
}