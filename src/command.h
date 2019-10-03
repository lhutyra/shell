#ifndef COMMAND_H
#define COMMAND_H

#include <stddef.h>

//Single Command.
typedef struct command {
    char ** argv;
    size_t size;
} command;

//Command table.
typedef struct command_t{
    int no_of_commands;
    struct command *cmd;
}command_t;

void command_constructor();
void command_destructor(command_t * command_table);

#endif
