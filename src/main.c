#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAXLINE 256

char *builtin[] = {"echo", "exit", "type"};

void search_exec_commands(const char *command, char **buf);
int find_if_executable(const char *input);
void run_executable(char *command);
void tokenization(char *string, char **buf);

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

        if (!found) {
          char *full_path = NULL;
          search_exec_commands(token, &full_path);
          if (full_path != NULL) {
            printf("%s is %s\n", token, full_path);
            free(full_path);
            found = 1;
          }
        }

        if (!found && token != NULL && strlen(token) > 0) {
          printf("%s: not found\n", token);
        }
        
        token = strtok(NULL, " ");
      }
    } else if (find_if_executable(command)) { // running external program
      // int ret = system(command);
      run_executable(command);
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
  char *saveptr;
  char *dir = strtok_r(path_copy, ":", &saveptr);

  while (dir != NULL) {
    char fullpath[512];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", dir, command);
    
    if ((access(fullpath, F_OK)) == 0 && access(fullpath, X_OK) == 0) {
      free(path_copy);
      if (buf)
        *buf = strdup(fullpath);
      return;
    }
    
    dir = strtok_r(NULL, ":", &saveptr);
  }

  free(path_copy);
  *buf = NULL;
  return;
}

int find_if_executable(const char *input) {
  char *command = strdup(input);

  // handle commands with / without arguments
  size_t space_pos = strcspn(input, " \t");
  if (space_pos != strlen(input)) {
    char *space = strchr(command, ' ');

    if (space != NULL)
      *space = '\0';
  }

  char *full_path = NULL;
  search_exec_commands(command, &full_path);
  if (full_path != NULL) {
    free(full_path);
    free(command);
    return 1;
  }

  free(full_path);
  free(command);
  return 0;
}

void run_executable(char *command) {
  char *args[64];
  tokenization(command, args);

  pid_t pid = fork();

  if (pid == 0) {
    execvp(args[0], args);
    perror("execvp failed");
    exit(1);
  } else if (pid > 0) {
    waitpid(pid, NULL, 0);
  } else {
    perror("fork failed");
  }
}

void tokenization(char *string, char *buf[]) {
  // char *buf[64];
  int i = 0;

  char *token = strtok(string, " ");
  while (token != NULL && i < 63) {
    buf[i++] = token;
    token = strtok(NULL, " ");
  }

  buf[i] = NULL;
}
