#pragma once

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

/**
 * @brief Запускает команды из файла
 * (переданного в командную строку) с задержками.
 * @param argc: количество аргументов командной строки.
 * @param argv: массив аргументов командной строки.
 * @param max_args: максимальное количество аргументов для команд.
 * @return 0, если программа успешно завершилась, иначе код ошибки.
 */
int Useless(int argc, char **argv, int max_args, int file_line_max_len);
