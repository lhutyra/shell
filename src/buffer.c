#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buffer_constructor(buffer_t *buffer) {
  // printf("[buffer::constructor]\n");
  buffer->str = NULL;
}

void buffer_destructor(buffer_t *buffer) {
  // printf("[buffer::destructor]\n");
  free(buffer->str);
  buffer->str = NULL;
}

void buffer_read(buffer_t *buffer) {
  // printf("[buffer::read]\n");
  buffer_constructor(buffer);

  size_t size = 0;

  if (getline(&buffer->str, &size, stdin) == -1) {
    printf("exit\n");
    buffer_destructor(buffer);
    exit(EXIT_SUCCESS);
  }

  buffer->str[strlen(buffer->str) - 1] = '\0';
}