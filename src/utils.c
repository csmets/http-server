#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char *intToStr(int number) {
    int length = snprintf(NULL, 0, "%d", number);
    char *str = malloc(length + 1);
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
