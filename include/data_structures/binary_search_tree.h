#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "../utils/student.h"
#include "../utils/constants.h"

// Cấu trúc nút của cây nhị phân tìm kiếm
// Mỗi nút lưu một điểm số và danh sách sinh viên có điểm số đó
struct NodeBST {
    float key;                              // Điểm số làm khóa
    Student studentsWithScore[MAX_STUDENTS_PER_SCORE]; // Mảng sinh viên có cùng điểm số
    int count;                              // Số lượng sinh viên có điểm số này
    struct NodeBST *left;                   // Con trỏ tới nút con bên trái
    struct NodeBST *right;                  // Con trỏ tới nút con bên phải
};

// Khởi tạo nút BST mới với điểm số và sinh viên đầu tiên
NodeBST* createNode(float score, Student student);

// Thêm một sinh viên vào cây BST
// Nếu điểm số đã tồn tại, thêm sinh viên vào danh sách của điểm số đó
// Nếu điểm số chưa tồn tại, tạo nút mới
void insertStudentBST(NodeBST* &root, Student student);

// Tìm kiếm sinh viên theo điểm số trong cây BST
NodeBST* searchByScore(NodeBST* root, float score);

// Hiển thị tất cả sinh viên theo thứ tự tăng dần của điểm số (duyệt inorder)
void inorderTraversal(NodeBST* root);

// Hiển thị tất cả sinh viên theo thứ tự giảm dần của điểm số (duyệt inorder ngược)
void reverseInorderTraversal(NodeBST* root);

// Tìm nút có giá trị nhỏ nhất trong cây con
NodeBST* findMinNode(NodeBST* node);

// Xóa một nút có điểm số xác định khỏi cây BST
NodeBST* deleteNode(NodeBST* root, float score);

// Giải phóng toàn bộ bộ nhớ được cấp phát cho cây BST
void freeBST(NodeBST* root);

// Đếm tổng số sinh viên trong cây BST
int countStudentsInBST(NodeBST* root);

// Tìm điểm số cao nhất trong cây BST
float findMaxScore(NodeBST* root);

// Tìm điểm số thấp nhất trong cây BST
float findMinScore(NodeBST* root);

// Tính điểm trung bình của tất cả sinh viên trong cây BST
float calculateAverageScore(NodeBST* root);

#endif // BINARY_SEARCH_TREE_H