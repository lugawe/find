
typedef enum FileType { TYPE_UNKNOWN, TYPE_DIRECTORY, TYPE_FILE } FileType;

typedef struct File {
    FileType type;
    char *name;
} File;

void print_file(File *file);

File *list_files(char *directory, int *amount);

