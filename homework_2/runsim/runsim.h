#pragma once

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief Осуществляет контроль количества
 * (одновременно работающих) приложений, запущенных с её помощью.
 * @param argc: количество аргументов командной строки.
 * @param argv: массив аргументов командной строки.
 * @param max_args: максимальное количество аргументов для команд.
 * @return 0, если программа успешно завершилась, иначе код ошибки.
 */
int Runsim(int argc, char **argv, int max_args);