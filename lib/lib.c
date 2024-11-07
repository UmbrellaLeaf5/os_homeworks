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

inline void PushStrToFront(const char* front_str, char* orig_str) {
  // временный массив, достаточно большой, чтобы вместить обе строки
  char temp[strlen(front_str) + strlen(orig_str) + 1];

  strcpy(temp, front_str);
  strcpy(temp + strlen(front_str), orig_str);
  strcpy(orig_str, temp);
}

int DedupArray(int* arr, int arr_size) {
  if (arr_size <= 1) return arr_size;  // если пуст

  int j = 0;
  for (int i = 0; i < arr_size; i++) {
    int is_duplicate = 0;

    // встречается ли текущий элемент arr[i] в массиве после него
    for (int k = i + 1; k < arr_size; k++)
      if (arr[i] == arr[k]) {
        is_duplicate = 1;
        break;
      }

    // элемент не является дубликатом, добавляем его в новый массив
    if (!is_duplicate) arr[j++] = arr[i];
  }

  return j;
}

int CompareInts(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

void SortArray(int* arr, int arr_size) {
  qsort(arr, arr_size, sizeof(int), CompareInts);
}
