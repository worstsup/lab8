#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct.h"

int main() {
    DblLinkedList *list = createListFromSentence();
    printf("\nИсходный список:\n");
    printDblLinkedList(list, printString);
    unsigned int n;
    char newWord[100];
    printf("\nВведите номер элемента, после которого хотите вставить новое слово (0 - %u): ", list->size - 1);
    scanf("%u", &n);
    while(getchar() != '\n');
    printf("Введите новое слово: ");
    scanf("%s", newWord);
    char *insertedWord = (char*)malloc(strlen(newWord) + 1);
    if (insertedWord == NULL) {
        printf("Ошибка выделения памяти.\n");
        deleteDblLinkedList(&list);
        return 1;
    }
    strcpy(insertedWord, newWord);
    if (n >= list->size) {
        pushBack(list, insertedWord);
    } else {
        insertAfter(list, n, insertedWord);
    }
    printf("\nСписок после вставки нового слова:\n");
    printDblLinkedList(list, printString);
    deleteDblLinkedList(&list);
    return 0;
}