#include "lib.h"

int Error(const char* format, ...) {
  // вывод сообщений об ошибках в stderr
  va_list args;
  va_start(args, format);

  vfprintf(stderr, format, args);

  va_end(args);
  return 1;
}

int ErrorWithFiles(const char* format, ...) {
  // вывод сообщений об ошибках в stderr
  va_list args;
  va_start(args, format);

  vfprintf(stderr, format, args);

  va_end(args);

  // закрытие файлов
  va_list file_args;
  va_start(file_args, format);

  for (FILE* file; (file = va_arg(file_args, FILE*));) fclose(file);

  va_end(file_args);

  return 1;
}
