#include "backup.h"

#include "lib.h"

int BackupFile(const char *source_file, const char *dest_file) {
  FILE *src_file = fopen(source_file, "rb");
  if (src_file == NULL)
    return ErrorWithFiles("Error opening source file", src_file);

  FILE *dst_file = fopen(dest_file, "wb");
  if (dst_file == NULL)
    return ErrorWithFiles("Error opening destination file", dst_file);

  char buffer[4096];
  for (size_t bytes; (bytes = fread(buffer, 1, sizeof(buffer), src_file)) > 0;)
    fwrite(buffer, 1, bytes, dst_file);

  fclose(src_file);
  fclose(dst_file);

  char gzip_command[512];
  snprintf(gzip_command, sizeof(gzip_command), "gzip %s", dest_file);

  if (system(gzip_command) == -1) return Error("Error compressing file");

  return 0;
}

int BackupFolder(const char *source_folder, const char *dest_folder) {
  struct stat st_src_folder;

  if (stat(source_folder, &st_src_folder) != 0 ||
      !S_ISDIR(st_src_folder.st_mode))
    return Error(
        "Source directory '%s' does not exist or is not a directory.\n",
        source_folder);

  DIR *src_folder = opendir(source_folder);
  if (src_folder == NULL) return Error("Error opening source directory");

  struct dirent *entry;
  while ((entry = readdir(src_folder)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    char src_path[512];
    snprintf(src_path, sizeof(src_path), "%s/%s", source_folder, entry->d_name);
    char dst_path[512];
    snprintf(dst_path, sizeof(dst_path), "%s/%s", dest_folder, entry->d_name);

    if (entry->d_type == DT_DIR) {
      mkdir(dst_path, 0755);
      BackupFolder(src_path, dst_path);

    } else if (entry->d_type == DT_REG) {
      if (access(dst_path, F_OK) == -1)
        BackupFile(src_path, dst_path);

      else {
        struct stat src_stat, dst_stat;
        stat(src_path, &src_stat);
        stat(dst_path, &dst_stat);

        if (src_stat.st_mtime > dst_stat.st_mtime)
          BackupFile(src_path, dst_path);
      }
    }
  }

  closedir(src_folder);
  return 0;
}

int Backup(int argc, char *argv[]) {
  if (argc != 3)
    return Error("Usage: %s <source directory> <destination directory>\n",
                 argv[0]);

  return BackupFolder(argv[1], argv[2]);
}
