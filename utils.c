#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *full_path(const char *path) {
    char buf[PATH_MAX];
    realpath(path, buf);
    return strdup(buf);
}
