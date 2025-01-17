
typedef enum FileType { TYPE_UNKNOWN, TYPE_DIRECTORY, TYPE_FILE } FileType;

typedef struct File {
    FileType type;
    char *name;
    char *path;
} File;

typedef void (*FileConsumer)(File *);

void traverse_files_rec(char *directory, int depth, FileConsumer consumer);

void traverse_files(char *directory, FileConsumer consumer);

File *list_files_rec(char *directory, int depth, int *amount);

File *list_files(char *directory, int *amount);
