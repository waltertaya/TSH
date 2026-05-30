#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PARSER_H

char **parse_input(char *input) {
    int size = 0, capacity = 2, i = 0;
    char **argv = malloc(capacity * sizeof(char *));

    char *p = input;
    char token[512];

    int single_qoute = 0;
    int double_qoute = 0;
    while (*p != '\0') {
        if (*p == '"' && single_qoute == 0) {
            if (*(p+1) != '\0' && *(p+1) == '"') {
                p += 2;
                continue;
            }
            double_qoute = !double_qoute;
            *p++;
            continue;
        }

        if (*p == '\'' && double_qoute == 0) {
            if (*(p+1) != '\0' && *(p+1) == '\'') {
                p +=2;
                continue;
            }
            single_qoute = !single_qoute;
            *p++;
            continue;
        }

        if (single_qoute || double_qoute) {
            token[i++] = *p;
        } else if (*p == ' ') {
            if (i == 0) {
                p++;
                continue;
            }
            token[i] = '\0';

            if (size + 1 >= capacity) {
                capacity *= 2;
                char **temp = realloc(argv, capacity * sizeof(char *));


                if (temp == NULL)
                    return NULL;

                argv = temp;
            }
            
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
