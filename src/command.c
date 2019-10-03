#include "command.h"

#include <stdlib.h>

void command_constructor(command_t * command_table) {
    
    //It's 0 indexed. So the actual number of commands is no_of_commands + 1.
    command_table->no_of_commands = 0;

    //allocating table for one command initally.
    command_table->cmd = (command*) malloc(sizeof(command)); 
    if(!command_table->cmd){
        free(command_table->cmd);
        exit(EXIT_FAILURE);
    }
    command_table->cmd->argv = NULL;
    command_table->cmd->size = 0;
}

void command_destructor(command_t * command_table) {
    for(size_t i = 0; i <= command_table->no_of_commands; i++){
        for (size_t j = 0; j < command_table->cmd[i].size; j++) {
            free(command_table->cmd[i].argv[j]);
        }
        free(command_table->cmd[i].argv);
        command_table->cmd[i].size = 0;
    }
    free(command_table->cmd);
}
