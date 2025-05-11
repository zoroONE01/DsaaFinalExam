#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "student_struct.h"
#include "array_list.h" // Để sử dụng hằng số MAX_STUDENTS
#include <iostream>

using namespace std;

// ========== Phần Mở Rộng: Cài đặt Cây Tìm Kiếm Nhị Phân (BST) ==========

// Định nghĩa cấu trúc node cho cây BST
struct NodeBST {
    float key;  // Điểm số làm khóa
    Student students[MAX_STUDENTS];  // Danh sách các sinh viên có cùng điểm số
    int count;  // Số lượng sinh viên có cùng điểm số
    NodeBST* left;
    NodeBST* right;
};

// Khởi tạo cây BST rỗng
void initBST(NodeBST* &root) {
    root = NULL;
}

// Tạo mới một node BST
NodeBST* createNodeBST(const Student &student) {
    NodeBST* newNode = new NodeBST;
    newNode->key = student.score;
    newNode->students[0] = student;
    newNode->count = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Thêm sinh viên vào cây BST
void insertToBST(NodeBST* &root, const Student &student) {
    // Nếu cây rỗng, tạo node gốc mới
    if (root == NULL) {
        root = createNodeBST(student);
        return;
    }
    
    // Nếu điểm số bằng với node hiện tại, thêm sinh viên vào danh sách
    if (student.score == root->key) {
        if (root->count < MAX_STUDENTS) {
            root->students[root->count] = student;
            root->count++;
        }
        // Nếu danh sách đầy, có thể xử lý bằng cách mở rộng hoặc báo lỗi
        return;
    }
    
    // Nếu điểm số nhỏ hơn, đi tới cây con bên trái
    if (student.score < root->key) {
        insertToBST(root->left, student);
    }
    // Nếu điểm số lớn hơn, đi tới cây con bên phải
    else {
        insertToBST(root->right, student);
    }
}

// Tìm node BST với điểm số cần tìm
NodeBST* searchBST(NodeBST* root, float score) {
    // Nếu cây rỗng hoặc tìm thấy điểm số
    if (root == NULL || root->key == score) {
        return root;
    }
    
    // Nếu điểm số nhỏ hơn node hiện tại, tìm trong cây con trái
    if (score < root->key) {
        return searchBST(root->left, score);
    }
    
    // Nếu điểm số lớn hơn node hiện tại, tìm trong cây con phải
    return searchBST(root->right, score);
}

// Tìm node có giá trị nhỏ nhất trong cây BST
NodeBST* findMinBST(NodeBST* root) {
    if (root == NULL) {
        return NULL;
    }
    
    NodeBST* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    
    return current;
}

// Xóa node khỏi cây BST
NodeBST* deleteFromBST(NodeBST* root, float score) {
    // Trường hợp cơ bản: cây rỗng
    if (root == NULL) {
        return NULL;
    }
    
    // Tìm node cần xóa
    if (score < root->key) {
        root->left = deleteFromBST(root->left, score);
    } else if (score > root->key) {
        root->right = deleteFromBST(root->right, score);
    } else {
        // Node với chỉ một hoặc không có con
        if (root->left == NULL) {
            NodeBST* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            NodeBST* temp = root->left;
            delete root;
            return temp;
        }
        
        // Node với hai con: tìm node kế tiếp theo thứ tự (successor)
        NodeBST* temp = findMinBST(root->right);
        
        // Sao chép nội dung của node kế tiếp vào node hiện tại
        root->key = temp->key;
        for (int i = 0; i < temp->count; i++) {
            root->students[i] = temp->students[i];
        }
        root->count = temp->count;
        
        // Xóa node kế tiếp
        root->right = deleteFromBST(root->right, temp->key);
    }
    
    return root;
}

// Duyệt cây BST theo thứ tự trung tố (Inorder)
void inorderTraversalBST(NodeBST* root) {
    if (root == NULL) {
        return;
    }
    
    // Duyệt cây con trái
    inorderTraversalBST(root->left);
    
    // Xử lý node hiện tại
    cout << "Điểm số: " << root->key << " - Số lượng sinh viên: " << root->count << "\n";
    for (int i = 0; i < root->count; i++) {
        displayStudent(root->students[i]);
        cout << "---\n";
    }
    
    // Duyệt cây con phải
    inorderTraversalBST(root->right);
}

// Giải phóng bộ nhớ cây BST
void freeBST(NodeBST* &root) {
    if (root == NULL) {
        return;
    }
    
    // Giải phóng các cây con
    freeBST(root->left);
    freeBST(root->right);
    
    // Giải phóng node hiện tại
    delete root;
    root = NULL;
}

#endif // BINARY_SEARCH_TREE_H