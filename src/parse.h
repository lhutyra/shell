#ifndef PARSE_H
#define PARSE_H

#include "buffer.h"
#include "command_table.h"

command_table_t parse(buffer_t buffer, const char * del);

#endif
