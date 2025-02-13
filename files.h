
typedef enum FileType { TYPE_UNKNOWN, TYPE_DIRECTORY, TYPE_FILE } FileType;

typedef struct File {
    FileType type;
    char *name;
    char *path;
} File;

typedef struct Options {
    char *directory;
    char *name;
    char *type;
    char *mtime;
    char *exec;
    char *size;
    char *maxdepth;
    int count;
} Options;

typedef void (*FileConsumer)(File *);

void traverse_files_rec(Options *options, FileConsumer consumer);

File *list_files_rec(Options *options, int *amount);
