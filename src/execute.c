#include "execute.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int execute(const command_t command) {
    if (command.size > 0) {
        if (!strcmp(command.argv[0], "exit")) {
            return 1;
        } else if (!strcmp(command.argv[0], "cd")) {
            if (chdir(command.argv[1]) == -1) {
                printf("shell: %s: %s: No such file or directory\n", command.argv[0], command.argv[1]);
	    }
            return 0;
        } else {
            switch(fork()) {
            case -1:
                exit(EXIT_FAILURE);
            case  0:
                if (execvp(command.argv[0], command.argv) == -1) {
                    printf("shell: %s: command not found\n", command.argv[0]);
		    exit(EXIT_FAILURE);
                }
            default:
                while (wait(NULL) > 0);
            }
        }
    }
    return 0;
}
