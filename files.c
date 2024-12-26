#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files.h"
#include "list.h"

File *create_file(struct dirent *dir) {
    File *file = malloc(sizeof(File));
    switch (dir->d_type) {
        case DT_DIR:
            file->type = TYPE_DIRECTORY;
            break;
        case DT_REG:
            file->type = TYPE_FILE;
            break;
        default:
            file->type = TYPE_UNKNOWN;
            break;
    }
    file->name = strdup(dir->d_name);
    return file;
}

void print_file(File *file) { printf("%s\n", file->name); }

File *list_files(char *directory, int *amount) {
    File *result;
    DIR *d = opendir(directory);
    if (d) {
        List *list = list_create();

        struct dirent *dir;
        while ((dir = readdir(d)) != NULL) {
            File *file = create_file(dir);
            if (file->type != TYPE_UNKNOWN) {
                list_add(list, file);
            }
        }

        int size = list->size;

        result = malloc(sizeof(File) * size);
        for (int i = 0; i < size; i++) {
            result[i] = *(File *)list_get(list, i);
        }

        list_free(list);

        // qsort(result, size, sizeof(File), files_type_comparator);

        *amount = size;

        closedir(d);
    }
    return result;
}

