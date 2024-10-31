#include "backup.h"

#include "lib.h"

int BackupFile(const char *src_file, const char *dst_file) {
  FILE *src_fp = fopen(src_file, "rb");
  if (src_fp == NULL)
    return ErrorWithFiles("Error opening source file", src_fp);

  FILE *dst_fp = fopen(dst_file, "wb");
  if (dst_fp == NULL)
    return ErrorWithFiles("Error opening destination file", dst_fp);

  char buffer[4096];
  for (size_t bytes; (bytes = fread(buffer, 1, sizeof(buffer), src_fp)) > 0;)
    fwrite(buffer, 1, bytes, dst_fp);

  fclose(src_fp);
  fclose(dst_fp);

  char command[512];
  snprintf(command, sizeof(command), "gzip %s", dst_file);

  if (system(command) == -1) return Error("Error compressing file");

  return 0;
}
