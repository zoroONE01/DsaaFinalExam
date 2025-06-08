#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include "../core/student.h"
#include "singly_linked_list.h" // Reuse NodeSLL structure
#include <iostream>

using namespace std;

// ========== Cài đặt danh sách liên kết vòng ==========
// Note: Circular linked list uses the same NodeSLL structure

// Function declarations
void initCLL(NodeSLL *&head);
void addToCLL(NodeSLL *&head, const Student &student);
bool deleteFromCLL(NodeSLL *&head, const char *studentID);
NodeSLL *searchInCLL(NodeSLL *head, const char *studentID);
bool updateInCLL(NodeSLL *head, const Student &newInfo);
void displayCLL(NodeSLL *head);
void freeCLL(NodeSLL *&head);
float findHighestScoreCLL(NodeSLL *head);
float findLowestScoreCLL(NodeSLL *head);
float calculateAverageScoreCLL(NodeSLL *head);

#endif // CIRCULAR_LINKED_LIST_H