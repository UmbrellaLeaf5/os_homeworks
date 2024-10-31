#include "backup.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <source directory> <destination directory>\n",
            argv[0]);
    return 1;
  }

  BackupFolder(argv[1], argv[2]);
  return 0;
}