#include "command_table.h"

#include <stdlib.h>

void command_table_constructor(command_table_t * ct) {
    //It's 0 indexed. So the actual number of commands is no_of_commands + 1.
    ct->size= 0;
    ct->input_file = NULL;
    ct->output_file = NULL;
    ct->error_file = NULL;
    //allocating table for one command initally.
    ct->command = (command_t*) malloc(sizeof(command_t));
    if(!ct->command){
        free(ct->command);
        exit(EXIT_FAILURE);
    }

    command_constructor(ct->command);
}

void command_table_destructor(command_table_t * ct) {
    for(size_t i = 0; i <= ct->size; i++){
        command_destructor(&ct->command[i]);
    }

    if(!ct->input_file)
        free(ct->input_file);
    if(!ct->output_file)
        free(ct->output_file);
    if(!ct->error_file)
        free(ct->error_file);
    free(ct->command);
    ct->size = 0;
}