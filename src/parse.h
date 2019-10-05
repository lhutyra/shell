#ifndef PARSE_H
#define PARSE_H

#include "buffer.h"
#include "command.h"

//Returns a pointer to an array of commands.
command_table_t parse(buffer_t buffer, const char * del);

#endif
