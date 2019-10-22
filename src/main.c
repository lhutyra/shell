#include "execute.h"
#include "parse.h"
//#include "prompt.h"
#include "read.h"

#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    buffer_t buffer;
    command_table_t ct;

    while (true) {
//        prompt("shell");

        buffer = read();
        ct = parse(buffer, " \t");

        int status = execute(ct);

        command_table_destructor(&ct);
        buffer_destructor(&buffer);

        if (status == 1) break;
    }

    return EXIT_SUCCESS;
}

