#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "files.h"

void parse_arguments(int argc, char **argv, Options *options) {
    int option;

    options->directory = ".";
    options->maxdepth = "-1";

    if (argc > 1 && argv[1][0] != '-') {
        options->directory = argv[1];
    }

    while ((option = getopt(argc, argv, "n:t:m:e:s:d:c")) != -1) {
        switch (option) {
            case 'n':  // -name
                options->name = optarg;
                // printf("'-name' with value: %s\n", options->name);
                break;
            case 't':  // -type
                options->type = optarg;
                // printf("'-type' with value: %s\n", options->type);
                break;
            case 'm':  // -mtime
                options->mtime = optarg;
                // printf("'-mtime' with value: %s\n", options->mtime);
                break;
            case 'e':  // -exec
                options->exec = optarg;
                // printf("'-exec' with value: %s\n", options->exec);
                break;
            case 's':  // -size
                options->size = optarg;
                // printf("'-size' with value: %s\n", options->size);
                break;
                case 'd':  // -maxdepth
                options->maxdepth = optarg;
                // printf("'-maxdepth' with value: %s\n", options->maxdepth);
                break;
            case 'c':  // -count
                options->count = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [directory] [-m value] [-e command] [-n filename] [-t filetype] [-s size] [-d maxdepth]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

void print_file(File *file) { printf("%s\n", file->path); }

void list_print_files(Options *options) {
     int size = 0;
     File *files = list_files_rec(options, &size);

     for (int i = 0; i < size; i++) {
         print_file(&files[i]);
     }
}

void traverse_print_files(Options *options) {
    //list_print_files(options);
    traverse_files_rec(options, print_file);
}

int main(int argc, char **argv) {
    Options options = {NULL, NULL, NULL, NULL, NULL};

    parse_arguments(argc, argv, &options);
    traverse_print_files(&options);

    return 0;
}
