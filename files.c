#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files.h"
#include "list.h"
#include "utils.h"

File *create_file(char *directory, struct dirent *dir) {
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
    file->path = mstrcat(directory, "/", file->name, NULL);
    return file;
}

void walk_files0(List *list, char *directory, int depth, int current_depth) {
    DIR *d = opendir(directory);
    if (d) {
        struct dirent *dir;
        while ((dir = readdir(d)) != NULL) {
            File *file = create_file(directory, dir);
            if (file->type != TYPE_UNKNOWN) {
                list_add(list, file);
            }
            if (file->type == TYPE_DIRECTORY && current_depth < depth) {
                char *name = file->name;
                if (strcmp(".", name) != 0 && strcmp("..", name) != 0) {
                    walk_files0(list, file->path, depth, current_depth + 1);
                }
            }
        }

        closedir(d);
    } else {
        perror("list_files: cannot open directory");
    }
}

void walk_files(List *list, char *directory, int depth) {
    walk_files0(list, directory, depth, 0);
}

void print_file(File *file) { printf("%s\n", file->path); }

File *list_files_rec(char *directory, int depth, int *amount) {
    File *result;
    DIR *d = opendir(directory);
    if (d) {
        List *list = list_create();

        walk_files(list, directory, depth);

        int size = list->size;

        result = malloc(sizeof(File) * size);
        for (int i = 0; i < size; i++) {
            result[i] = *(File *)list_get(list, i);
        }

        list_free(list);

        // qsort(result, size, sizeof(File), files_type_comparator);

        *amount = size;

        closedir(d);
    } else {
        perror("list_files: cannot open directory");
    }
    return result;
}

File *list_files(char *directory, int *amount) {
    return list_files_rec(directory, 0, amount);
}
