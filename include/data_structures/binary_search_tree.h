#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "../core/student.h"
#include "../utils/constants.h"
#include <iostream>

using namespace std;

// ========== Cài đặt cây tìm kiếm nhị phân ==========

const int MAX_STUDENTS_PER_SCORE = 10; // Số lượng sinh viên tối đa cho mỗi điểm số

// Định nghĩa cấu trúc node cho cây BST
#ifndef NODE_BST_DEFINED
#define NODE_BST_DEFINED
struct NodeBST
{
    float key;                                // Điểm số làm khóa
    Student students[MAX_STUDENTS_PER_SCORE]; // Danh sách sinh viên có điểm số này
    int count;                                // Số lượng sinh viên trong node này
    NodeBST *left;                            // Con trỏ tới node con bên trái
    NodeBST *right;                           // Con trỏ tới node con bên phải
};
#endif

// Function declarations
void initBST(NodeBST *&root);
NodeBST *createNodeBST(float score, const Student &student);
bool isStudentExistsInBST(NodeBST *root, const char *studentID);
void insertToBST(NodeBST *&root, const Student &student);
NodeBST *deleteFromBST(NodeBST *&root, float key);
NodeBST *searchInBST(NodeBST *root, float score);
NodeBST *findMinNode(NodeBST *root);
void inorderTraversalBST(NodeBST *root);
void preorderTraversalBST(NodeBST *root);
void postorderTraversalBST(NodeBST *root);
void inorderTraversalBSTWithTimer(NodeBST *root);
void preorderTraversalBSTWithTimer(NodeBST *root);
void postorderTraversalBSTWithTimer(NodeBST *root);
void displayBSTTree(NodeBST *root, int level = 0, char branch = ' ');
void displayBSTNode(NodeBST *node);
void freeBST(NodeBST *&root);

#endif // BINARY_SEARCH_TREE_H