#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

// Создание нового пустого списка
DblLinkedList* createDblLinkedList() {
    DblLinkedList *tmp = (DblLinkedList*)malloc(sizeof(DblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
    return tmp;
}

// Удаление всего списка
void deleteDblLinkedList(DblLinkedList **list) {
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

// Добавление элемента в начало списка
void pushFront(DblLinkedList *list, void *data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        return;
    }
    tmp->value = data;
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;
    if (list->tail == NULL) {
        list->tail = tmp;
    }
    list->size++;
}


// Добавление элемента в конец списка
void pushBack(DblLinkedList *list, void *value) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        return;
    }
    tmp->value = value;
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;
    if (list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}

// Получение N–го узла
Node* getNth(DblLinkedList *list, unsigned int index) {
    Node *tmp = NULL;
    unsigned int i;
    if (index < list->size/2) {
        i = 0;
        tmp = list->head;
        while (tmp && i < index) {
            tmp = tmp->next;
            i++;
        }
    }
    else {
        i = list->size - 1;
        tmp = list->tail;
        while (tmp && i > index) {
            tmp = tmp->prev;
            i--;
        }
    }
    return tmp;
}

// Вставка нового узла после узла с индексом index
void insertAfter(DblLinkedList *list, unsigned int index, void *value) {
    Node *elm = getNth(list, index);
    if (elm == NULL) {
        printf("Элемент с индексом %u не найден!\n", index);
        return;
    }
    Node *ins = (Node*) malloc(sizeof(Node));
    if (ins == NULL)
        return;
    ins->value = value;
    ins->prev = elm;
    ins->next = elm->next;
    if (elm->next) {
        elm->next->prev = ins;
    } else {
        list->tail = ins;
    }
    elm->next = ins;
    list->size++;
}

// Удаление N–го узла
void* deleteNth(DblLinkedList *list, unsigned int index) {
    Node *elm = NULL;
    void *tmp = NULL;
    elm = getNth(list, index);
    if (elm == NULL) {
        return NULL;
    }
    if (elm->prev) {
        elm->prev->next = elm->next;
    }
    if (elm->next) {
        elm->next->prev = elm->prev;
    }
    tmp = elm->value;
    if (!elm->prev) {
        list->head = elm->next;
    }
    if (!elm->next) {
        list->tail = elm->prev;
    }
    free(elm);
    list->size--;
    return tmp;
}

// Функция вывода списка слов (значения – строки)
void printDblLinkedList(DblLinkedList *list, void (*fun)(void*))
{
    Node *tmp = list->head;
    while (tmp)
   {
        fun(tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

// Функция вывода строки (слово)
void printString(void *value) {
    printf("%s ", (char*) value);
}


// Функция удаляет завершающую точку, если она есть
void removeTrailingDot(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '.')
        str[len - 1] = '\0';
}

// Функция формирования двусвязного списка слов из введённой строки
DblLinkedList* createListFromSentence() {
    char line[MAX_LINE];
    DblLinkedList *list = createDblLinkedList();
    printf("Введите предложение (слова разделены пробелами, окончание - точка):\n");
    if (!fgets(line, sizeof(line), stdin)) {
        return list;
    }
    line[strcspn(line, "\n")] = '\0';
    removeTrailingDot(line);
    char *token = strtok(line, " ");
    while (token != NULL) {
        char *word = (char*)malloc(strlen(token) + 1);
        if (word == NULL) {
            token = strtok(NULL, " ");
            continue;
        }
        strcpy(word, token);
        pushBack(list, word);
        token = strtok(NULL, " ");
    }
    return list;
}