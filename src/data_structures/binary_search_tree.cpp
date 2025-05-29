#include "../../include/data_structures/binary_search_tree.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Khởi tạo nút BST mới với điểm số và sinh viên đầu tiên
NodeBST *createNode(float score, Student student)
{
    NodeBST *newNode = new NodeBST;
    newNode->key = score;
    newNode->count = 1;
    newNode->studentsWithScore[0] = student;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Thêm một sinh viên vào cây BST
void insertStudentBST(NodeBST *&root, Student student)
{
    // Nếu cây rỗng, tạo nút gốc mới
    if (root == NULL)
    {
        root = createNode(student.score, student);
        return;
    }

    // Nếu điểm số bằng với điểm số ở nút hiện tại
    if (student.score == root->key)
    {
        // Kiểm tra nếu danh sách sinh viên chưa đầy
        if (root->count < MAX_STUDENTS_PER_SCORE)
        {
            root->studentsWithScore[root->count] = student;
            root->count++;
        }
        else
        {
            cout << "Danh sách sinh viên có điểm " << student.score << " đã đầy!" << endl;
        }
    }
    // Nếu điểm số nhỏ hơn, đi sang nút con trái
    else if (student.score < root->key)
    {
        insertStudentBST(root->left, student);
    }
    // Nếu điểm số lớn hơn, đi sang nút con phải
    else
    {
        insertStudentBST(root->right, student);
    }
}

// Tìm kiếm sinh viên theo điểm số trong cây BST
NodeBST *searchByScore(NodeBST *root, float score)
{
    // Nếu cây rỗng hoặc tìm thấy nút có điểm số cần tìm
    if (root == NULL || root->key == score)
    {
        return root;
    }

    // Nếu điểm số nhỏ hơn giá trị nút hiện tại, tìm kiếm ở cây con trái
    if (score < root->key)
    {
        return searchByScore(root->left, score);
    }

    // Nếu điểm số lớn hơn giá trị nút hiện tại, tìm kiếm ở cây con phải
    return searchByScore(root->right, score);
}

// Hiển thị thông tin một sinh viên
void displayStudent(Student student)
{
    cout << left << setw(10) << student.studentID
         << setw(20) << student.firstName
         << setw(20) << student.lastName
         << setw(15) << student.studentClass
         << setw(5) << student.score << endl;
}

// Hiển thị tất cả sinh viên trong một nút BST
void displayNodeStudents(NodeBST *node)
{
    if (node != NULL)
    {
        cout << "\nDanh sách sinh viên có điểm " << node->key << ":" << endl;
        cout << left << setw(10) << "Mã SV"
             << setw(20) << "Họ"
             << setw(20) << "Tên"
             << setw(15) << "Lớp"
             << setw(5) << "Điểm" << endl;
        cout << string(70, '-') << endl;

        for (int i = 0; i < node->count; i++)
        {
            displayStudent(node->studentsWithScore[i]);
        }
    }
}

// Hiển thị tất cả sinh viên theo thứ tự tăng dần của điểm số (duyệt inorder)
void inorderTraversal(NodeBST *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        displayNodeStudents(root);
        inorderTraversal(root->right);
    }
}

// Hiển thị tất cả sinh viên theo thứ tự giảm dần của điểm số (duyệt inorder ngược)
void reverseInorderTraversal(NodeBST *root)
{
    if (root != NULL)
    {
        reverseInorderTraversal(root->right);
        displayNodeStudents(root);
        reverseInorderTraversal(root->left);
    }
}

// Tìm nút có giá trị nhỏ nhất trong cây con
NodeBST *findMinNode(NodeBST *node)
{
    NodeBST *current = node;

    // Đi xuống theo các nút con bên trái
    while (current && current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

// Xóa một nút có điểm số xác định khỏi cây BST
NodeBST *deleteNode(NodeBST *root, float score)
{
    if (root == NULL)
    {
        return root;
    }

    // Nếu điểm số nhỏ hơn giá trị nút hiện tại, đi xuống nút con trái
    if (score < root->key)
    {
        root->left = deleteNode(root->left, score);
    }
    // Nếu điểm số lớn hơn giá trị nút hiện tại, đi xuống nút con phải
    else if (score > root->key)
    {
        root->right = deleteNode(root->right, score);
    }
    // Nếu điểm số bằng giá trị nút hiện tại, đây là nút cần xóa
    else
    {
        // Trường hợp 1: Nút không có con hoặc chỉ có một con
        if (root->left == NULL)
        {
            NodeBST *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            NodeBST *temp = root->left;
            delete root;
            return temp;
        }

        // Trường hợp 2: Nút có hai con
        // Tìm phần tử kế nhiệm trong cây con bên phải (phần tử nhỏ nhất)
        NodeBST *temp = findMinNode(root->right);

        // Sao chép dữ liệu từ phần tử kế nhiệm
        root->key = temp->key;
        for (int i = 0; i < temp->count; i++)
        {
            root->studentsWithScore[i] = temp->studentsWithScore[i];
        }
        root->count = temp->count;

        // Xóa phần tử kế nhiệm
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

// Giải phóng toàn bộ bộ nhớ được cấp phát cho cây BST
void freeBST(NodeBST *root)
{
    if (root != NULL)
    {
        freeBST(root->left);
        freeBST(root->right);
        delete root;
    }
}

// Hàm đệ quy để đếm số sinh viên trong BST
int countStudentsInBST(NodeBST *root)
{
    if (root == NULL)
    {
        return 0;
    }

    return root->count + countStudentsInBST(root->left) + countStudentsInBST(root->right);
}

// Tìm điểm số cao nhất trong cây BST
float findMaxScore(NodeBST *root)
{
    if (root == NULL)
    {
        return -1; // Giá trị đặc biệt để chỉ ra cây rỗng
    }

    // Điểm cao nhất sẽ là nút ngoài cùng bên phải
    while (root->right != NULL)
    {
        root = root->right;
    }

    return root->key;
}

// Tìm điểm số thấp nhất trong cây BST
float findMinScore(NodeBST *root)
{
    if (root == NULL)
    {
        return -1; // Giá trị đặc biệt để chỉ ra cây rỗng
    }

    // Điểm thấp nhất sẽ là nút ngoài cùng bên trái
    while (root->left != NULL)
    {
        root = root->left;
    }

    return root->key;
}

// Hàm đệ quy để tính tổng điểm của tất cả sinh viên trong BST
float sumScores(NodeBST *root, int &totalStudents)
{
    if (root == NULL)
    {
        return 0;
    }

    float sum = root->key * root->count; // Điểm số * số sinh viên có điểm số này
    totalStudents += root->count;

    return sum + sumScores(root->left, totalStudents) + sumScores(root->right, totalStudents);
}

// Tính điểm trung bình của tất cả sinh viên trong cây BST
float calculateAverageScore(NodeBST *root)
{
    int totalStudents = 0;
    float totalScore = sumScores(root, totalStudents);

    if (totalStudents == 0)
    {
        return 0;
    }

    return totalScore / totalStudents;
}