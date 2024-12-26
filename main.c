#include <stdio.h>
#include <stdlib.h>

#include "files.h"

void print_files(char *dir) {
    int size = 0;
    File *files = list_files(dir, &size);

    for (int i = 0; i < size; i++) {
        print_file(&files[i]);
    }
}

int main(int argc, char **argv) {
    // todo parse arguments

    if (argc == 1) {
        print_files(".");
    } else if (argc == 2) {
        print_files(argv[1]);
    }

    return 0;
}

