#include "command.h"

#include <stdio.h>
#include <stdlib.h>

void command_constructor(command_t *command) {
  printf("[command_t::constructor]\n");
  command->argv = NULL;
  command->size = 0;
}

void command_destructor(command_t *command) {
  printf("[command_t::destructor]\n");
  for (size_t i = 0; i < command->size; i++) {
    free(command->argv[i]);
  }
  free(command->argv);
  command->size = 0;
}

void command_resize(command_t *command, size_t size) {
    if (size > command->size) {
        command->argv = realloc(command->argv, size * sizeof(char *));
        if (!command->argv) {
            free(command->argv);
            exit(EXIT_FAILURE);
        }
        printf("[command_t::resize] %zu\n", size);
    }
}