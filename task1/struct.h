#ifndef DATABASE_H
#define DATABASE_H
typedef struct Node{
    int multi; //информационное поле для коэффициента перед многочленом
    int degree; //информационное поле для степени многочлена
    struct Node *next; //адресное поле
} Node;

Node* addElement(Node* head, int multi, int degree);
void printList(Node* head);
Node* deleteNode(Node* head, unsigned int index);
void deleteList(Node** head);
Node* replaceEvenCoefficients(Node* L1, Node* L2);
Node* inputPolynomial();
int getValidInt();
#endif