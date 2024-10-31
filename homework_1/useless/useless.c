#include "useless.h"

#include "lib.h"

int Useless(int argc, char **argv, int max_args) {
  if (argc != 2) return Error("Wrong usage! Use: %s <file_name>\n", argv[0]);

  char *file_name = argv[1];
  FILE *file = fopen(file_name, "r");

  if (file == NULL)
    return Error("Error opening file '%s': %s\n", file_name, strerror(errno));

  char line[1024];

  while (fgets(line, sizeof(line), file) != NULL) {
    char *delay_str = strtok(line, " ");
    char *command_name = strtok(NULL, " \n");

    if (delay_str == NULL || command_name == NULL) {
      Error("Invalid line in file: %s\n", line);
      continue;
    }

    sleep(atoi(delay_str));

    char *command_args[max_args];
    command_args[0] = command_name;
    int i = 1;

    for (char *arg = strtok(NULL, " \n"); arg != NULL && i < max_args - 1;
         arg = strtok(NULL, " \n"))
      command_args[i++] = arg;

    command_args[i] = NULL;
    pid_t pid = fork();

    if (pid < 0)
      return ErrorWithFiles("Error forking: %s\n", strerror(errno), file);

    if (pid == 0) {
      // child process
      execvp(command_name, command_args);
      return ErrorWithFiles("Error executing command '%s': %s\n", command_name,
                            strerror(errno), file);
    }

    // parent process
    waitpid(pid, NULL, 0);
  }

  fclose(file);
  return 0;
}