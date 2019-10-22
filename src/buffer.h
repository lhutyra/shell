#ifndef SHELL_BUFFER_H
#define SHELL_BUFFER_H

typedef struct buffer_t {
    char * str;
} buffer_t;

void buffer_constructor(buffer_t * buffer);
void buffer_destructor(buffer_t * buffer);

#endif //SHELL_BUFFER_H