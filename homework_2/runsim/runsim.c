#include "runsim.h"

#include "lib.h"

int Runsim(int argc, char **argv, int max_args) {
  if (argc != 2)  // кол-во аргументов должно быть строго 2 (+ кол-во программ)
    return Error("Wrong usage! Use: %s <max_commands_amount>\n", argv[0]);

  // получение максимального кол-ва одновременно выполняющихся команд
  int max_commands_amount = atoi(argv[1]);

  if (max_commands_amount <= 0)
    return Error("Invalid programs amount! (should be positive)\n");

  if (max_commands_amount > INT_MAX)
    return Error("Invalid programs amount! (too much)\n");

  // счетчик запущенных команд
  int commands_count = 0;

  // буфер для чтения команд из стандартного ввода
  char buffer[4096];

  // чтение команд из стандартного ввода
  while (fgets(buffer, sizeof(buffer), stdin)) {
    // удаление символа новой строки из буфера
    buffer[strcspn(buffer, "\n")] = 0;

    while (commands_count) {
      // ожидание завершения любого дочернего процесса без блокировки
      pid_t pid = waitpid(-1, NULL, WNOHANG);

      if (pid > 0)
        commands_count--;

      else  // если нет завершенных процессов, выходим из внутреннего цикла
        break;
    }

    if (commands_count >= max_commands_amount) {
      // превышение максимального количества одновременно работающих команд
      Error(
          "Too many running commands. Please wait or close some to "
          "continue...\n");
      continue;
    }

    // разбиение строки на имя команды и аргументы
    char *command_name = strtok(buffer, " ");

    // аргументы команды
    char *command_args[max_args];

    // первый аргумент команды - имя команды
    command_args[0] = command_name;

    {
      int command_arg_count = 1;

      // получение аргументов из строки
      for (char *arg;
           (arg = strtok(NULL, " \n")) && command_arg_count < max_args - 1;)
        command_args[command_arg_count++] = arg;

      // последний аргумент NULL
      command_args[command_arg_count] = NULL;
    }

    // дочерний процесс
    pid_t pid = fork();

    // fork не удался
    if (pid < 0) return Error("Error forking: %s\n", strerror(errno));

    // выполняется только в дочернем процессе:
    if (pid == 0) {
      if (execvp(command_name, command_args) == -1)
        // в том случае, если команда не выполнилась
        return Error("Error executing command '%s': %s\n", command_name,
                     strerror(errno));

    } else  // в родительском процессе
      commands_count++;
  }

  // ожидание завершения всех запущенных дочерних процессов
  while (wait(NULL) > 0);

  return 0;
}