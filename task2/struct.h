#ifndef DATABASE_H
#define DATABASE_H
#define MAX_LINE 1024
typedef struct _Node
{
    void *value;
    struct _Node *next;
    struct _Node *prev; 
} Node;

typedef struct _DblLinkedList
{
    unsigned int size;
    Node *head;
    Node *tail;
} DblLinkedList;

DblLinkedList* createDblLinkedList();
void deleteDblLinkedList(DblLinkedList **list);
void pushFront(DblLinkedList *list, void *data);
void pushBack(DblLinkedList *list, void *value);
Node* getNth(DblLinkedList *list, unsigned int index);
void insertAfter(DblLinkedList *list, unsigned int index, void *value);
void* deleteNth(DblLinkedList *list, unsigned int index);
void printDblLinkedList(DblLinkedList *list, void (*fun)(void*));
void printString(void *value);
void removeTrailingDot(char *str);
DblLinkedList* createListFromSentence();

#endif