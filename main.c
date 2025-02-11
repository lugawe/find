#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "files.h"

void parse_arguments(int argc, char **argv, Options *options) {
    int option;

    options->directory = ".";

    if (argc > 1 && argv[1][0] != '-') {
        options->directory = argv[1];
    }

    while ((option = getopt(argc, argv, "n:t:m:e:")) != -1) {
        switch (option) {
            case 'n':  // -name
                options->name = optarg;
                printf("'-name' with value: %s\n", options->name);
                break;
            case 't':  // -type
                options->type = optarg;
                printf("'-type' with value: %s\n", options->type);
                break;
            case 'm':  // -mtime
                options->mtime = optarg;
                printf("'-mtime' with value: %s\n", options->mtime);
                break;
            case 'e':  // -exec
                options->exec = optarg;
                printf("'-exec' with value: %s\n", options->exec);
                break;
            default:
                fprintf(stderr, "Usage: %s [-m value] [-e command] [-n filename] [-t filetype] [directory]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

void print_file(File *file) { printf("%s\n", file->path); }

// void list_print_files(char *dir) {
//     int size = 0;
//     File *files = list_files_rec(dir, 1000, &size);  // todo to be discussed

//     for (int i = 0; i < size; i++) {
//         print_file(&files[i]);
//     }
// }

void traverse_print_files(Options *options) {
    traverse_files_rec(1000, options, print_file);  // todo to be discussed
}

int main(int argc, char **argv) {
    Options options = {NULL, NULL, NULL, NULL, NULL};
    
    parse_arguments(argc, argv, &options);
    traverse_print_files(&options);

    return 0;
}
