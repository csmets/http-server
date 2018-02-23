#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "server_config.h"
#include "utils.h"

char *intToStr(int number) {
    int length = snprintf(NULL, 0, "%d", number);
    char *str = NULL;
    str = malloc(length + 1);
    snprintf(str, length + 1, "%d", number);
    return str;
}

int fexists(char file_name[]) {
    FILE *file;
    if ((file = fopen(file_name, "r"))) {
       fclose(file);
       return 1;
    }
    return 0;
}

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}
