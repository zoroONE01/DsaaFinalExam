#include "../../include/algorithms/search.h"
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
bool compareIgnoreCase(const char* str1, const char* str2) {
    if (!str1 || !str2) return false;
    
    while (*str1 && *str2) {
        if (tolower(*str1) != tolower(*str2)) {
            return false;
        }
        str1++;
        str2++;
    }
    return (*str1 == *str2);
}

/**
 * @brief Kiểm tra chuỗi con không phân biệt hoa thường
 */
bool containsIgnoreCase(const char* str, const char* substring) {
    if (!str || !substring) return false;
    if (strlen(substring) == 0) return true;
    
    char* lowerStr = new char[strlen(str) + 1];
    char* lowerSub = new char[strlen(substring) + 1];
    
    // Chuyển sang chữ thường
    for (int i = 0; str[i]; i++) {
        lowerStr[i] = tolower(str[i]);
    }
    lowerStr[strlen(str)] = '\0';
    
    for (int i = 0; substring[i]; i++) {
        lowerSub[i] = tolower(substring[i]);
    }
    lowerSub[strlen(substring)] = '\0';
    
    bool found = (strstr(lowerStr, lowerSub) != nullptr);
    
    delete[] lowerStr;
    delete[] lowerSub;
    
    return found;
}

/**
 * @brief Kiểm tra sinh viên có khớp với tiêu chí tìm kiếm không
 */
bool checkStudentMatch(const Student& student, const char* keyword, int searchCriteria) {
    if (!keyword || strlen(keyword) == 0) return true;
    
    switch (searchCriteria) {
        case SEARCH_BY_STUDENT_ID: // Mã sinh viên
            return containsIgnoreCase(student.studentID, keyword);
        case SEARCH_BY_FIRST_NAME: // Tên
            return containsIgnoreCase(student.firstName, keyword);
        case SEARCH_BY_LAST_NAME: // Họ
            return containsIgnoreCase(student.lastName, keyword);
        case SEARCH_BY_CLASS: // Lớp
            return containsIgnoreCase(student.studentClass, keyword);
        case SEARCH_BY_SCORE: // Điểm
        {
            float searchScore = atof(keyword);
            return (student.score >= searchScore - 0.01 && student.score <= searchScore + 0.01);
        }
        default:
            return false;
    }
}

/**
 * @brief In văn bản với phần khớp được tô đỏ và in đậm
 */
void printWithHighlight(const char* text, const char* keyword, int searchCriteria, int currentCriteria) {
    // Chỉ highlight nếu đây là trường đang tìm kiếm
    if (searchCriteria == currentCriteria && keyword && strlen(keyword) > 0) {
        if (containsIgnoreCase(text, keyword)) {
            cout << RED << BOLD << text << RESET;
        } else {
            cout << text;
        }
    } else {
        cout << text;
    }
}

// ========== HÀM TÌM KIẾM TUẦN TỰ ==========

/**
 * @brief Tìm kiếm tuần tự trong mảng
 */
SearchResult sequentialSearchArray(const ArrayStudentList& list, const char* keyword, int searchCriteria) {
    SearchResult result;
    result.count = 0;
    result.isBinarySearch = false;
    
    chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();
    
    // Đếm số lượng kết quả trước
    int matchCount = 0;
    for (int i = 0; i < list.count; i++) {
        if (checkStudentMatch(list.students[i], keyword, searchCriteria)) {
            matchCount++;
        }
    }
    
    // Cấp phát bộ nhớ cho kết quả
    if (matchCount > 0) {
        result.students = new Student[matchCount];
        result.count = matchCount;
        
        int resultIndex = 0;
        for (int i = 0; i < list.count; i++) {
            if (checkStudentMatch(list.students[i], keyword, searchCriteria)) {
                result.students[resultIndex] = list.students[i];
                resultIndex++;
            }
        }
    } else {
        result.students = nullptr;
    }
    
    chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
    chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    result.searchTimeMs = static_cast<double>(duration.count()) / 1000.0;
    
    return result;
}

/**
 * @brief Tìm kiếm nhị phân trong mảng đã sắp xếp theo điểm
 */
