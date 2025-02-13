
#include <string.h>

#include "files.h"

int files_name_comparator(const void *a, const void *b) {
    const File *f1 = (const File *)a;
    const File *f2 = (const File *)b;

    return strcmp(f1->path, f2->path);
}

int files_type_comparator(const void *a, const void *b) {
    const File *f1 = (const File *)a;
    const File *f2 = (const File *)b;

    return f1->type - f2->type;
}
