#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Выводит сообщение об ошибке в stderr.
 * @param format: строка формата вывода.
 * @param ... доп. аргументы для формата.
 * @return 1.
 */
int Error(const char *format, ...);

/**
 * @brief Выводит сообщение об ошибке в stderr ошибок и закрывает файлы.
 * @param format: строка формата вывода.
 * @param ... доп. аргументы для формата и список файлов.
 * @return 1.
 */
int ErrorWithFiles(const char *format, ...);

/**
 * @brief Добавляет строку в начало другой строки.
 * @param front_str: строка, которую нужно добавить в начало.
 * @param orig_str: строка, к которой нужно добавить `front_str`.
 */
void PushStrToFront(const char *front_str, char *orig_str);

/**
 * @brief Удаляет дубликаты из массива целых чисел.
 * @param arr: массив целых чисел.
 * @param arr_size: размер массива.
 * @return int: количество уникальных элементов в массиве.
 */
int DedupArray(int *arr, int arr_size);

/**
 * @brief Сортирует массив целых чисел по возрастанию.
 * @param arr: массив целых чисел.
 * @param arr_size: размер массива.
 */
void SortArray(int *arr, int arr_size);
