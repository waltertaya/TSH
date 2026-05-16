#include "builtin.h"
#include "shell.h"
#include "exec.h"
#include "path.h"

int LOOP_FLAG = 1;
char *BUILTIN[] = {"echo", "exit", "type"};

int is_builtin(const char *cmd) {
    for (int i = 0; i < sizeof(BUILTIN)/sizeof(BUILTIN[0]); i++)
        if (strcmp(cmd, BUILTIN[i]) == 0)
            return 1;
    
    return 0;
}

int run_builtin(char **argv) {
    if (strcmp(argv[0], "exit") == 0)
        command_exit();
    else if (strcmp(argv[0], "echo") == 0)
        command_echo(argv);
    else if (strcmp(argv[0], "type") == 0)
        command_type(argv);

    return 0;
}

void command_exit() {
    LOOP_FLAG = 0;
}

void command_echo(char **argv) {
    char **p = argv;

    p += 1;
    while (*p != NULL) {
        printf("%s ", *p);
        p++;
    }
    printf("\n");
}

void command_type(char **argv) {
    char **p = argv;
    p += 1; // skip command
    while (*p != NULL) {
        // check for builtin
        if (is_builtin(*p)) {
            printf("%s is a shell builtin\n", *p);
        } else if (is_external(*p)) { // external commands
            char *path = find_executable(*p);
            if (path != NULL) {
                printf("%s is %s\n", *p, path);
                free(path);
            }
        } else {
            printf("%s: not found\n", *p);
        }
        p++;
    }
}
