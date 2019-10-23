#include "command_table.h"

#include <stdio.h>
#include <stdlib.h>

void command_table_constructor(command_table_t *ct) {
  // printf("[command_table_t::constructor]\n");
  ct->input_file = NULL;
  ct->output_file = NULL;
  ct->error_file = NULL;
  ct->command = NULL;
  // It's 0 indexed. So the actual number of commands is no_of_commands + 1.
  ct->size = 0;
}

void command_table_destructor(command_table_t *ct) {
  // printf("[command_table_t::destructor]\n");
  if (!ct->input_file)
    free(ct->input_file);
  if (!ct->output_file)
    free(ct->output_file);
  if (!ct->error_file)
    free(ct->error_file);

  for (size_t i = 0; i <= ct->size; i++) {
    command_destructor(&ct->command[i]);
  }
  free(ct->command);
  ct->size = 0;
}

void command_table_resize(command_table_t *ct, size_t size) {
  // printf("[command_table_t::resize]\n");
  if (size > ct->size) {
    ct->command = realloc(ct->command, size * sizeof(command_t));
    if (!ct->command) {
      command_table_destructor(ct);
      exit(EXIT_FAILURE);
    }
  }
}