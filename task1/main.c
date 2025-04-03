#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

int main() {
    Node* L1 = NULL;
    Node* L2 = NULL;

    printf("Ввод многочлена L1:\n");
    L1 = inputPolynomial();
    printf("Ввод многочлена L2:\n");
    L2 = inputPolynomial();
    printf("L1 до обработки: ");
    printList(L1);
    printf("L2: ");
    printList(L2);
    L1 = replaceEvenCoefficients(L1, L2);
    printf("L1 после обработки: ");
    printList(L1);

    deleteList(&L1);
    deleteList(&L2);

    return 0;
}