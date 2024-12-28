#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *full_path(const char *path) {
    char buf[PATH_MAX];
    realpath(path, buf);
    return strdup(buf);
}

char *mstrcat(const char *str, ...) {
    int size = 1;  // includes terminating null

    char *result = malloc(sizeof(char) * size);
    result[0] = '\0';

    va_list va;
    va_start(va, str);

    while (str) {
        int len = strlen(str);
        size += len;

        char *tmp = realloc(result, sizeof(char) * size);
        if (tmp) {
            result = tmp;
            strcat(result, str);
        } else {
            size -= len;
            perror("mstrcat: cannot realloc");
        }

        str = va_arg(va, const char *);
    }

    va_end(va);

    return result;
}
