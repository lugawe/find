#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void print_int(void *content) { printf("%d\n", *(int *)content); }

int main() {
    List *list = list_create();
    int a = 2;
    int b = 3;
    int c = 5;
    int d = -42;
    list_add(list, &a);
    list_add(list, &b);
    list_add(list, &c);
    list_add(list, &d);
    list_traverse(list, print_int);
    for (int i = 0; i < list->size; i++) {
        print_int(list_get(list, i));
    }
    list_free(list);
    return 0;
}

