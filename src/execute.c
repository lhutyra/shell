#include "execute.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int execute(const command_table_t command_table) {
    //Index to iterate through the command table.
    size_t i;
    
    //Storing the STDIN and STDOUT file descriptors, so it can be reverted back
    //after the pipe command.
    int temp_in = dup(0);
    int temp_out = dup(1);

    //Array for pipe FDs (File descriptors).
    int pipefd[2];
    
    //Initializing it with STDIN and STDOUT.
    //So for one command, or for the first command in a pipe sequence,
    //pipefd[0] will be STDIN.
    //and pipefd[1] will be STDOUT, in case of one command.
    //otherwise it will be the output in case of piped commands.
    pipefd[0] = dup(0);
    pipefd[1] = dup(1);
    
    //Iterating through to command table.
    for(i = 0; i <= command_table.size; i++ ){
        if (command_table.command[i].size > 0) {
            if (!strcmp(command_table.command[i].argv[0], "exit")) {
                return 1;
            } else if (!strcmp(command_table.command[i].argv[0], "cd")) {
                if (chdir(command_table.command[i].argv[1]) == -1) {
                    printf("shell: %s: %s: No such file or directory\n", command_table.command[i].argv[0], command_table.command[i].argv[1]);
            }
                return 0;
            } else {
                //Setting the read end of the pipe as the 
                //default for the process.
                //In case of the first command/only command this will be STDOUT.
                //In the later iteration, this will be the read end of the pipe.
                dup2(pipefd[0], 0);
                close(pipefd[0]);

                //If it's the last command in the table, 
                //then the write end of the pipe is set to STDOUT.
                if(i == command_table.size){
                    pipefd[1] = dup(temp_out);
                }
                else{
                    //Creating the pipe.
                    if(pipe(pipefd) == -1){
                        perror("pipe");
                        exit(EXIT_FAILURE);
                    }
                }
                
                //Redirecting the output to pipe's write end.
                dup2(pipefd[1], 1);
                close(pipefd[1]);
                //The child process inherits the open file descriptors, 
                //which allows this to work.
                switch(fork()) {
                case -1:
                    exit(EXIT_FAILURE);
                case  0:
                    if (execvp(command_table.command[i].argv[0], command_table.command[i].argv) == -1) {
                        printf("shell: %s: command not found\n", command_table.command[i].argv[0]);
                exit(EXIT_FAILURE);
                    }
                default:
                    while (wait(NULL) > 0);
                }
            }     
        }
    }

    //Reverting back to STDIN and STDOUT, after all the commands have been executed.
    dup2(temp_out, 1);
    dup2(temp_in, 0);
    close(temp_out);
    close(temp_in);
    return 0;
}
