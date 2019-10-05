#include "command.h"

#include <stdlib.h>

void command_table_constructor(command_table_t * command_table) {
    
    //It's 0 indexed. So the actual number of commands is no_of_commands + 1.
    command_table->size= 0;

    //allocating table for one command initally.
    command_table->command = (command_t*) malloc(sizeof(command_t)); 
    if(!command_table->command){
        free(command_table->command);
        exit(EXIT_FAILURE);
    }
    
    command_constructor(command_table->command);
}

void command_constructor(command_t * command){
    command->argv = NULL;
    command->size = 0;
}

void command_table_destructor(command_table_t * command_table) {
    for(size_t i = 0; i <= command_table->size; i++){
        command_destructor(&command_table->command[i]);
    }
    free(command_table->command);
    command_table->size = 0;
}

void command_destructor(command_t * command){
    for(size_t i = 0; i < command->size; i++){
        free(command->argv[i]);
    }
    free(command->argv);
    command->size = 0;
}
