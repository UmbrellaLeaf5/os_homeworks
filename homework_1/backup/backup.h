#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int BackupFile(const char *source_file, const char *dest_file);

int BackupFolder(const char *source_folder, const char *dest_folder);

int Backup(int argc, char *argv[]);
