#include "parse.h"

#include <stdlib.h>
#include <string.h>

command_t parse(buffer_t buffer, const char * del) {
    command_t command;
    command_constructor(&command);

    size_t i;
    char * str, * saveptr;

    for (i = 0, str = buffer.str; ; ++i, str = NULL) {
        char * token = strtok_r(str, del, &saveptr);
        if (!token) break;
        command.size++;
        if (i == 0) {
            command.argv = malloc(sizeof(char *));
            if (!command.argv) {
                free(command.argv);
                exit(EXIT_FAILURE);
            }
        } else {
            command.argv = realloc(command.argv, (command.size + 1) * sizeof(char *));
            if (!command.argv) {
                free(command.argv);
                exit(EXIT_FAILURE);
            }
        }
        command.argv[i] = malloc((strlen(token) + 1) * sizeof(char));
        if (!command.argv) {
            free(command.argv);
            exit(EXIT_FAILURE);
        }
        memset(command.argv[i], 0, strlen(token) + 1);
        strcpy((char *) command.argv[i], token);
    }

    command.argv = realloc(command.argv, (command.size + 1) * sizeof(char *));
    if (!command.argv) {
        free(command.argv);
        exit(EXIT_FAILURE);
    }
    if (command.size != 0) {
        command.argv[command.size] = NULL;
    }

    return command;
}