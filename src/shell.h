#ifndef SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define SHELL_H
#define MAXLINE 256

extern int LOOP_FLAG;

void trim_newline(char *input);

#endif
