#include <stdarg.h>
#include <stdio.h>

/**
 * @brief Выводит сообщение об ошибке в stderr.
 * @param format: строка формата вывода.
 * @param ... доп. аргументы для формата.
 * @return 1.
 */
int Error(const char* format, ...);

/**
 * @brief Выводит сообщение об ошибке в stderr ошибок и закрывает файлы.
 * @param format: строка формата вывода.
 * @param ... доп. аргументы для формата и список файлов.
 * @return 1.
 */
int ErrorWithFiles(const char* format, ...);