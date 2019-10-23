#include "parse.h"

#include <stdlib.h>
#include <string.h>

void safe_dup(char *file, char *token) {
  file = strdup(token);
  if (!file) {
    free(file);
    exit(EXIT_FAILURE);
  }
}

command_table_t parse(buffer_t buffer, const char *del) {
  command_table_t ct;
  command_table_constructor(&ct);
  
  ct.command = (command_t *)malloc(sizeof(command_t));
  if (!ct.command) {
    free(ct.command);
    exit(EXIT_FAILURE);
  }

  command_constructor(ct.command);
  
  size_t i;
  char *str, *saveptr;

  size_t ci = 0;

  for (i = 0, str = buffer.str;; ++i, str = NULL) {
    char *token = strtok_r(str, del, &saveptr);
    if (!token)
      break;

    if (*token == '|') {
      command_resize(&ct.command[ci], ct.command[ci].size + 1);
      if (ct.command[ci].size != 0) {
        ct.command[ci].argv[ct.command[ci].size] = NULL;
      }

      ct.size += 1;
      ci += 1;
      command_table_resize(&ct, ct.size + 1);

      command_constructor(&ct.command[ci]);
      // Reseting i to -1 for the next command.
      i = -1;
      continue;
    }

    if (*token == '>') {
      token = strtok_r(str, del, &saveptr);
      safe_dup(ct.output_file, token);
      continue;
    }

    if (*token == '<') {
      token = strtok_r(str, del, &saveptr);
      safe_dup(ct.input_file, token);
      continue;
    }

    if (strcmp(token, "2>") == 0) {
      token = strtok_r(str, del, &saveptr);
      safe_dup(ct.error_file, token);
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

  command_resize(&ct.command[ci], ct.command[ci].size + 1);
  if (ct.command[ci].size != 0) {
    ct.command[ci].argv[ct.command[ci].size] = NULL;
  }

  return ct;
}