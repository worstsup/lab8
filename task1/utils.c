#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

int getValidInt() {
    int value;
    while (scanf("%d", &value) != 1) {
        while (getchar() != '\n');
        printf("Некорректный ввод! Пожалуйста, введите целое число: ");
    }
    return value;
}

Node* inputPolynomial() {
    Node* head = NULL;
    int multi, degree;
    char ch;
    while (1) {
        printf("Введите коэффициент: ");
        multi = getValidInt();

        printf("Введите степень: ");
        degree = getValidInt();
        while (getchar() != '\n');
        head = addElement(head, multi, degree);

        printf("Хотите добавить еще одну степень? (y/n): ");
        scanf("%c", &ch);
        if (ch != 'y' && ch != 'Y') break;
    }
    return head;
}

// Функция добавления элемента в список
Node* addElement(Node* head, int multi, int degree) {
    // Если коэффициент равен нулю, не добавляем элемент в список
    if (multi == 0) {
        return head;
    }

    Node* tmp = head;
    Node* prev = NULL;

    // Ищем позицию для вставки в порядке убывания степени
    while (tmp != NULL) {
        if (tmp->degree == degree) {
            // Если степень совпадает, складываем коэффициенты
            tmp->multi += multi;
            // Если коэффициент после сложения стал нулевым, удаляем элемент
            if (tmp->multi == 0) {
                return deleteNode(head, degree);
            }
            return head;
        }
        if (tmp->degree < degree) {
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    // новый узел
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->multi = multi;
    new_node->degree = degree;
    new_node->next = NULL;

    if (prev == NULL) {
        new_node->next = head;
        return new_node;
    }

    // Вставляем новый элемент в список
    new_node->next = prev->next;
    prev->next = new_node;

    return head;
}

// Функция печати списка
void printList(Node* head) {
    if (!head) {
        printf("List is empty\n");
        return;
    }

    int firstElement = 1;

    while (head) {
        if (head->multi == 0) {
            head = head->next;
            continue;
        }

        if (firstElement) {
            if (head->multi == 1) {
                if (head->degree == 0) {
                    printf("1");
                } 
                else if (head->degree == 1) {
                    printf("x");
                } 
                else {
                    printf("x^%d", head->degree);
                }
            } 
            else if (head->multi == -1) {
                if (head->degree == 0) {
                    printf("-1");
                } 
                else if (head->degree == 1) {
                    printf("-x");
                } 
                else {
                    printf("-x^%d", head->degree);
                }
            } 
            else {
                printf("%d", head->multi);
                if (head->degree == 1) {
                    printf("*x");
                } 
                else if (head->degree != 0) {
                    printf("*x^%d", head->degree);
                }
            }
            firstElement = 0;
        } 
        else {
            if (head->multi == 1) {
                if (head->degree == 0) {
                    printf(" + 1");
                } 
                else if (head->degree == 1) {
                    printf(" + x");
                } 
                else {
                    printf(" + x^%d", head->degree);
                }
            } 
            else if (head->multi == -1) {
                if (head->degree == 0) {
                    printf(" - 1");
                } 
                else if (head->degree == 1) {
                    printf(" - x");
                } 
                else {
                    printf(" - x^%d", head->degree);
                }
            } 
            else if (head->multi > 0) {
                printf(" + %d", head->multi);
                if (head->degree == 1) {
                    printf("*x");
                } 
                else if (head->degree != 0) {
                    printf("*x^%d", head->degree);
                }
            } 
            else {
                printf(" - %d", -head->multi);
                if (head->degree == 1) {
                    printf("*x");
                } 
                else if (head->degree != 0) {
                    printf("*x^%d", head->degree);
                }
            }
        }

        head = head->next;
    }
    printf("\n");
}

// Функция удаления элемента по индексу
Node* deleteNode(Node* head, unsigned int index) {
    if (!head) {
        printf("Список пуст\n");
        return head;
    }

    Node* tmp = head;
    if (index == 0) {
        head = head->next;
        free(tmp);
        return head;
    }

    int i = 0;
    while (tmp && i < index - 1) {
        tmp = tmp->next;
        i++;
    }

    if (!tmp || !tmp->next) return head;

    Node* to_delete = tmp->next;
    tmp->next = to_delete->next;
    free(to_delete);
    return head;
}

// Функция удаления списка
void deleteList(Node** head) {
    Node* tmp = *head;
    while (tmp) {
        Node* next = tmp->next;
        free(tmp);
        tmp = next;
    }
    *head = NULL;
}

// Функция замены четных коэффициентов из L1 на коэффициенты из L2
Node* replaceEvenCoefficients(Node* L1, Node* L2) {
    Node* tmp1 = L1;
    Node* tmp2 = L2;
    int maxDegree = -1;
    int maxMulti = 0;
    while (tmp2) {
        if (tmp2->degree > maxDegree) {
            maxDegree = tmp2->degree;
            maxMulti = tmp2->multi;
        }
        tmp2 = tmp2->next;
    }
    while (tmp1) {
        if (tmp1->multi % 2 == 0) {
            tmp1->multi = maxMulti;
        }
        tmp1 = tmp1->next;
    }
    return L1;
}