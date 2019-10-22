#include "execute.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int execute(const command_table_t ct) {
    //Index to iterate through the command table.
    size_t i;
    
    //Storing the STDIN,STDOUT and STDERR file descriptors, so it can be reverted back
    //after the pipe command.
    int temp_in = dup(0);
    int temp_out = dup(1);
    int temp_err = dup(3);
    //Array for pipe FDs (File descriptors).
    int pipefd[2];
    
    //Initializing it with STDIN and STDOUT.
    //So for one command, or for the first command in a pipe sequence,
    //pipefd[0] will be STDIN.
    //and pipefd[1] will be STDOUT, in case of one command.
    //otherwise it will be the output in case of piped commands.
    pipefd[0] = dup(0);
    pipefd[1] = dup(1);
   
    //For the the input/output/err files.
    int fdin;
    int fdout;
    int fderr;

    //Checking if input is redirected.
    //If not detected, setting it to default.
    if(ct.input_file){
        fdin = open(ct.input_file, O_RDONLY);
        if(fdin == -1){
            exit(EXIT_FAILURE);
        }
    }
    else
        fdin = dup(temp_in);
    
    //Iterating through to command table.
    for(i = 0; i <= ct.size; i++ ){
        if (ct.command[i].size > 0) {
            if (!strcmp(ct.command[i].argv[0], "exit")) {
                return 1;
            } else if (!strcmp(ct.command[i].argv[0], "cd")) {
                if (chdir(ct.command[i].argv[1]) == -1) {
                    printf("shell: %s: %s: No such file or directory\n", ct.command[i].argv[0], ct.command[i].argv[1]);
            }
                return 0;
            } else {
                //Setting the read end of the pipe as the 
                //default for the process.
                //In case of the first command/only command this will be STDOUT.
                //In the later iteration, this will be the read end of the pipe.
                dup2(fdin, 0);
                close(fdin);

                //If it's the last command in the table, 
                //then the write end of the pipe is set to STDOUT.
                //And the STDERR is set.
                if(i == ct.size) {
                    if(ct.output_file || ct.error_file){
                        //2>&1
                        if((ct.output_file && ct.error_file) && strcmp(ct.output_file, ct.error_file) == 0){
                            fdout = open(ct.output_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
                            fderr = fdout;
                        }
                        //only output_file('>') or only error_file('2>')
                        else {
                            if(ct.output_file)
                                fdout = open(ct.output_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
                            if(ct.error_file)
                                fderr = open(ct.error_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
                        }
                    }
                    else {
                        //Both to default.
                        fdout = dup(temp_out);
                        fderr = dup(temp_out);
                    }
                }
                else{
                    //Creating the pipe.
                    if(pipe(pipefd) == -1){
                        perror("pipe");
                        exit(EXIT_FAILURE);
                    }
                    fdin = pipefd[0];
                    fdout = pipefd[1];
                }
                
                //Redirecting the output to pipe's write end.
                dup2(fdout, 1);
                //Redirecting the err.
                dup2(fderr, 2);
                close(fdout);
                close(fderr);
                //The child process inherits the open file descriptors, 
                //which allows this to work.
                switch(fork()) {
                case -1:
                    exit(EXIT_FAILURE);
                case  0:
                    if (execvp(ct.command[i].argv[0], ct.command[i].argv) == -1) {
                        printf("shell: %s: command not found\n", ct.command[i].argv[0]);
                exit(EXIT_FAILURE);
                    }
                default:
                    while (wait(NULL) > 0);
                }
            }     
        }
    }

    //Reverting back to STDIN, STDOUT and STDERR after all the commands have been executed.
    dup2(temp_in, 0);
    dup2(temp_out, 1);
    dup2(temp_err, 2);
    close(temp_in);
    close(temp_out);
    close(temp_err);
    return 0;
}
