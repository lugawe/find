#include <ctype.h>
#include <dirent.h>
#include <fnmatch.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "files.h"
#include "list.h"
#include "utils.h"

bool test_file(File *file, Options *options) {
    if (!options) return true;

    // -n
    if (options->name) {
        if (fnmatch(options->name, file->name, 0) != 0) {
            return false;
        }
    }

    // -t
    if (options->type) {
        char type = options->type[0];
        if ((type == 'd' && file->type != TYPE_DIRECTORY) ||
            (type == 'f' && file->type != TYPE_FILE)) {
            return false;
        }
    }

    // -m / -s
    if (options->mtime || options->size) {
        struct stat file_stat;
        if (stat(file->path, &file_stat) == 0) {
            if (options->mtime) {
                time_t now = time(NULL);
                time_t file_mtime = file_stat.st_mtime;
                int days_old = (now - file_mtime) / 86400;

                int mtime_val = abs(atoi(options->mtime));
                char sign = options->mtime[0];

                if ((sign == '+' && days_old <= mtime_val) ||
                    (sign == '-' && days_old >= mtime_val) ||
                    (isdigit(sign) && days_old != mtime_val)) {
                    return false;
                }
            }
            if (options->size) {
                int size = file_stat.st_size;
                if (atoi(options->size) != size) {
                    return false;
                }
            }
        }
    }

    // -e
    if (options->exec) {
        char command[1024];
        snprintf(command, sizeof(command), "%s %s", options->exec, file->path);
        system(command);
    }

    return true;
}

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
    file->name = dir->d_name;
    file->path = mstrcat(directory, "/", file->name, NULL);
    return file;
}

void walk_files0(char *directory, int depth, int current_depth, Options *options, FileConsumer consumer) {
    DIR *d = opendir(directory);
    if (!d) {
        perror("list_files: cannot open directory");
        return;
    }

    struct dirent *dir;
    while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            continue;
        }

        File *file = create_file(directory, dir);

        if (file->type == TYPE_DIRECTORY && (depth == -1 || current_depth < depth)) {
            walk_files0(file->path, depth, current_depth + 1, options, consumer);
        }

        if (test_file(file, options)) {
            consumer(file);
        } else {
            free(file);
        }
    }

    closedir(d);
}

void walk_files(Options *options, FileConsumer consumer) {
    walk_files0(options->directory, atoi(options->maxdepth), 0, options, consumer);
}

// ---

void traverse_files_rec(Options *options, FileConsumer consumer) {
    walk_files(options, consumer);
}

// ---

List *list;

void list_add_fileconsumer(File *file) {
    list_add(list, file);
}

File *list_files_rec(Options *options, int *amount) {
    list = list_create();

    walk_files(options, list_add_fileconsumer);

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
