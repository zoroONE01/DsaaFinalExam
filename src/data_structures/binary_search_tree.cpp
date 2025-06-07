#include "../../include/data_structures/binary_search_tree.h"
#include "../../include/ui/common_ui.h"
#include <iostream>
#include <chrono>
#include <cstring>

using namespace std;

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

// Kiểm tra sinh viên tồn tại trong cây BST theo mã sinh viên
bool isStudentExistsInBST(NodeBST *root, const char *studentID)
{
    if (root == NULL)
    {
        return false;
    }

    // Kiểm tra trong node hiện tại
    for (int i = 0; i < root->count; i++)
    {
        if (strcmp(root->students[i].studentID, studentID) == 0)
        {
            return true; // Tìm thấy mã sinh viên trùng lặp
        }
    }

    // Tìm kiếm đệ quy trong cây con trái và phải
    return isStudentExistsInBST(root->left, studentID) || isStudentExistsInBST(root->right, studentID);
}

// Thêm sinh viên vào cây BST
void insertToBST(NodeBST *&root, const Student &student)
{
    // Kiểm tra tính hợp lệ của dữ liệu sinh viên trước khi thêm
    if (strlen(student.studentID) == 0)
    {
        printError("Mã sinh viên không được để trống!");
        return;
    }

    if (student.score < MIN_SCORE || student.score > MAX_SCORE)
    {
        printError("Điểm số không hợp lệ! Điểm phải trong khoảng 0-10.");
        return;
    }

    // Kiểm tra mã sinh viên trùng lặp trước khi thêm
    if (isStudentExistsInBST(root, student.studentID))
    {
        printError("Mã sinh viên đã tồn tại trong cây BST!");
        return;
    }

    // Nếu cây rỗng, tạo node mới
    if (root == NULL)
    {
        root = createNodeBST(student.score, student);
        printSuccess("Đã thêm sinh viên thành công vào cây BST!");
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
        printSuccess("Đã thêm sinh viên thành công vào cây BST!");
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
void displayBSTTree(NodeBST *root, int level, char branch)
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

// Xóa node trong cây BST theo key (điểm số)
NodeBST *deleteFromBST(NodeBST *&root, float key)
{
    // Nếu cây rỗng
    if (root == NULL)
    {
        printWarning("Không tìm thấy node có điểm số cần xóa!");
        return root;
    }

    // Nếu key nhỏ hơn key của node hiện tại, đi sang trái
    if (key < root->key)
    {
        root->left = deleteFromBST(root->left, key);
    }
    // Nếu key lớn hơn key của node hiện tại, đi sang phải
    else if (key > root->key)
    {
        root->right = deleteFromBST(root->right, key);
    }
    // Nếu tìm thấy node cần xóa
    else
    {
        cout << GREEN << "✅ Đã tìm thấy và xóa node có điểm số " << key << " khỏi cây BST!" << RESET << endl;

        // Trường hợp 1: Node là lá (không có con)
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }
        // Trường hợp 2: Node có một con
        else if (root->left == NULL)
        {
            NodeBST *temp = root;
            root = root->right;
            delete temp;
            return root;
        }
        else if (root->right == NULL)
        {
            NodeBST *temp = root;
            root = root->left;
            delete temp;
            return root;
        }
        // Trường hợp 3: Node có hai con
        else
        {
            // Tìm node nhỏ nhất trong cây con phải (successor)
            NodeBST *minNode = findMinNode(root->right);

            // Sao chép dữ liệu từ successor vào node hiện tại
            root->key = minNode->key;
            for (int i = 0; i < minNode->count; i++)
            {
                root->students[i] = minNode->students[i];
            }
            root->count = minNode->count;

            // Xóa successor
            root->right = deleteFromBST(root->right, minNode->key);
        }
    }
    return root;
}

// Duyệt cây BST theo thứ tự giữa (In-order) với đo thời gian
void inorderTraversalBSTWithTimer(NodeBST *root)
{
    cout << BOLD << BLUE << "\n=== DUYỆT CÂY BST THEO THỨ TỰ GIỮA (IN-ORDER) - CÓ ĐO THỜI GIAN ===" << RESET << endl;

    // Bắt đầu đo thời gian
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

    if (root == NULL)
    {
        printWarning("Cây BST rỗng!");
    }
    else
    {
        cout << CYAN << "Kết quả duyệt cây theo thứ tự tăng dần (điểm số):" << RESET << endl;
        inorderTraversalBST(root);
    }

    // Kết thúc đo thời gian
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << BOLD << GREEN << "\n⏱️  Thời gian thực hiện: "
         << duration.count() << " microseconds ("
         << duration.count() / 1000.0 << " ms)" << RESET << endl;
}

// Duyệt cây BST theo thứ tự trước (Pre-order) với đo thời gian
void preorderTraversalBSTWithTimer(NodeBST *root)
{
    cout << BOLD << BLUE << "\n=== DUYỆT CÂY BST THEO THỨ TỰ TRƯỚC (PRE-ORDER) - CÓ ĐO THỜI GIAN ===" << RESET << endl;

    // Bắt đầu đo thời gian
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

    if (root == NULL)
    {
        printWarning("Cây BST rỗng!");
    }
    else
    {
        cout << CYAN << "Kết quả duyệt cây theo thứ tự trước:" << RESET << endl;
        preorderTraversalBST(root);
    }

    // Kết thúc đo thời gian
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << BOLD << GREEN << "\n⏱️  Thời gian thực hiện: "
         << duration.count() << " microseconds ("
         << duration.count() / 1000.0 << " ms)" << RESET << endl;
}

// Duyệt cây BST theo thứ tự sau (Post-order) với đo thời gian
void postorderTraversalBSTWithTimer(NodeBST *root)
{
    cout << BOLD << BLUE << "\n=== DUYỆT CÂY BST THEO THỨ TỰ SAU (POST-ORDER) - CÓ ĐO THỜI GIAN ===" << RESET << endl;

    // Bắt đầu đo thời gian
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

    if (root == NULL)
    {
        printWarning("Cây BST rỗng!");
    }
    else
    {
        cout << CYAN << "Kết quả duyệt cây theo thứ tự sau:" << RESET << endl;
        postorderTraversalBST(root);
    }

    // Kết thúc đo thời gian
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << BOLD << GREEN << "\n⏱️  Thời gian thực hiện: "
         << duration.count() << " microseconds ("
         << duration.count() / 1000.0 << " ms)" << RESET << endl;
}
