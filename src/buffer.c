#include "buffer.h"

#include <stdlib.h>

void buffer_constructor(buffer_t * buffer) {
    buffer->str = NULL;
}

void buffer_destructor(buffer_t * buffer) {
    free(buffer->str);
    buffer->str = NULL;
}