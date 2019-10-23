#include "prompt.h"

#define __USE_POSIX

#include <limits.h>
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define RED "\033[31;1m"
#define WHITE "\033[37;1m"
#define RESET "\033[0m"

#define USERNAME_SIZE 128
#define HOSTNAME_SIZE 128

void prompt(const char *prompt) {
  char buf1[USERNAME_SIZE];
  char buf2[HOSTNAME_SIZE];
  char buf3[PATH_MAX];

  getlogin_r(buf1, USERNAME_SIZE);
  gethostname(buf2, HOSTNAME_SIZE);
  getcwd(buf3, sizeof(buf3));

  char *del = "/";
  char *dir;
  char *token = strtok(buf3, del);
  while (token != NULL) {
    dir = token;
    token = strtok(NULL, del);
  }

  if (isatty(fileno(stdin))) {
    printf(RED "[%s@%s" RESET " " WHITE "%s" RED "]$ " RESET, buf1, buf2, dir);
  }
}