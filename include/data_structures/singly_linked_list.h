#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include "../core/student.h"
#include <iostream>

using namespace std;

// ========== Cài đặt danh sách liên kết đơn ==========

// Định nghĩa cấu trúc node cho danh sách liên kết đơn
#ifndef NODE_SLL_DEFINED
#define NODE_SLL_DEFINED
struct NodeSLL
{
    Student info;
    NodeSLL *next;
};
#endif

// Function declarations
void initSLL(NodeSLL *&head);
NodeSLL *createNodeSLL(const Student &student);
void addToHeadSLL(NodeSLL *&head, const Student &student);
void addToTailSLL(NodeSLL *&head, const Student &student);
bool deleteFromSLL(NodeSLL *&head, const char *studentID);
NodeSLL *searchInSLL(NodeSLL *head, const char *studentID);
bool updateInSLL(NodeSLL *head, const Student &newInfo);
void displaySLL(NodeSLL *head);
void freeSLL(NodeSLL *&head);

#endif // SINGLY_LINKED_LIST_H