#ifndef PARSE_H
#define PARSE_H

#include "buffer.h"
#include "command.h"

command_t parse(buffer_t buffer, const char * del);

#endif