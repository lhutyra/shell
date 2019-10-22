#include "prompt.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define RED "\033[31;1m"
#define WHITE "\033[37;1m"
#define RESET "\033[0m"

void prompt(const char *prompt) {
  if (isatty(fileno(stdin))) {
    printf(RED "[%s]$ " RESET, prompt);
  }
}
