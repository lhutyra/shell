#ifndef SHELL_PARSE_H
#define SHELL_PARSE_H

#include "buffer.h"
#include "command_table.h"

command_table_t parse(buffer_t buffer, const char *del);

#endif // SHELL_PARSE_H
