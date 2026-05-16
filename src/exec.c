#include "shell.h"
#include "exec.h"
#include "path.h"

int is_external(const char *cmd) {
    char *path = NULL;

    path = find_executable(cmd);

    if (path != NULL) {
        free(path);
        return 1;
    }

    free(path);
    return 0;
}

void run_external(char **argv) {
    pid_t pid = fork();

    char **args = argv;

    if (pid == 0) {
        execvp(args[0], args+1);
        perror("execvp failed");
        exit(1);
    } else if (pid > 0) {
        waitpid(pid, NULL, 0);
    } else {
        perror("fork failed");
    }
}