SearchResult binarySearchArrayByScore(const ArrayStudentList& list, float targetScore) {
    SearchResult result;
    result.count = 0;
    result.isBinarySearch = true;
    result.students = nullptr;
    
    chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();
    
    int left = 0, right = list.count - 1;
    int foundIndex = -1;
    
    // Tìm kiếm nhị phân
    while (left <= right) {
        int mid = (left + right) / 2;
        
        if (list.students[mid].score == targetScore) {
            foundIndex = mid;
            break;
        } else if (list.students[mid].score < targetScore) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    if (foundIndex != -1) {
        // Tìm tất cả sinh viên có cùng điểm số
        int startIndex = foundIndex, endIndex = foundIndex;
        
        // Tìm về phía trước
        while (startIndex > 0 && list.students[startIndex - 1].score == targetScore) {
            startIndex--;
        }
        
        // Tìm về phía sau
        while (endIndex < list.count - 1 && list.students[endIndex + 1].score == targetScore) {
            endIndex++;
        }
        
        result.count = endIndex - startIndex + 1;
        result.students = new Student[result.count];
        
        for (int i = 0; i < result.count; i++) {
            result.students[i] = list.students[startIndex + i];
        }
    }
    
    chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
    chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    result.searchTimeMs = static_cast<double>(duration.count()) / 1000.0;
    
    return result;
}

/**
 * @brief Tìm kiếm trong danh sách liên kết đơn (luôn dùng tìm kiếm tuần tự)
 */
SearchResult sequentialSearchSLL(NodeSLL* head, const char* keyword, int searchCriteria) {
    SearchResult result;
    result.count = 0;
    result.isBinarySearch = false;
    result.students = nullptr;
    
    chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();
    
    // Đếm số lượng kết quả
    int matchCount = 0;
    NodeSLL* current = head;
    while (current != nullptr) {
        if (checkStudentMatch(current->info, keyword, searchCriteria)) {
            matchCount++;
        }
        current = current->next;
    }
    
    if (matchCount > 0) {
        result.students = new Student[matchCount];
        result.count = matchCount;
        
        int resultIndex = 0;
        int nodeIndex = 0;
        current = head;
        while (current != nullptr) {
            if (checkStudentMatch(current->info, keyword, searchCriteria)) {
                result.students[resultIndex] = current->info;
                resultIndex++;
            }
            current = current->next;
            nodeIndex++;
        }
    }
    
    chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
    chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    result.searchTimeMs = static_cast<double>(duration.count()) / 1000.0;
    
    return result;
}

/**
 * @brief Tìm kiếm trong danh sách liên kết vòng (luôn dùng tìm kiếm tuần tự)
 */
SearchResult sequentialSearchCLL(NodeSLL* head, const char* keyword, int searchCriteria) {
    SearchResult result;
    result.count = 0;
    result.isBinarySearch = false;
    result.students = nullptr;
    
    if (head == nullptr) {
        result.searchTimeMs = 0;
        return result;
    }
    
    chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();
    
    // Đếm số lượng kết quả
    int matchCount = 0;
    NodeSLL* current = head;
    do {
        if (checkStudentMatch(current->info, keyword, searchCriteria)) {
            matchCount++;
        }
        current = current->next;
    } while (current != head);
    
    if (matchCount > 0) {
        result.students = new Student[matchCount];
        result.count = matchCount;
        
        int resultIndex = 0;
        int nodeIndex = 0;
        current = head;
        do {
            if (checkStudentMatch(current->info, keyword, searchCriteria)) {
                result.students[resultIndex] = current->info;
                resultIndex++;
            }
            current = current->next;
            nodeIndex++;
        } while (current != head);
    }
    
    chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
    chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    result.searchTimeMs = static_cast<double>(duration.count()) / 1000.0;
    
    return result;
}

/**
 * @brief Tìm kiếm trong danh sách liên kết kép
 */
SearchResult searchDoublyLinkedList(NodeDLL* head, const char* keyword, int searchCriteria, bool isSorted, int sortCriteria) {
    SearchResult result;
    result.count = 0;
    result.students = nullptr;
    
    // Nếu danh sách đã sắp xếp theo điểm và tìm kiếm theo điểm, có thể dùng binary search
    if (isSorted && sortCriteria == SORT_BY_SCORE && searchCriteria == SEARCH_BY_SCORE) {
        result.isBinarySearch = true;
        
        chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();
        
        float targetScore = atof(keyword);
        
        // Đếm tổng số node
        int totalNodes = 0;
        NodeDLL* current = head;
        while (current != nullptr) {
            totalNodes++;
            current = current->next;
        }
        
        // Binary search trên doubly linked list
        int left = 0, right = totalNodes - 1;
        int foundIndex = -1;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            
            // Di chuyển đến node thứ mid
            NodeDLL* midNode = head;
            for (int i = 0; i < mid; i++) {
                midNode = midNode->next;
            }
            
            if (midNode->info.score == targetScore) {
                foundIndex = mid;
                break;
            } else if (midNode->info.score < targetScore) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        if (foundIndex != -1) {
            // Thu thập tất cả sinh viên có cùng điểm
            int matchCount = 0;
            current = head;
            while (current != nullptr) {
                if (current->info.score == targetScore) {
                    matchCount++;
                }
                current = current->next;
            }
            
            if (matchCount > 0) {
                result.students = new Student[matchCount];
                result.count = matchCount;
                
                int resultIndex = 0;
                int nodeIndex = 0;
                current = head;
                while (current != nullptr) {
                    if (current->info.score == targetScore) {
                        result.students[resultIndex] = current->info;
                        resultIndex++;
                    }
                    current = current->next;
                    nodeIndex++;
                }
            }
        }
        
        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
        result.searchTimeMs = static_cast<double>(duration.count()) / 1000.0;
    } else {
        // Tìm kiếm tuần tự
        result.isBinarySearch = false;
        
        chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();
        
        // Đếm số lượng kết quả
        int matchCount = 0;
        NodeDLL* current = head;
        while (current != nullptr) {
            if (checkStudentMatch(current->info, keyword, searchCriteria)) {
                matchCount++;
            }
            current = current->next;
        }
        
        if (matchCount > 0) {
            result.students = new Student[matchCount];
            result.count = matchCount;
            
            int resultIndex = 0;
            int nodeIndex = 0;
            current = head;
            while (current != nullptr) {
                if (checkStudentMatch(current->info, keyword, searchCriteria)) {
                    result.students[resultIndex] = current->info;
                    resultIndex++;
                }
                current = current->next;
                nodeIndex++;
            }
        }
        
        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
        result.searchTimeMs = static_cast<double>(duration.count()) / 1000.0;
    }
    
    return result;
}

// ========== HÀM HIỂN THỊ KẾT QUẢ ==========

/**
 * @brief Hiển thị kết quả tìm kiếm
 */
void displaySearchResults(const SearchResult& result, const char* keyword, int searchCriteria, bool showReversedName, const char* dataStructureName) {
    if (result.count == 0) {
        cout << RED << "\n❌ Không tìm thấy sinh viên nào khớp với tiêu chí tìm kiếm!" << RESET << endl;
        cout << CYAN << "⏱️  Thời gian tìm kiếm: " << fixed << setprecision(3) << result.searchTimeMs << " ms" << RESET << endl;
        return;
    }
    
    // Hiển thị thông tin tìm kiếm
    cout << GREEN << "\n✅ Tìm thấy " << result.count << " sinh viên khớp với tiêu chí tìm kiếm!" << RESET << endl;
    cout << CYAN << "🔍 Phương pháp: " << (result.isBinarySearch ? "Tìm kiếm nhị phân" : "Tìm kiếm tuần tự") << RESET << endl;
    cout << CYAN << "📊 Cấu trúc dữ liệu: " << dataStructureName << RESET << endl;
    cout << CYAN << "⏱️  Thời gian: " << fixed << setprecision(3) << result.searchTimeMs << " ms" << RESET << endl;
    
    if (showReversedName) {
        cout << YELLOW << "🔄 Hiển thị kèm họ tên đảo ngược" << RESET << endl;
    }
    
    // Hiển thị bảng kết quả
    cout << "\n";
    cout << setfill('=') << setw(125) << "=" << setfill(' ') << endl;
    cout << "| " << setw(3) << "STT" << " | " << setw(12) << "Mã SV" << " | " 
         << setw(15) << "Họ" << " | " << setw(10) << "Tên" << " | " 
         << setw(12) << "Lớp" << " | " << setw(6) << "Điểm" << " |";
    
    if (showReversedName) {
        cout << setw(25) << "Họ Tên Đảo ngược" << " |";
    }
    cout << endl;
    cout << setfill('-') << setw(125) << "-" << setfill(' ') << endl;
    
    for (int i = 0; i < result.count; i++) {
        const Student& student = result.students[i];
        
        cout << "| " << setw(3) << (i + 1) << " | ";
        
        // Hiển thị mã sinh viên với highlight nếu cần
        printWithHighlight(student.studentID, keyword, searchCriteria, SEARCH_BY_STUDENT_ID);
        cout << string(12 - strlen(student.studentID), ' ') << " | ";
        
        // Hiển thị họ với highlight nếu cần
        printWithHighlight(student.lastName, keyword, searchCriteria, SEARCH_BY_LAST_NAME);
        cout << string(15 - strlen(student.lastName), ' ') << " | ";
        
        // Hiển thị tên với highlight nếu cần
        printWithHighlight(student.firstName, keyword, searchCriteria, SEARCH_BY_FIRST_NAME);
        cout << string(10 - strlen(student.firstName), ' ') << " | ";
        
        // Hiển thị lớp với highlight nếu cần
        printWithHighlight(student.studentClass, keyword, searchCriteria, SEARCH_BY_CLASS);
        cout << string(12 - strlen(student.studentClass), ' ') << " | ";
        
        // Hiển thị điểm với highlight nếu cần
        if (searchCriteria == 5) {
            cout << RED << BOLD << setw(6) << fixed << setprecision(1) << student.score << RESET;
        } else {
            cout << setw(6) << fixed << setprecision(1) << student.score;
        }
        cout << " |";
        
        // Hiển thị họ tên đảo ngược nếu được yêu cầu
        if (showReversedName) {
            char* reversedName = reverseFullName(student.firstName, student.lastName);
            if (reversedName) {
                cout << setw(25) << reversedName;
                delete[] reversedName;
            } else {
                cout << setw(25) << "";
            }
            cout << " |";
        }
        
        cout << endl;
    }
    cout << setfill('-') << setw(125) << "-" << setfill(' ') << endl;
}
