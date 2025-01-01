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

void walk_files0(char *directory, int depth, int current_depth, FileConsumer consumer) {
    DIR *d = opendir(directory);
    if (d) {
        struct dirent *dir;
        while ((dir = readdir(d)) != NULL) {
            File *file = create_file(directory, dir);
            consumer(file);
            if (file->type == TYPE_DIRECTORY && current_depth < depth) {
                char *name = file->name;
                if (strcmp(".", name) != 0 && strcmp("..", name) != 0) {
                    walk_files0(file->path, depth, current_depth + 1, consumer);
                }
            }
        }

        closedir(d);
    } else {
        perror("list_files: cannot open directory");
    }
}

void walk_files(char *directory, int depth, FileConsumer consumer) {
    walk_files0(directory, depth, 0, consumer);
}

// ---

void traverse_files_rec(char *directory, int depth, FileConsumer consumer) {
    walk_files(directory, depth, consumer);
}

void traverse_files(char *directory, FileConsumer consumer) {
    traverse_files_rec(directory, 0, consumer);
}

// ---

List *list;

void list_add_fileconsumer(File *file) {
    if (file->type == TYPE_FILE) {
        list_add(list, file);
    }
}

File *list_files_rec(char *directory, int depth, int *amount) {
    list = list_create();

    walk_files(directory, depth, list_add_fileconsumer);

    int size = list->size;

    File *result = malloc(sizeof(File) * size);
    for (int i = 0; i < size; i++) {
        result[i] = *(File *)list_get(list, i);
    }

    list_free(list);
    list = NULL;

    // qsort(result, size, sizeof(File), files_type_comparator);

    *amount = size;
    return result;
}

File *list_files(char *directory, int *amount) { return list_files_rec(directory, 0, amount); }
