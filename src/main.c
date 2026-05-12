#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1024

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  printf("$ ");
  char command[MAXLINE];
  fgets(command, sizeof(command), stdin);
  command[strcspn(command, "\n")] = '\0';
  printf("%s: command not found\n", command);

  return 0;
}
