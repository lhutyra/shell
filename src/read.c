#include "read.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

buffer_t read() {
    buffer_t buffer;
    buffer_constructor(&buffer);

    size_t size = 0;

    if (getline(&buffer.str, &size, stdin) == -1) {
        printf("exit\n");
        buffer_destructor(&buffer);
        exit(EXIT_SUCCESS);
    }

    buffer.str[strlen(buffer.str) - 1] = '\0';

    return buffer;
}