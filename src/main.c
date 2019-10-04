#include "execute.h"
#include "parse.h"
#include "prompt.h"
#include "read.h"

#include <stdlib.h>

int main(int argc, char **argv) {
    buffer_t buffer;
    //This is basically a Command Table now.
    command_table_t command_table;

    while (1) {
        prompt("shell");

        buffer_constructor(&buffer);
        //command_table_constructor(&command_table);

        buffer = read();

        command_table = parse(buffer, " \t");
        int status = execute(command_table);

        command_table_destructor(&command_table);
        buffer_destructor(&buffer);

        if (status == 1) break;
    }

    return EXIT_SUCCESS;
}

