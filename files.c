#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files.h"
#include "list.h"

File *create_file(struct dirent *dir) {
    File *file = malloc(sizeof(File));
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
            list_add(list, create_file(dir));
        }

        int size = list->size;

        result = malloc(sizeof(File) * size);
        for (int i = 0; i < size; i++) {
            result[i] = *(File *)list_get(list, i);
        }

        *amount = size;

        closedir(d);
    }
    return result;
}

