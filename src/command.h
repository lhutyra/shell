#ifndef COMMAND_H
#define COMMAND_H

#include <stddef.h>

//Single Command.
typedef struct command_t {
    char ** argv;
    size_t size;
} command_t;

//Command table.
typedef struct command_table_t {
    int size;
    char* input_file;
    char* output_file;
    char* error_file;
    struct command_t *command;
} command_table_t;

void command_constructor(command_t * command);
void command_table_constructor(command_table_t * command_table);
void command_destructor(command_t * command);
void command_table_destructor(command_table_t * command_table);

#endif
