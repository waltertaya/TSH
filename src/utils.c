#include "shell.h"

void trim_newline(char *input) {
    input[strcspn(input, "\r\n")] = '\0';
}
