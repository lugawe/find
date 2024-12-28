
typedef enum FileType { TYPE_UNKNOWN, TYPE_DIRECTORY, TYPE_FILE } FileType;

typedef struct File {
    FileType type;
    char *path;
    char *name;
} File;

typedef int (*FilePredicate)(File *);

void traverse_files_rec(char *directory, int depth, FilePredicate predicate);

void traverse_files(char *directory, FilePredicate predicate);

File *list_files_rec(char *directory, int depth, int *amount);

File *list_files(char *directory, int *amount);
