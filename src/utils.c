#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char *intToStr(int number) {
    int length = snprintf(NULL, 0, "%d", number);
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", number);
    return str;
}
