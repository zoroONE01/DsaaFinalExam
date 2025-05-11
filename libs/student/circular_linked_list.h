#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include "student_struct.h"
#include "singly_linked_list.h" // Để sử dụng struct NodeSLL và một số hàm chung
#include <iostream>

using namespace std;

// ========== Cài đặt danh sách liên kết vòng ==========
// Danh sách liên kết vòng sử dụng cùng cấu trúc node với danh sách liên kết đơn (NodeSLL)

// Khởi tạo danh sách liên kết vòng rỗng
void initCLL(NodeSLL* &head) {
    head = NULL;
}

// Thêm sinh viên vào danh sách liên kết vòng
void addToCLL(NodeSLL* &head, const Student &student) {
    NodeSLL* newNode = createNode(student);
    
    // Nếu danh sách rỗng
    if (head == NULL) {
        head = newNode;
        head->next = head;  // Trỏ vào chính nó để tạo vòng tròn
        return;
    }
    
    // Tìm node cuối cùng
    NodeSLL* current = head;
    while (current->next != head) {
        current = current->next;
    }
    
    // Thêm node mới vào sau node cuối cùng
    current->next = newNode;
    newNode->next = head;
}

// Xóa sinh viên theo mã sinh viên trong danh sách liên kết vòng
bool deleteFromCLL(NodeSLL* &head, const char* studentID) {
    // Nếu danh sách rỗng
    if (head == NULL) {
        return false;
    }
    
    // Nếu chỉ có một node
    if (head->next == head) {
        if (strcmp(head->info.studentID, studentID) == 0) {
            delete head;
            head = NULL;
            return true;
        }
        return false;
    }
    
    // Nếu sinh viên cần xóa là head
    if (strcmp(head->info.studentID, studentID) == 0) {
        // Tìm node cuối cùng
        NodeSLL* last = head;
        while (last->next != head) {
            last = last->next;
        }
        
        // Cập nhật head và xóa node cũ
        NodeSLL* temp = head;
        head = head->next;
        last->next = head;  // Cập nhật liên kết vòng
        delete temp;
        return true;
    }
    
    // Tìm node trước node cần xóa
    NodeSLL* current = head;
    while (current->next != head && strcmp(current->next->info.studentID, studentID) != 0) {
        current = current->next;
    }
    
    // Nếu không tìm thấy sinh viên
    if (current->next == head) {
        return false;
    }
    
    // Xóa node
    NodeSLL* temp = current->next;
    current->next = current->next->next;
    delete temp;
    return true;
}

// Cập nhật sinh viên theo mã sinh viên trong danh sách liên kết vòng
bool updateInCLL(NodeSLL* head, const Student &student) {
    if (head == NULL) {
        return false;
    }
    
    // Kiểm tra node đầu tiên
    if (strcmp(head->info.studentID, student.studentID) == 0) {
        head->info = student;
        return true;
    }
    
    // Kiểm tra các node còn lại
    NodeSLL* current = head->next;
    while (current != head) {
        if (strcmp(current->info.studentID, student.studentID) == 0) {
            current->info = student;
            return true;
        }
        current = current->next;
    }
    
    return false;  // Không tìm thấy sinh viên
}

// Tìm kiếm sinh viên theo mã sinh viên trong danh sách liên kết vòng
NodeSLL* searchInCLL(NodeSLL* head, const char* studentID) {
    if (head == NULL) {
        return NULL;
    }
    
    // Kiểm tra node đầu tiên
    if (strcmp(head->info.studentID, studentID) == 0) {
        return head;
    }
    
    // Kiểm tra các node còn lại
    NodeSLL* current = head->next;
    while (current != head) {
        if (strcmp(current->info.studentID, studentID) == 0) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;  // Không tìm thấy sinh viên
}

// Hiển thị danh sách sinh viên từ danh sách liên kết vòng
void displayCLL(NodeSLL* head) {
    if (head == NULL) {
        cout << "Danh sách sinh viên rỗng!\n";
        return;
    }
    
    cout << "Danh sách sinh viên:\n";
    cout << "---------------------------------------------------\n";
    int count = 0;
    NodeSLL* current = head;
    do {
        count++;
        cout << "Sinh viên thứ " << count << ":\n";
        displayStudent(current->info);
        cout << "---------------------------------------------------\n";
        current = current->next;
    } while (current != head);
}

// Giải phóng bộ nhớ danh sách liên kết vòng
void freeCLL(NodeSLL* &head) {
    if (head == NULL) {
        return;
    }
    
    NodeSLL* current = head->next;
    NodeSLL* temp;
    
    while (current != head) {
        temp = current;
        current = current->next;
        delete temp;
    }
    
    delete head;
    head = NULL;
}

#endif // CIRCULAR_LINKED_LIST_H