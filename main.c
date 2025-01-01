#include <stdio.h>
#include <stdlib.h>

#include "files.h"

void print_file(File *file) { printf("%s\n", file->path); }

void list_print_files(char *dir) {
    int size = 0;
    File *files = list_files_rec(dir, 1000, &size);  // todo to be discussed

    for (int i = 0; i < size; i++) {
        print_file(&files[i]);
    }
}

void traverse_print_files(char *dir) {
    traverse_files_rec(dir, 1000, print_file);  // todo to be discussed
}

int main(int argc, char **argv) {
    // todo parse arguments

    if (argc == 1) {
        traverse_print_files(".");
    } else if (argc == 2) {
        traverse_print_files(argv[1]);
    }

    return 0;
}
