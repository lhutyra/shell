#include "parse.h"

#include <stdlib.h>
#include <string.h>

command_table_t parse(buffer_t buffer, const char *del) {
  command_table_t ct;
  command_table_constructor(&ct);

  size_t i;
  char *str, *saveptr;
  // To keep track of number of commands.
  // As it's 0 indexed. ci = 0, indicates one command.
  size_t ci = 0;

  for (i = 0, str = buffer.str;; ++i, str = NULL) {
    char *token = strtok_r(str, del, &saveptr);
    if (!token)
      break;

    // Checking for PIPE('|'), If pipe, allocating space for the new command.
    if (*token == '|') {
      command_resize(&ct.command[ci], ct.command[ci].size + 1);
      if (ct.command[ci].size != 0) {
        ct.command[ci].argv[ct.command[ci].size] = NULL;
      }

      ct.size += 1;
      ci += 1;
      ct.command = realloc(ct.command, sizeof(command_t) * (ct.size + 1));
      if (!ct.command) {
        command_destructor(ct.command);
        exit(EXIT_FAILURE);
      }

      command_constructor(&ct.command[ci]);
      // Reseting i to -1 for the next command.
      i = -1;
      continue;
    }

    if (*token == '>') {
      token = strtok_r(str, del, &saveptr);
      ct.output_file = strdup(token);
      if (!ct.output_file) {
        free(ct.output_file);
        exit(EXIT_FAILURE);
      }
      continue;
    }

    if (*token == '<') {
      token = strtok_r(str, del, &saveptr);
      ct.input_file = strdup(token);
      if (!ct.input_file) {
        free(ct.input_file);
        exit(EXIT_FAILURE);
      }
      continue;
    }

    if (strcmp(token, "2>") == 0) {
      token = strtok_r(str, del, &saveptr);
      ct.error_file = strdup(token);
      if (!ct.error_file) {
        free(ct.error_file);
        exit(EXIT_FAILURE);
      }
      continue;
    }

    if (strcmp(token, "2>&1") == 0) {
      ct.error_file = ct.output_file;
      continue;
    }

    ct.command[ci].size++;
    if (i == 0) {
      ct.command[ci].argv = malloc(sizeof(char *));
      if (!ct.command[ci].argv) {
        free(ct.command[ci].argv);
        exit(EXIT_FAILURE);
      }
    } else {
      command_resize(&ct.command[ci], ct.command[ci].size + 1);
    }
    ct.command[ci].argv[i] = malloc((strlen(token) + 1) * sizeof(char));
    if (!ct.command[ci].argv) {
      free(ct.command[ci].argv);
      exit(EXIT_FAILURE);
    }
    memset(ct.command[ci].argv[i], 0, strlen(token) + 1);
    strcpy((char *)ct.command[ci].argv[i], token);
  }

  return ct;
}
