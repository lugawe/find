
typedef struct File {
    char *name;
    long size;
} File;

void print_file(File *file);

File *list_files(char *directory, int *amount);

