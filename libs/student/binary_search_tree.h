#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "student_struct.h"
#include "array_list.h" // Để sử dụng các hàm hiển thị bảng
#include <iostream>

using namespace std;

// ========== Cài đặt cây tìm kiếm nhị phân ==========
const int MAX_STUDENTS_PER_SCORE = 10; // Số lượng sinh viên tối đa cho mỗi điểm số

// Định nghĩa cấu trúc node cho cây BST
struct NodeBST
{
    float key;                                // Điểm số làm khóa
    Student students[MAX_STUDENTS_PER_SCORE]; // Danh sách sinh viên có điểm số này
    int count;                                // Số lượng sinh viên trong node này
    NodeBST *left;                            // Con trỏ tới node con bên trái
    NodeBST *right;                           // Con trỏ tới node con bên phải
};

// Khởi tạo cây BST rỗng
void initBST(NodeBST *&root)
{
    root = NULL;
}

// Tạo mới một node BST
NodeBST *createNodeBST(float score, const Student &student)
{
    NodeBST *newNode = new NodeBST;
    newNode->key = score;
    newNode->students[0] = student;
    newNode->count = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Thêm sinh viên vào cây BST
void insertToBST(NodeBST *&root, const Student &student)
{
    // Nếu cây rỗng, tạo node mới
    if (root == NULL)
    {
        root = createNodeBST(student.score, student);
        return;
    }

    // Nếu điểm số bằng nhau
    if (student.score == root->key)
    {
        // Kiểm tra nếu danh sách đã đầy
        if (root->count >= MAX_STUDENTS_PER_SCORE)
        {
            printWarning("Cây BST đã đạt giới hạn sinh viên cho điểm số này!");
            return;
        }

        // Thêm sinh viên vào node hiện tại
        root->students[root->count] = student;
        root->count++;
    }
    // Nếu điểm số nhỏ hơn, đi sang trái
    else if (student.score < root->key)
    {
        insertToBST(root->left, student);
    }
    // Nếu điểm số lớn hơn, đi sang phải
    else
    {
        insertToBST(root->right, student);
    }
}

// Hiển thị các sinh viên trong một node BST
void displayBSTNode(NodeBST *node)
{
    cout << BOLD << CYAN << "\n=== SINH VIÊN CÓ ĐIỂM " << node->key << " (" << node->count << " sinh viên) ===" << RESET << endl;

    displayStudentTableHeader();

    for (int i = 0; i < node->count; i++)
    {
        displayStudentInTable(node->students[i], i + 1);

        // Hiển thị dòng phân cách nếu không phải sinh viên cuối cùng
        if (i < node->count - 1)
        {
            displayStudentTableSeparator();
        }
    }

    displayStudentTableFooter();
}

// Duyệt cây BST theo thứ tự trước (Pre-order)
void preorderTraversalBST(NodeBST *root)
{
    if (root == NULL)
    {
        return;
    }

    displayBSTNode(root);
    preorderTraversalBST(root->left);
    preorderTraversalBST(root->right);
}

// Duyệt cây BST theo thứ tự giữa (In-order)
void inorderTraversalBST(NodeBST *root)
{
    if (root == NULL)
    {
        return;
    }

    inorderTraversalBST(root->left);
    displayBSTNode(root);
    inorderTraversalBST(root->right);
}

// Duyệt cây BST theo thứ tự sau (Post-order)
void postorderTraversalBST(NodeBST *root)
{
    if (root == NULL)
    {
        return;
    }

    postorderTraversalBST(root->left);
    postorderTraversalBST(root->right);
    displayBSTNode(root);
}

// Tìm kiếm sinh viên trong cây BST theo điểm số
NodeBST *searchInBST(NodeBST *root, float score)
{
    // Nếu cây rỗng hoặc tìm thấy điểm số
    if (root == NULL || root->key == score)
    {
        return root;
    }

    // Nếu điểm số nhỏ hơn node hiện tại, đi sang trái
    if (score < root->key)
    {
        return searchInBST(root->left, score);
    }

    // Nếu điểm số lớn hơn node hiện tại, đi sang phải
    return searchInBST(root->right, score);
}

// Tìm node với giá trị nhỏ nhất trong cây
NodeBST *findMinNode(NodeBST *root)
{
    NodeBST *current = root;

    // Luôn đi về bên trái để tìm giá trị nhỏ nhất
    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

// Hiển thị cây BST theo cách trực quan
void displayBSTTree(NodeBST *root, int level = 0, char branch = ' ')
{
    if (root == NULL)
    {
        return;
    }

    displayBSTTree(root->right, level + 1, '/');

    for (int i = 0; i < level; i++)
    {
        cout << "   ";
    }

    if (level > 0)
    {
        cout << YELLOW << " " << branch << "──" << RESET;
    }

    // Màu sắc cho điểm số dựa trên giá trị
    if (root->key >= 8.0)
    {
        cout << GREEN << root->key << " (" << root->count << ")" << RESET << endl;
    }
    else if (root->key >= 6.5)
    {
        cout << BLUE << root->key << " (" << root->count << ")" << RESET << endl;
    }
    else if (root->key >= 5.0)
    {
        cout << YELLOW << root->key << " (" << root->count << ")" << RESET << endl;
    }
    else
    {
        cout << RED << root->key << " (" << root->count << ")" << RESET << endl;
    }

    displayBSTTree(root->left, level + 1, '\\');
}

// Giải phóng bộ nhớ cây BST
void freeBST(NodeBST *&root)
{
    if (root == NULL)
    {
        return;
    }

    // Giải phóng các node con trước
    freeBST(root->left);
    freeBST(root->right);

    // Giải phóng node hiện tại
    delete root;
    root = NULL;
}

#endif // BINARY_SEARCH_TREE_H