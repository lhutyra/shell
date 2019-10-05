#include "parse.h"

#include <stdlib.h>
#include <string.h>

command_table_t parse(buffer_t buffer, const char * del) {
    command_table_t command_table;
    command_table_constructor(&command_table);

    size_t i;
    char * str, * saveptr;
    //To keep track of number of commands.
    //As it's 0 indexed. command_index = 0, indicates one command.
    size_t command_index = 0; 

    for (i = 0, str = buffer.str; ; ++i, str = NULL) {
        char * token = strtok_r(str, del, &saveptr);
        if (!token) break;
        
        //Checking for PIPE('|'), If pipe, allocating space for the new command.
        if(*token == '|'){
            
            //Adding NULL to the end of last comment.
            command_table.command[command_index].argv = realloc(command_table.command[command_index].argv, (command_table.command[command_index].size + 1) * sizeof(char *));
            if (!command_table.command[command_index].argv) {
                free(command_table.command[command_index].argv);
                exit(EXIT_FAILURE);
            }
            if (command_table.command[command_index].size != 0) {
                command_table.command[command_index].argv[command_table.command[command_index].size] = NULL;
            }

            command_table.size += 1;
            command_index += 1;
            command_table.command = realloc(command_table.command, sizeof(command_t)*(command_table.size+1));
            if(!command_table.command){
                command_destructor(command_table.command);
                exit(EXIT_FAILURE);
            }
            
            command_constructor(&command_table.command[command_index]);
            //Reseting i to -1 for the next command.
            i = -1;
            continue;
        } 
        
        command_table.command[command_index].size++;
        if (i == 0) {
            command_table.command[command_index].argv = malloc(sizeof(char *));
            if (!command_table.command[command_index].argv) {
                free(command_table.command[command_index].argv);
                exit(EXIT_FAILURE);
            }
        } else {
            command_table.command[command_index].argv = realloc(command_table.command[command_index].argv, (command_table.command[command_index].size + 1) * sizeof(char *));
            if (!command_table.command[command_index].argv) {
                free(command_table.command[command_index].argv);
                exit(EXIT_FAILURE);
            }
        }
        command_table.command[command_index].argv[i] = malloc((strlen(token) + 1) * sizeof(char));
        if (!command_table.command[command_index].argv) {
            free(command_table.command[command_index].argv);
            exit(EXIT_FAILURE);
        }
        memset(command_table.command[command_index].argv[i], 0, strlen(token) + 1);
        strcpy((char *) command_table.command[command_index].argv[i], token);
    }

    command_table.command[command_index].argv = realloc(command_table.command[command_index].argv, (command_table.command[command_index].size + 1) * sizeof(char *));
    if (!command_table.command[command_index].argv) {
        free(command_table.command[command_index].argv);
        exit(EXIT_FAILURE);
    }
    if (command_table.command[command_index].size != 0) {
        command_table.command[command_index].argv[command_table.command[command_index].size] = NULL;
    }
     
    return command_table;
}
