#include <stdio.h>
#include <stdlib.h>

#include "files.h"

int main(int argc, char **argv) {
    // todo parse arguments

    int size = 0;
    File *files = list_files(".", &size);

    for (int i = 0; i < size; i++) {
        print_file(&files[i]);
    }

    return 0;
}

