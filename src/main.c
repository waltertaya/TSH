#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1024

char *builtin[3] = {"echo", "exit", "type"};

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
    else if (strncmp(command, "echo ", 5) == 0) { // echo command
      printf("%s\n", command+5);
    } else if (strncmp(command, "type ", 5) == 0) { // type builtin
      char *token = strtok(command+5, " ");

      while (token != NULL) {
        int found = 0;
        for (int i = 0; i < 3; i++) {
          if (strcmp(token, builtin[i]) == 0) {
            printf("%s is a shell builtin\n", builtin[i]);
            found = 1;
            break;
          }
        }
        if (!found)
          printf("%s: not found\n", command+5);
        
        token = strtok(NULL, " ");
      }
    } else {
      printf("%s: command not found\n", command);
    }
  }

  return 0;
}
