#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List *list_create() {
    List *result = malloc(sizeof(List));
    result->head = NULL;
    result->size = 0;
    return result;
}

void list_traverse(List *list, void (*fnc)(void *)) {
    if (list == NULL) {
        perror("list_traverse: list is NULL");
    }

    ListNode *head = list->head;
    while (head != NULL) {
        fnc(head->content);
        head = head->next;
    }
}

void list_add(List *list, void *content) {
    if (list == NULL) {
        perror("list_add: list is NULL");
    }

    ListNode *node = malloc(sizeof(ListNode));
    node->content = content;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
    } else {
        ListNode *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }

    list->size++;
}

void *list_get(List *list, int index) {
    if (list == NULL) {
        perror("list_get: list is NULL");
    }
    if (index < 0 || index > list->size) {
        perror("list_get: invalid index");
    }

    int c = 0;

    ListNode *head = list->head;
    while (head != NULL) {
        if (index == c) {
            return head->content;
        }
        head = head->next;
        c++;
    }

    return NULL;
}

void list_free(List *list) {
    if (list == NULL) {
        perror("list_free: list is NULL");
    }

    ListNode *current = list->head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

