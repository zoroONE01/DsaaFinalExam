#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "../core/student.h"
#include <iostream>

using namespace std;

// ========== Cài đặt danh sách liên kết đôi ==========

// Định nghĩa cấu trúc node cho danh sách liên kết đôi
#ifndef NODE_DLL_DEFINED
#define NODE_DLL_DEFINED
struct NodeDLL
{
    Student info;
    NodeDLL *next;
    NodeDLL *prev;
};
#endif

// Function declarations
void initDLL(NodeDLL *&head, NodeDLL *&tail);
NodeDLL *createNodeDLL(const Student &student);
void addToHeadDLL(NodeDLL *&head, NodeDLL *&tail, const Student &student);
void addToTailDLL(NodeDLL *&head, NodeDLL *&tail, const Student &student);
bool deleteFromDLL(NodeDLL *&head, NodeDLL *&tail, const char *studentID);
NodeDLL *searchInDLL(NodeDLL *head, const char *studentID);
bool updateInDLL(NodeDLL *head, const Student &newInfo);
void displayDLL(NodeDLL *head);
void freeDLL(NodeDLL *&head, NodeDLL *&tail);

#endif // DOUBLY_LINKED_LIST_H