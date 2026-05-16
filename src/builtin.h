#ifndef BUILTIN_H
#define BUILTIN_H

extern char *BUILTIN[];

int is_builtin(const char *cmd);
int run_builtin(char **argv);
void command_exit();
void command_echo(char **argv);
void command_type(char **argv);

#endif
