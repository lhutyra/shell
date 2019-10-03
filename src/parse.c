#include "parse.h"

#include <stdlib.h>
#include <string.h>

command_t parse(buffer_t buffer, const char * del) {
    command_t command_table;
    command_constructor(&command_table);

    size_t i;
    char * str, * saveptr;
    //To keep track of number of commands.
    //As it's 0 indexed. cmd_index = 0, indicates 1 command.
    size_t cmd_index = 0; 

    for (i = 0, str = buffer.str; ; ++i, str = NULL) {
        char * token = strtok_r(str, del, &saveptr);
        if (!token) 
            break;
        
        //Checking for PIPE('|'), If pipe, allocating space for the new command.
        if(*token == '|'){
            command_table.no_of_commands += 1;
            cmd_index += 1;
            command_table.cmd = realloc(command_table.cmd, sizeof(command_t)*(command_table.no_of_commands+1));
            if(!command_table.cmd){
                free(command_table.cmd);
                exit(EXIT_FAILURE);
            }
            command_table.cmd[cmd_index].argv = NULL;
            command_table.cmd[cmd_index].size = 0;
            //Reseting i to -1 for the next command.
            i = -1;
            continue;
        } 
        
        //printf("Token: %s\n", token); 
        command_table.cmd[cmd_index].size++;
        if (i == 0) {
            command_table.cmd[cmd_index].argv = malloc(sizeof(char *));
            if (!command_table.cmd[cmd_index].argv) {
                free(command_table.cmd[cmd_index].argv);
                exit(EXIT_FAILURE);
            }
        } else {
            command_table.cmd[cmd_index].argv = realloc(command_table.cmd[cmd_index].argv, (command_table.cmd[cmd_index].size + 1) * sizeof(char *));
            if (!command_table.cmd[cmd_index].argv) {
                free(command_table.cmd[cmd_index].argv);
                exit(EXIT_FAILURE);
            }
        }
        command_table.cmd[cmd_index].argv[i] = malloc((strlen(token) + 1) * sizeof(char));
        if (!command_table.cmd[cmd_index].argv) {
            free(command_table.cmd[cmd_index].argv);
            exit(EXIT_FAILURE);
        }
        memset(command_table.cmd[cmd_index].argv[i], 0, strlen(token) + 1);
        strcpy((char *) command_table.cmd[cmd_index].argv[i], token);
    }

    command_table.cmd[cmd_index].argv = realloc(command_table.cmd[cmd_index].argv, (command_table.cmd[cmd_index].size + 1) * sizeof(char *));
    if (!command_table.cmd[cmd_index].argv) {
        free(command_table.cmd[cmd_index].argv);
        exit(EXIT_FAILURE);
    }
    if (command_table.cmd[cmd_index].size != 0) {
        command_table.cmd[cmd_index].argv[command_table.cmd[cmd_index].size] = NULL;
    }
    
    return command_table;
}
