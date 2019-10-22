#ifndef SHELL_COMMAND_H
#define SHELL_COMMAND_H

#include <stddef.h>

typedef struct command_t {
  char **argv;
  size_t size;
} command_t;

void command_constructor(command_t *command);
void command_destructor(command_t *command);

void command_resize(command_t *command, size_t size);

#endif // SHELL_COMMAND_H
