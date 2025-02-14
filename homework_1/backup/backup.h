#pragma once

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

/**
 * @brief Архивирует папку, используя аргументы командной строки
 * @param argc: количество аргументов командной строки.
 * @param argv: массив аргументов командной строки.
 * @return 0, если программа успешно завершилась, иначе код ошибки.
 */
int Backup(int argc, char **argv);
