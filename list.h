
typedef struct ListNode {
    void *content;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head;
    int size;
} List;

List *list_create();

void list_traverse(List *list, void (*fnc)(void *));

void list_add(List *list, void *content);

void list_free(List *list);

