#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>

void buffer_constructor(buffer_t *buffer) {
  // printf("[buffer::constructor]\n");
  buffer->str = NULL;
}

void buffer_destructor(buffer_t *buffer) {
  // printf("[buffer::destructor]\n");
  free(buffer->str);
  buffer->str = NULL;
}