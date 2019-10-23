#include "prompt.h"

#include <sys/param.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define RED "\033[31;1m"
#define WHITE "\033[37;1m"
#define RESET "\033[0m"

#define USERNAME_MAX 128
#define HOSTNAME_MAX 128

void session_username(char *buffer) {
  getlogin_r(buffer, USERNAME_MAX);
}

void session_hostname(char *buffer) {
  gethostname(buffer, HOSTNAME_MAX);
}

void prompt() {
  char buf1[USERNAME_MAX];
  char buf2[HOSTNAME_MAX];
  char buf3[MAXPATHLEN];

  session_username(buf1);
  session_hostname(buf2);

  getcwd(buf3, sizeof(buf3));

  char *dir;
  char *token = strtok(buf3, "/");
  while (token != NULL) {
    dir = token;
    token = strtok(NULL, "/");
  }

  if (isatty(fileno(stdin))) {
    printf(RED "[%s@%s" RESET " " WHITE "%s" RED "]$" RESET " ", buf1, buf2, dir);
  }
}