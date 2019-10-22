#ifndef SHELL_COMMAND_TABLE_H
#define SHELL_COMMAND_TABLE_H

#include "command.h"

typedef struct command_table_t {
    int size;
    char* input_file;
    char* output_file;
    char* error_file;
    struct command_t *command;
} command_table_t;

void command_table_constructor(command_table_t * ct);
void command_table_destructor(command_table_t * ct);

#endif //SHELL_COMMAND_TABLE_H