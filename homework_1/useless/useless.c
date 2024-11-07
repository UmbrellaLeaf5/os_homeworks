#include "useless.h"

#include "lib.h"

int Useless(int argc, char **argv, int max_args, int file_line_max_len) {
  if (argc != 2)  // кол-во аргументов должно быть строго 2 (+ название файла)
    return Error("Wrong usage! Use: %s <file_name>\n", argv[0]);

  // получение имени файла и его открытие на чтение
  char *file_name = argv[1];
  FILE *file = fopen(file_name, "r");

  if (!file)
    return Error("Error opening file '%s': %s\n", file_name, strerror(errno));

  int *delays = malloc(sizeof(int));
  char **commands = malloc(sizeof(char *));

  int max_index = 0;

  // строка файла
  char file_line[file_line_max_len];

  // чтение строк файла, пока не встретим конец
  while (fgets(file_line, sizeof(file_line), file)) {
    delays = realloc(delays, sizeof(int) * (max_index + 1));
    commands = realloc(commands, sizeof(char *) * (max_index + 1));

    // время выполнения команды (до пробела)
    char *command_delay_str = strtok(file_line, " ");
    delays[max_index] = atoi(command_delay_str);

    // имя команды (до переноса)
    char *command_with_args = strtok(NULL, "\n");

    // если какая-то из частей NULL, пропускаем
    if (!command_delay_str || !command_with_args) {
      Error("Invalid line in file: %s\n", file_line);
      continue;
    }

    PushStrToFront(" ", command_with_args);
    PushStrToFront(command_delay_str, command_with_args);

    commands[max_index] = malloc(strlen(command_with_args) + 1);
    strcpy(commands[max_index], command_with_args);

    max_index++;
  }

  int commands_amount =
      max_index;  // (индекс увеличился лишний раз в последней итерации)

  int delays_amount = DedupArray(delays, commands_amount);
  SortArray(delays, delays_amount);

  for (int i = 0; i < delays_amount; i++) {
    // задержка на кол-во секунд в delays[i] - delays[i - 1]
    if (i != 0)
      sleep((unsigned int)(delays[i] - delays[i - 1]));
    else
      sleep((unsigned int)delays[i]);

    for (int j = 0; j < commands_amount; j++) {
      char curr_command[strlen(commands[j]) + 1];
      strcpy(curr_command, commands[j]);

      char *command_delay_str = strtok(curr_command, " ");

      if (atoi(command_delay_str) == delays[i]) {
        char *command_name = strtok(NULL, " \n");

        // аргументы команды
        char *command_args[max_args];

        // первый аргумент команды - имя команды
        command_args[0] = command_name;
        int command_arg_count = 1;

        // получение аргументов из строки
        for (char *arg;
             (arg = strtok(NULL, " \n")) && command_arg_count < max_args - 1;)
          command_args[command_arg_count++] = arg;

        // последний аргумент NULL
        command_args[command_arg_count] = NULL;

        // дочерний процесс
        pid_t pid = fork();

        // fork не удался
        if (pid < 0)
          return ErrorWithFiles("Error forking: %s\n", strerror(errno), file);

        // выполняется только в дочернем процессе.
        if (pid == 0)
          // дочерний процесс: запуск команды с аргументами.
          if (execvp(command_name, command_args) == -1)
            // в том случае, если команда не выполнилась
            return ErrorWithFiles("Error executing command '%s': %s\n",
                                  command_name, strerror(errno), file);

        waitpid(pid, NULL, 0);
      }
    }
  }

  free(delays);

  for (int i = 0; i < commands_amount; i++) free(commands[i]);
  free(commands);

  fclose(file);

  return 0;
}
