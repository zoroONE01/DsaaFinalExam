#include "../../include/algorithms/student_search.h"
#include "../../include/utils/constants.h"
#include "../../include/ui/common_ui.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <chrono>
#include <iomanip>

using namespace std;

// ========== HÀM TIỆN ÍCH TÌM KIẾM ==========

/**
 * @brief So sánh chuỗi không phân biệt hoa thường
 */
bool compareStringsIgnoreCase(const char* str1, const char* str2) {
    if (!str1 || !str2) return false;
    
    while (*str1 && *str2) {
        if (tolower(*str1) != tolower(*str2)) {
            return false;
        }
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

/**
 * @brief Kiểm tra chuỗi con (không phân biệt hoa thường)
 */
bool containsSubstring(const char* str, const char* substring) {
    if (!str || !substring) return false;
    if (strlen(substring) == 0) return true;
    
    int strLen = strlen(str);
    int subLen = strlen(substring);
    
    for (int i = 0; i <= strLen - subLen; i++) {
        bool match = true;
        for (int j = 0; j < subLen; j++) {
            if (tolower(str[i + j]) != tolower(substring[j])) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

/**
 * @brief Kiểm tra sinh viên có khớp với tiêu chí tìm kiếm không
 */
bool studentMatchesCriteria(const Student& student, const char* keyword, int searchCriteria) {
    if (!keyword || strlen(keyword) == 0) return true;
    
    switch (searchCriteria) {
        case SEARCH_BY_STUDENT_ID:
            return containsSubstring(student.studentID, keyword);
        case SEARCH_BY_FIRST_NAME:
            return containsSubstring(student.firstName, keyword);
        case SEARCH_BY_LAST_NAME:
            return containsSubstring(student.lastName, keyword);
        case SEARCH_BY_CLASS:
            return containsSubstring(student.studentClass, keyword);
        case SEARCH_BY_SCORE: {
            float searchScore = atof(keyword);
            return (student.score >= searchScore - 0.01 && student.score <= searchScore + 0.01);
        }
        default:
            return false;
    }
}

/**
 * @brief Đảo ngược họ và tên đầy đủ
 */
char* reverseFullName(const char* firstName, const char* lastName) {
    if (!firstName || !lastName) return nullptr;
    
    // Tạo chuỗi họ tên đầy đủ: "Họ Tên"
    int totalLen = strlen(lastName) + strlen(firstName) + 2; // +2 cho dấu cách và null terminator
    char* fullName = new char[totalLen];
    strcpy(fullName, lastName);
    strcat(fullName, " ");
    strcat(fullName, firstName);
    
    // Đảo ngược toàn bộ chuỗi
    int len = strlen(fullName);
    char* reversed = new char[len + 1];
    
    for (int i = 0; i < len; i++) {
        reversed[i] = fullName[len - 1 - i];
    }
    reversed[len] = '\0';
    
    delete[] fullName;
    return reversed;
}

// ========== HÀM ĐO THỜI GIAN ==========

SearchTimer startTimer() {
    SearchTimer timer;
    chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
    timer.startTime = chrono::duration_cast<chrono::microseconds>(now.time_since_epoch()).count();
    timer.endTime = 0;
    return timer;
}

void stopTimer(SearchTimer& timer) {
    chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
    timer.endTime = chrono::duration_cast<chrono::microseconds>(now.time_since_epoch()).count();
}

double getElapsedTimeMs(const SearchTimer& timer) {
    return static_cast<double>(timer.endTime - timer.startTime) / 1000.0;
}

// ========== THUẬT TOÁN TÌM KIẾM ==========

/**
 * @brief Tìm kiếm tuần tự trong mảng sinh viên
 */
SearchResult sequentialSearch(Student* students, int totalCount, const char* keyword, int searchCriteria) {
    SearchResult result;
    result.students = nullptr;
    result.count = 0;
    result.isBinarySearch = false;
    
    SearchTimer timer = startTimer();
    
    // Đếm số lượng kết quả trước
    int matchCount = 0;
    for (int i = 0; i < totalCount; i++) {
        if (studentMatchesCriteria(students[i], keyword, searchCriteria)) {
            matchCount++;
        }
    }
    
    if (matchCount > 0) {
        result.students = new Student[matchCount];
        result.count = matchCount;
        
        int resultIndex = 0;
        for (int i = 0; i < totalCount; i++) {
            if (studentMatchesCriteria(students[i], keyword, searchCriteria)) {
                result.students[resultIndex] = students[i];
                resultIndex++;
            }
        }
    }
    
    stopTimer(timer);
    result.searchTimeMs = getElapsedTimeMs(timer);
    
    return result;
}

/**
 * @brief Tìm kiếm nhị phân trong mảng đã sắp xếp
 */
SearchResult binarySearchArray(const ArrayStudentList& list, const char* keyword, int searchCriteria, int sortCriteria) {
    SearchResult result;
    result.students = nullptr;
    result.count = 0;
    result.isBinarySearch = true;
    
    SearchTimer timer = startTimer();
    
    // Tìm kiếm nhị phân chỉ áp dụng khi tiêu chí tìm kiếm khớp với tiêu chí sắp xếp
    if (searchCriteria == sortCriteria) {
        if (searchCriteria == SEARCH_BY_SCORE) {
            float searchScore = atof(keyword);
            int left = 0, right = list.count - 1;
            int foundIndex = -1;
            
            // Tìm kiếm nhị phân
            while (left <= right) {
                int mid = (left + right) / 2;
                if (list.students[mid].score == searchScore) {
                    foundIndex = mid;
                    break;
                } else if (list.students[mid].score < searchScore) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            
            if (foundIndex != -1) {
                // Tìm tất cả sinh viên có cùng điểm số
                int startIndex = foundIndex, endIndex = foundIndex;
                
                // Tìm về phía trước
                while (startIndex > 0 && list.students[startIndex - 1].score == searchScore) {
                    startIndex--;
                }
                
                // Tìm về phía sau
                while (endIndex < list.count - 1 && list.students[endIndex + 1].score == searchScore) {
                    endIndex++;
                }
                
                result.count = endIndex - startIndex + 1;
                result.students = new Student[result.count];
                
                for (int i = 0; i < result.count; i++) {
                    result.students[i] = list.students[startIndex + i];
                }
            }
        }
        // Có thể thêm tìm kiếm nhị phân cho các tiêu chí khác nếu cần
    }
    
    // Nếu không thể dùng tìm kiếm nhị phân, dùng tìm kiếm tuần tự
    if (result.count == 0 && searchCriteria != sortCriteria) {
        stopTimer(timer);
        return sequentialSearch(const_cast<Student*>(list.students), list.count, keyword, searchCriteria);
    }
    
    stopTimer(timer);
    result.searchTimeMs = getElapsedTimeMs(timer);
    
    return result;
}

/**
 * @brief Tìm kiếm trong Array List
 */
SearchResult searchInArrayList(const ArrayStudentList& list, const char* keyword, int searchCriteria, bool isSorted, int sortCriteria) {
    if (isSorted && searchCriteria == sortCriteria) {
        return binarySearchArray(list, keyword, searchCriteria, sortCriteria);
    } else {
        return sequentialSearch(const_cast<Student*>(list.students), list.count, keyword, searchCriteria);
    }
}

/**
 * @brief Tìm kiếm trong Singly Linked List (luôn dùng tìm kiếm tuần tự)
 */
SearchResult searchInSinglyLinkedList(NodeSLL* head, const char* keyword, int searchCriteria) {
    SearchResult result;
    result.students = nullptr;
    result.count = 0;
    result.isBinarySearch = false;
    
    SearchTimer timer = startTimer();
    
    // Đếm số lượng kết quả trước
    int matchCount = 0;
    NodeSLL* current = head;
    while (current != nullptr) {
        if (studentMatchesCriteria(current->info, keyword, searchCriteria)) {
            matchCount++;
        }
        current = current->next;
    }
    
    if (matchCount > 0) {
        result.students = new Student[matchCount];
        result.count = matchCount;
        
        int resultIndex = 0;
        current = head;
        while (current != nullptr) {
            if (studentMatchesCriteria(current->info, keyword, searchCriteria)) {
                result.students[resultIndex] = current->info;
                resultIndex++;
            }
            current = current->next;
        }
    }
    
    stopTimer(timer);
    result.searchTimeMs = getElapsedTimeMs(timer);
    
    return result;
}

/**
 * @brief Tìm kiếm trong Circular Linked List (luôn dùng tìm kiếm tuần tự)
 */
SearchResult searchInCircularLinkedList(NodeSLL* head, const char* keyword, int searchCriteria) {
    SearchResult result;
    result.students = nullptr;
    result.count = 0;
    result.isBinarySearch = false;
    
    if (head == nullptr) {
        result.searchTimeMs = 0;
        return result;
    }
    
    SearchTimer timer = startTimer();
    
    // Đếm số lượng kết quả trước
    int matchCount = 0;
    NodeSLL* current = head;
    do {
        if (studentMatchesCriteria(current->info, keyword, searchCriteria)) {
            matchCount++;
        }
        current = current->next;
    } while (current != head);
    
    if (matchCount > 0) {
        result.students = new Student[matchCount];
        result.count = matchCount;
        
        int resultIndex = 0;
        current = head;
        do {
            if (studentMatchesCriteria(current->info, keyword, searchCriteria)) {
                result.students[resultIndex] = current->info;
                resultIndex++;
            }
            current = current->next;
        } while (current != head);
    }
    
    stopTimer(timer);
    result.searchTimeMs = getElapsedTimeMs(timer);
    
    return result;
}

/**
 * @brief Tìm kiếm trong Doubly Linked List
 */
SearchResult searchInDoublyLinkedList(NodeDLL* head, const char* keyword, int searchCriteria, bool isSorted, int sortCriteria) {
    SearchResult result;
    result.students = nullptr;
    result.count = 0;
    result.isBinarySearch = false;
    
    SearchTimer timer = startTimer();
    
    // Doubly Linked List có thể dùng tìm kiếm nhị phân nếu đã sắp xếp
    if (isSorted && searchCriteria == sortCriteria && searchCriteria == SEARCH_BY_SCORE) {
        result.isBinarySearch = true;
        float searchScore = atof(keyword);
        
        // Đếm tổng số node
        int totalNodes = 0;
        NodeDLL* temp = head;
        while (temp != nullptr) {
            totalNodes++;
            temp = temp->next;
        }
        
        // Thực hiện tìm kiếm nhị phân
        int left = 0, right = totalNodes - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            
            // Di chuyển đến node thứ mid
            NodeDLL* midNode = head;
            for (int i = 0; i < mid; i++) {
                midNode = midNode->next;
            }
            
            if (midNode->info.score == searchScore) {
                // Tìm thấy, thu thập tất cả sinh viên có cùng điểm
                int matchCount = 0;
                NodeDLL* current = head;
                while (current != nullptr) {
                    if (current->info.score == searchScore) {
                        matchCount++;
                    }
                    current = current->next;
                }
                
                if (matchCount > 0) {
                    result.students = new Student[matchCount];
                    result.count = matchCount;
                    
                    int resultIndex = 0;
                    current = head;
                    while (current != nullptr) {
                        if (current->info.score == searchScore) {
                            result.students[resultIndex] = current->info;
                            resultIndex++;
                        }
                        current = current->next;
                    }
                }
                break;
            } else if (midNode->info.score < searchScore) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    } else {
        // Tìm kiếm tuần tự
        result.isBinarySearch = false;
        
        int matchCount = 0;
        NodeDLL* current = head;
        while (current != nullptr) {
            if (studentMatchesCriteria(current->info, keyword, searchCriteria)) {
                matchCount++;
            }
            current = current->next;
        }
        
        if (matchCount > 0) {
            result.students = new Student[matchCount];
            result.count = matchCount;
            
            int resultIndex = 0;
            current = head;
            while (current != nullptr) {
                if (studentMatchesCriteria(current->info, keyword, searchCriteria)) {
                    result.students[resultIndex] = current->info;
                    resultIndex++;
                }
                current = current->next;
            }
        }
    }
    
    stopTimer(timer);
    result.searchTimeMs = getElapsedTimeMs(timer);
    
    return result;
}

// ========== HÀM HIỂN THỊ KẾT QUẢ ==========

/**
 * @brief In văn bản với phần khớp được tô đỏ và in đậm
 */
void printHighlighted(const char* text, const char* keyword) {
    if (!text || !keyword) {
        cout << (text ? text : "");
        return;
    }
    
    string textStr(text);
    string keywordStr(keyword);
    
    // Chuyển thành chữ thường để so sánh
    string textLower = textStr;
    string keywordLower = keywordStr;
    
    for (size_t i = 0; i < textLower.length(); i++) {
        textLower[i] = tolower(textLower[i]);
    }
    for (size_t i = 0; i < keywordLower.length(); i++) {
        keywordLower[i] = tolower(keywordLower[i]);
    }
    
    // Tìm vị trí của từ khóa trong văn bản
    size_t pos = textLower.find(keywordLower);
    
    if (pos != string::npos) {
        // In phần trước từ khóa
        cout << textStr.substr(0, pos);
        
        // In từ khóa với màu đỏ và in đậm
        cout << RED << BOLD << textStr.substr(pos, keywordStr.length()) << RESET;
        
        // In phần sau từ khóa
        cout << textStr.substr(pos + keywordStr.length());
    } else {
        // Nếu không tìm thấy từ khóa, in bình thường
        cout << textStr;
    }
}

/**
 * @brief Hiển thị một sinh viên với highlight
 */
void displayStudentWithHighlight(const Student& student, const char* keyword, int searchCriteria, bool showReversedName) {
    cout << "│ ";
    
    // Hiển thị mã sinh viên
    if (searchCriteria == SEARCH_BY_STUDENT_ID) {
        printHighlighted(student.studentID, keyword);
    } else {
        cout << student.studentID;
    }
    cout << string(DISPLAY_WIDTH_ID - strlen(student.studentID), ' ') << " │ ";
    
    // Hiển thị họ
    if (searchCriteria == SEARCH_BY_LAST_NAME) {
        printHighlighted(student.lastName, keyword);
    } else {
        cout << student.lastName;
    }
    cout << string(DISPLAY_WIDTH_NAME - strlen(student.lastName), ' ') << " │ ";
    
    // Hiển thị tên
    if (searchCriteria == SEARCH_BY_FIRST_NAME) {
        printHighlighted(student.firstName, keyword);
    } else {
        cout << student.firstName;
    }
    cout << string(DISPLAY_WIDTH_NAME - strlen(student.firstName), ' ') << " │ ";
    
    // Hiển thị lớp
    if (searchCriteria == SEARCH_BY_CLASS) {
        printHighlighted(student.studentClass, keyword);
    } else {
        cout << student.studentClass;
    }
    cout << string(DISPLAY_WIDTH_CLASS - strlen(student.studentClass), ' ') << " │ ";
    
    // Hiển thị điểm
    if (searchCriteria == SEARCH_BY_SCORE) {
        cout << RED << BOLD << fixed << setprecision(2) << student.score << RESET;
    } else {
        cout << fixed << setprecision(2) << student.score;
    }
    cout << "   │";
    
    // Hiển thị họ tên đảo ngược nếu được yêu cầu
    if (showReversedName) {
        char* reversedName = reverseFullName(student.firstName, student.lastName);
        if (reversedName) {
            cout << " " << YELLOW << ITALIC << reversedName << RESET;
            delete[] reversedName;
        }
    }
    
    cout << endl;
}

/**
 * @brief Hiển thị kết quả tìm kiếm
 */
void displaySearchResults(const SearchResult& result, const char* keyword, int searchCriteria, bool showReversedName) {
    if (result.count == 0) {
        cout << RED << "\n❌ Không tìm thấy sinh viên nào khớp với tiêu chí tìm kiếm!" << RESET << endl;
        cout << CYAN << "⏱️  Thời gian tìm kiếm: " << fixed << setprecision(3) << result.searchTimeMs << " ms" << RESET << endl;
        return;
    }
    
    // Hiển thị thông tin tìm kiếm
    cout << GREEN << "\n✅ Tìm thấy " << result.count << " sinh viên khớp với tiêu chí tìm kiếm!" << RESET << endl;
    cout << CYAN << "🔍 Phương pháp: " << (result.isBinarySearch ? "Tìm kiếm nhị phân" : "Tìm kiếm tuần tự") << RESET << endl;
    cout << CYAN << "⏱️  Thời gian: " << fixed << setprecision(3) << result.searchTimeMs << " ms" << RESET << endl;
    
    if (showReversedName) {
        cout << YELLOW << "🔄 Hiển thị kèm họ tên đảo ngược" << RESET << endl;
    }
    
    // Hiển thị bảng kết quả
    cout << "\n";
    displayStudentTableHeader();
    
    for (int i = 0; i < result.count; i++) {
        displayStudentWithHighlight(result.students[i], keyword, searchCriteria, showReversedName);
    }
    
    displayStudentTableFooter();
}

/**
 * @brief Giải phóng bộ nhớ kết quả tìm kiếm
 */
void freeSearchResult(SearchResult& result) {
    if (result.students != nullptr) {
        delete[] result.students;
        result.students = nullptr;
    }
    result.count = 0;
}
