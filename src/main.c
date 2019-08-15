#include "execute.h"
#include "parse.h"
#include "prompt.h"
#include "read.h"

#include <stdlib.h>

int main(int argc, char **argv) {
    buffer_t buffer;
    command_t command;

    while (1) {
        prompt("shell");

        buffer_constructor(&buffer);
        command_constructor(&command);

        buffer = read();

        command = parse(buffer, " \t");

        int status = execute(command);

        command_destructor(&command);
        buffer_destructor(&buffer);

        if (status == 1) break;
    }

    return EXIT_SUCCESS;
}