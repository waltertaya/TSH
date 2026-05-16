#include "shell.h"
#include "parser.h"
#include "builtin.h"
#include "exec.h"
#include "path.h"

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  char input[MAXLINE];

  while (LOOP_FLAG) {
      printf("$ ");

      if (!fgets(input, sizeof(input), stdin)) break;

      trim_newline(input);

      char **argv = parse_input(input);
      if (!argv || !argv[0]) {
          free_argv(argv);
          continue;
      }

      if (is_builtin(argv[0])) {
          run_builtin(argv);
      } else if (is_external(argv[0])){
          run_external(argv);
      } else {
        printf("%s: command not found\n", argv[0]);
      }

      free_argv(argv);
  }

  return 0;
}
