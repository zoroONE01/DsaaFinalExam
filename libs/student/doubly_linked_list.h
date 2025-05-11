#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "student_struct.h"
#include <iostream>

using namespace std;

// ========== Cài đặt danh sách liên kết đôi ==========
// Định nghĩa cấu trúc node cho danh sách liên kết đôi
struct NodeDLL {
    Student info;
    NodeDLL* prev;
    NodeDLL* next;
};

// Khởi tạo danh sách liên kết đôi rỗng
void initDLL(NodeDLL* &head, NodeDLL* &tail) {
    head = NULL;
    tail = NULL;
}

// Tạo mới một node sinh viên cho danh sách liên kết đôi
NodeDLL* createNodeDLL(const Student &student) {
    NodeDLL* newNode = new NodeDLL;
    newNode->info = student;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Thêm sinh viên vào đầu danh sách liên kết đôi
void addToHeadDLL(NodeDLL* &head, NodeDLL* &tail, const Student &student) {
    NodeDLL* newNode = createNodeDLL(student);
    
    // Nếu danh sách rỗng
    if (head == NULL) {
        head = newNode;
        tail = newNode;
        return;
    }
    
    // Thêm vào đầu danh sách
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

// Thêm sinh viên vào cuối danh sách liên kết đôi
void addToTailDLL(NodeDLL* &head, NodeDLL* &tail, const Student &student) {
    NodeDLL* newNode = createNodeDLL(student);
    
    // Nếu danh sách rỗng
    if (head == NULL) {
        head = newNode;
        tail = newNode;
        return;
    }
    
    // Thêm vào cuối danh sách
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
}

// Xóa sinh viên theo mã sinh viên trong danh sách liên kết đôi
bool deleteFromDLL(NodeDLL* &head, NodeDLL* &tail, const char* studentID) {
    // Nếu danh sách rỗng
    if (head == NULL) {
        return false;
    }
    
    // Nếu sinh viên cần xóa là head
    if (strcmp(head->info.studentID, studentID) == 0) {
        NodeDLL* temp = head;
        
        // Nếu chỉ có một node
        if (head == tail) {
            head = NULL;
            tail = NULL;
        } else {
            head = head->next;
            head->prev = NULL;
        }
        
        delete temp;
        return true;
    }
    
    // Nếu sinh viên cần xóa là tail
    if (strcmp(tail->info.studentID, studentID) == 0) {
        NodeDLL* temp = tail;
        tail = tail->prev;
        tail->next = NULL;
        delete temp;
        return true;
    }
    
    // Tìm node cần xóa
    NodeDLL* current = head->next;
    while (current != NULL && strcmp(current->info.studentID, studentID) != 0) {
        current = current->next;
    }
    
    // Nếu không tìm thấy sinh viên
    if (current == NULL) {
        return false;
    }
    
    // Xóa node
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    return true;
}

// Cập nhật sinh viên theo mã sinh viên trong danh sách liên kết đôi
bool updateInDLL(NodeDLL* head, const Student &student) {
    NodeDLL* current = head;
    while (current != NULL) {
        if (strcmp(current->info.studentID, student.studentID) == 0) {
            current->info = student;
            return true;
        }
        current = current->next;
    }
    
    return false;  // Không tìm thấy sinh viên
}

// Tìm kiếm sinh viên theo mã sinh viên trong danh sách liên kết đôi
NodeDLL* searchInDLL(NodeDLL* head, const char* studentID) {
    NodeDLL* current = head;
    while (current != NULL) {
        if (strcmp(current->info.studentID, studentID) == 0) {
            return current;  // Trả về node tìm thấy
        }
        current = current->next;
    }
    
    return NULL;  // Không tìm thấy sinh viên
}

// Hiển thị danh sách sinh viên từ danh sách liên kết đôi
void displayDLL(NodeDLL* head) {
    if (head == NULL) {
        cout << "Danh sách sinh viên rỗng!\n";
        return;
    }
    
    cout << "Danh sách sinh viên:\n";
    cout << "---------------------------------------------------\n";
    int count = 0;
    NodeDLL* current = head;
    while (current != NULL) {
        count++;
        cout << "Sinh viên thứ " << count << ":\n";
        displayStudent(current->info);
        cout << "---------------------------------------------------\n";
        current = current->next;
    }
}

// Giải phóng bộ nhớ danh sách liên kết đôi
void freeDLL(NodeDLL* &head, NodeDLL* &tail) {
    while (head != NULL) {
        NodeDLL* temp = head;
        head = head->next;
        delete temp;
    }
    tail = NULL;
}

// --- MergeSort cho danh sách liên kết đôi ---
// Hàm tách một node khỏi danh sách liên kết đôi
void splitDLL(NodeDLL* head, NodeDLL** firstHalf, NodeDLL** secondHalf) {
    NodeDLL* slow = head;
    NodeDLL* fast = head->next;
    
    // 'fast' di chuyển hai bước, 'slow' di chuyển một bước
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    
    // 'slow' hiện là ở giữa danh sách
    // Chia danh sách thành hai phần
    *firstHalf = head;
    *secondHalf = slow->next;
    (*secondHalf)->prev = NULL;  // Cập nhật con trỏ prev của nửa thứ hai
    slow->next = NULL;  // Ngắt liên kết giữa hai nửa
}

// Hợp nhất hai danh sách liên kết đôi đã sắp xếp
NodeDLL* mergeDLL(NodeDLL* firstHalf, NodeDLL* secondHalf) {
    // Nếu một trong hai nửa rỗng
    if (firstHalf == NULL) {
        return secondHalf;
    }
    if (secondHalf == NULL) {
        return firstHalf;
    }
    
    // Chọn node nhỏ hơn làm đầu danh sách kết quả
    NodeDLL* result = NULL;
    
    if (firstHalf->info.score <= secondHalf->info.score) {
        result = firstHalf;
        result->next = mergeDLL(firstHalf->next, secondHalf);
        if (result->next != NULL) {
            result->next->prev = result;
        }
    } else {
        result = secondHalf;
        result->next = mergeDLL(firstHalf, secondHalf->next);
        if (result->next != NULL) {
            result->next->prev = result;
        }
    }
    
    return result;
}

// Thuật toán MergeSort cho danh sách liên kết đôi
void mergeSortDLL(NodeDLL** headRef) {
    NodeDLL* head = *headRef;
    NodeDLL* firstHalf;
    NodeDLL* secondHalf;
    
    // Trường hợp cơ bản
    if (head == NULL || head->next == NULL) {
        return;
    }
    
    // Chia danh sách thành hai nửa
    splitDLL(head, &firstHalf, &secondHalf);
    
    // Sắp xếp đệ quy hai nửa
    mergeSortDLL(&firstHalf);
    mergeSortDLL(&secondHalf);
    
    // Hợp nhất hai nửa đã sắp xếp
    *headRef = mergeDLL(firstHalf, secondHalf);
}

#endif // DOUBLY_LINKED_LIST_H