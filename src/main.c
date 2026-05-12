#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1024

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  while (1) {
    printf("$ ");
    char command[MAXLINE];
    fgets(command, sizeof(command), stdin);
    command[strlen(command) - 1] = '\0';

    // exit command
    if (strcmp(command, "exit") == 0)
      break;
    
    // echo command
    if (strncmp(command, "echo ", 5) == 0) {
      printf("%s\n", command+5);
    } else {
      printf("%s: command not found\n", command);
    }
  }

  return 0;
}
