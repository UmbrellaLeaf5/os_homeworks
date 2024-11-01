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
 * @brief Архивирует файл.
 * @param source_file: путь к исходному файлу.
 * @param dest_file: путь к файлу резервной копии.
 * @return 0, если программа успешно завершилась, иначе код ошибки.
 */
int BackupFile(const char *source_file, const char *dest_file);

/**
 * @brief Архивирует папку.
 * @param source_folder: путь к исходной папке.
 * @param dest_folder: путь к папке резервной копии.
 * @return 0, если программа успешно завершилась, иначе код ошибки.
 */
int BackupFolder(const char *source_folder, const char *dest_folder);

/**
 * @brief Архивирует папку, используя аргументы командной строки
 * @param argc: количество аргументов командной строки.
 * @param argv: массив аргументов командной строки.
 * @return 0, если программа успешно завершилась, иначе код ошибки.
 */
int Backup(int argc, char **argv);
