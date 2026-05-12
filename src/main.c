#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXLINE 256

char *builtin[] = {"echo", "exit", "type"};

void search_exec_commands(const char *command, char **buf);

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  while (1) {
    printf("$ ");
    char command[MAXLINE];
    fgets(command, sizeof(command), stdin);
    size_t len = strlen(command);
    if (len > 0 && command[len - 1] == '\n')
      command[strlen(command) - 1] = '\0';

    // exit command
    if (strcmp(command, "exit") == 0)
      break;
    else if (strncmp(command, "echo ", 5) == 0) { // echo command
      printf("%s\n", command+5);
    } else if (strncmp(command, "type ", 5) == 0) { // type builtin
      char *args = command + 5;
      char *token = strtok(args, " ");

      while (token != NULL) {
        int found = 0;
        for (int i = 0; i < (sizeof(builtin) / sizeof(builtin[0])); i++) {
          if (strcmp(token, builtin[i]) == 0) {
            printf("%s is a shell builtin\n", builtin[i]);
            found = 1;
            break;
          }
        }

        char *fullpath = NULL;
        search_exec_commands(token, &fullpath);
        if (fullpath != NULL) {
          printf("%s is %s\n", token, fullpath);
          free(fullpath);
          found = 1;
          break;
        }

        if (!found && token != NULL && strlen(token) > 0) {
          printf("%s: not ~ found\n", token);
        }
        
        token = strtok(NULL, " ");
      }
    } else {
      printf("%s: command not found\n", command);
    }
  }

  return 0;
}

void search_exec_commands(const char *command, char **buf) {
  char *path = getenv("PATH");
  if (!path) {
    if (buf)
      *buf = NULL;
    return;
  }

  char *path_copy = strdup(path);
  char *dir = strtok(path_copy, ":");

  while (dir != NULL) {
    char fullpath[512];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", dir, command);
    
    if ((access(fullpath, X_OK)) == 0) {
      free(path_copy);
      if (buf)
        *buf = strdup(fullpath);
      return;
    }
    
    dir = strtok(NULL, ":");
  }

  free(path_copy);
  *buf = NULL;
  return;
}
