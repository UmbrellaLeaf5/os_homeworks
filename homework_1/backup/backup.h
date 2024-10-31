#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int BackupFile(const char *src_file, const char *dst_file);

int BackupFolder(const char *src_dir, const char *dst_dir);
