#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>

typedef struct buffer_t {
    char * str;
} buffer_t;

void buffer_constructor(buffer_t * buffer);

void buffer_destructor(buffer_t * buffer);

#endif