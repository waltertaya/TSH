#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PARSER_H

char **parse_input(char *input) {
    int size = 0, capacity = 2, i = 0;
    char **argv = malloc(capacity * sizeof(char *));

    char *p = input;
    char token[512];

    while (*p != '\0') {
        if (*p == ' ') {
            token[i] = '\0';

            if (size + 1 >= capacity) {
                capacity *= 2;
                argv = realloc(argv, capacity * sizeof(char *));
            }

            if (argv == NULL)
                return NULL;
            
            argv[size] = malloc(strlen(token) + 1);
            strcpy(argv[size], token);

            size++;
            i = 0;
        } else {
            token[i++] = *p;
        }
        
        p++;
    }

    token[i] = '\0';

    argv[size] = malloc(strlen(token) + 1);
    strcpy(argv[size], token);

    size++;

    argv[size] = NULL;

    return argv;
}

void free_argv(char **argv) {
    free(argv);
}
