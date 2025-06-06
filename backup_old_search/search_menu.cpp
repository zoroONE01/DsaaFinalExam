#include "../../include/ui/search_menu.h"
#include "../../include/ui/common_ui.h"
#include "../../include/utils/validation.h"
#include "../../include/utils/error_handling.h"
#include "../../include/data_structures/array_list.h"
#include "../../include/data_structures/singly_linked_list.h"
#include "../../include/data_structures/circular_linked_list.h"
#include "../../include/data_structures/doubly_linked_list.h"
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

// ========== CÀI ĐẶT MENU TÌM KIẾM ==========

/**
 * @brief Hiển thị menu chọn tiêu chí tìm kiếm
 */
int displaySearchCriteriaMenu() {
    printHeader("CHỌN TIÊU CHÍ TÌM KIẾM");
    
    cout << CYAN << "┌─────────────────────────────────────┐" << RESET << endl;
    cout << CYAN << "│" << RESET << " " << YELLOW << "1." << RESET << " Tìm kiếm theo Mã sinh viên     " << CYAN << "│" << RESET << endl;
    cout << CYAN << "│" << RESET << " " << YELLOW << "2." << RESET << " Tìm kiếm theo Tên              " << CYAN << "│" << RESET << endl;
    cout << CYAN << "│" << RESET << " " << YELLOW << "3." << RESET << " Tìm kiếm theo Họ               " << CYAN << "│" << RESET << endl;
    cout << CYAN << "│" << RESET << " " << YELLOW << "4." << RESET << " Tìm kiếm theo Lớp              " << CYAN << "│" << RESET << endl;
    cout << CYAN << "│" << RESET << " " << YELLOW << "5." << RESET << " Tìm kiếm theo Điểm             " << CYAN << "│" << RESET << endl;
    cout << CYAN << "│" << RESET << " " << YELLOW << "0." << RESET << " Quay lại                       " << CYAN << "│" << RESET << endl;
    cout << CYAN << "└─────────────────────────────────────┘" << RESET << endl;
    
    int choice;
    cout << BOLD << "Nhập lựa chọn của bạn (0-5): " << RESET;
    
    // Kiểm tra đầu vào hợp lệ
    while (!(cin >> choice) || choice < 0 || choice > 5) {
        printError("Lựa chọn không hợp lệ! Vui lòng nhập số từ 0-5.");
        clearInputBuffer();
        cout << BOLD << "Nhập lại: " << RESET;
    }
    clearInputBuffer();
    
    return choice;
}

/**
 * @brief Lấy tên tiêu chí tìm kiếm
 */
const char* getSearchCriteriaName(int criteria) {
    switch (criteria) {
        case SEARCH_BY_STUDENT_ID: return "Mã sinh viên";
        case SEARCH_BY_FIRST_NAME: return "Tên";
        case SEARCH_BY_LAST_NAME: return "Họ";
        case SEARCH_BY_CLASS: return "Lớp";
        case SEARCH_BY_SCORE: return "Điểm";
        default: return "Không xác định";
    }
}

/**
 * @brief Nhập từ khóa tìm kiếm
 */
bool inputSearchKeyword(char* keyword, int maxLength, int searchCriteria) {
    cout << CYAN << "\n📝 Nhập từ khóa tìm kiếm theo " << getSearchCriteriaName(searchCriteria) << ":" << RESET << endl;
    
    if (searchCriteria == SEARCH_BY_SCORE) {
        cout << YELLOW << "💡 Lưu ý: Nhập điểm số (0.0 - 10.0)" << RESET << endl;
    } else {
        cout << YELLOW << "💡 Lưu ý: Tìm kiếm không phân biệt hoa thường, có thể nhập từ khóa một phần" << RESET << endl;
    }
    
    cout << BOLD << "Từ khóa: " << RESET;
    cin.getline(keyword, maxLength);
    
    // Kiểm tra từ khóa rỗng
    if (strlen(keyword) == 0) {
        printError("Từ khóa không được để trống!");
        return false;
    }
    
    // Kiểm tra điểm số hợp lệ nếu tìm kiếm theo điểm
    if (searchCriteria == SEARCH_BY_SCORE) {
        float score = atof(keyword);
        if (score < 0.0 || score > 10.0) {
            printError("Điểm số phải nằm trong khoảng 0.0 - 10.0!");
            return false;
        }
    }
    
    return true;
}

/**
 * @brief Hỏi người dùng có muốn hiển thị họ tên đảo ngược không
 */
bool askForReversedNameDisplay() {
    cout << CYAN << "\n🔄 Bạn có muốn hiển thị họ tên đảo ngược trong kết quả không? (y/n): " << RESET;
    
    char choice;
    cin >> choice;
    clearInputBuffer();
    
    return (choice == 'y' || choice == 'Y');
}

/**
 * @brief Thực hiện tìm kiếm cho Array List
 */
void searchInArrayListInterface(ArrayStudentList* list, const char* keyword, int searchCriteria, bool showReversed, bool isSorted, int sortCriteria) {
    if (!list || list->count == 0) {
        printError("Danh sách sinh viên trống!");
        return;
    }
    
    SearchResult result = searchInArrayList(*list, keyword, searchCriteria, isSorted, sortCriteria);
    displaySearchResults(result, keyword, searchCriteria, showReversed);
    freeSearchResult(result);
}

/**
 * @brief Thực hiện tìm kiếm cho Singly Linked List
 */
void searchInSinglyLinkedListInterface(NodeSLL** head, const char* keyword, int searchCriteria, bool showReversed) {
    if (!head || !*head) {
        printError("Danh sách sinh viên trống!");
        return;
    }
    
    SearchResult result = searchInSinglyLinkedList(*head, keyword, searchCriteria);
    displaySearchResults(result, keyword, searchCriteria, showReversed);
    freeSearchResult(result);
}

/**
 * @brief Thực hiện tìm kiếm cho Circular Linked List
 */
void searchInCircularLinkedListInterface(NodeSLL** head, const char* keyword, int searchCriteria, bool showReversed) {
    if (!head || !*head) {
        printError("Danh sách sinh viên trống!");
        return;
    }
    
    SearchResult result = searchInCircularLinkedList(*head, keyword, searchCriteria);
    displaySearchResults(result, keyword, searchCriteria, showReversed);
    freeSearchResult(result);
}

/**
 * @brief Thực hiện tìm kiếm cho Doubly Linked List
 */
void searchInDoublyLinkedListInterface(NodeDLL** head, const char* keyword, int searchCriteria, bool showReversed, bool isSorted, int sortCriteria) {
    if (!head || !*head) {
        printError("Danh sách sinh viên trống!");
        return;
    }
    
    SearchResult result = searchInDoublyLinkedList(*head, keyword, searchCriteria, isSorted, sortCriteria);
    displaySearchResults(result, keyword, searchCriteria, showReversed);
    freeSearchResult(result);
}

/**
 * @brief Hàm tìm kiếm tổng hợp cho tất cả cấu trúc dữ liệu
 */
void performSearch(int dataStructureType, void* dataStructure, bool isSorted, int sortCriteria) {
    if (!dataStructure) {
        printError("Cấu trúc dữ liệu không hợp lệ!");
        return;
    }
    
    // Chọn tiêu chí tìm kiếm
    int searchCriteria = displaySearchCriteriaMenu();
    if (searchCriteria == 0) {
        return; // Người dùng chọn quay lại
    }
    
    // Nhập từ khóa tìm kiếm
    char keyword[256];
    if (!inputSearchKeyword(keyword, sizeof(keyword), searchCriteria)) {
        return;
    }
    
    // Hỏi có muốn hiển thị họ tên đảo ngược không
    bool showReversed = askForReversedNameDisplay();
    
    // Hiển thị thông tin tìm kiếm
    cout << CYAN << "\n🔍 Đang tìm kiếm..." << RESET << endl;
    cout << YELLOW << "📋 Cấu trúc dữ liệu: " << getDataStructureName(dataStructureType) << RESET << endl;
    cout << YELLOW << "🎯 Tiêu chí: " << getSearchCriteriaName(searchCriteria) << RESET << endl;
    cout << YELLOW << "🔑 Từ khóa: \"" << keyword << "\"" << RESET << endl;
    
    if (isSorted) {
        cout << YELLOW << "📊 Dữ liệu đã sắp xếp theo: " << getSearchCriteriaName(sortCriteria) << RESET << endl;
    }
    
    printDivider();
    
    // Thực hiện tìm kiếm tương ứng với cấu trúc dữ liệu
    switch (dataStructureType) {
        case ARRAY_LIST:
            searchInArrayListInterface((ArrayStudentList*)dataStructure, keyword, searchCriteria, showReversed, isSorted, sortCriteria);
            break;
            
        case SINGLY_LINKED_LIST:
            searchInSinglyLinkedListInterface((NodeSLL**)dataStructure, keyword, searchCriteria, showReversed);
            break;
            
        case CIRCULAR_LINKED_LIST:
            searchInCircularLinkedListInterface((NodeSLL**)dataStructure, keyword, searchCriteria, showReversed);
            break;
            
        case DOUBLY_LINKED_LIST:
            searchInDoublyLinkedListInterface((NodeDLL**)dataStructure, keyword, searchCriteria, showReversed, isSorted, sortCriteria);
            break;
            
        default:
            printError("Cấu trúc dữ liệu không được hỗ trợ cho tìm kiếm!");
            break;
    }
}

/**
 * @brief Giao diện tìm kiếm sinh viên
 */
void searchStudentInterface(int dataStructureType, void* dataStructure, bool isSorted, int sortCriteria) {
    clearScreen();
    printHeader("TÌM KIẾM SINH VIÊN");
    
    cout << GREEN << "📚 Chức năng này cho phép bạn tìm kiếm sinh viên theo nhiều tiêu chí khác nhau:" << RESET << endl;
    cout << CYAN << "   • Mã sinh viên, Họ, Tên, Lớp, Điểm" << RESET << endl;
    cout << CYAN << "   • Tìm kiếm không phân biệt hoa thường" << RESET << endl;
    cout << CYAN << "   • Tự động chọn thuật toán tìm kiếm tối ưu" << RESET << endl;
    cout << CYAN << "   • Hiển thị thời gian thực hiện" << RESET << endl;
    cout << CYAN << "   • Tùy chọn hiển thị họ tên đảo ngược" << RESET << endl;
    
    printDivider();
    
    performSearch(dataStructureType, dataStructure, isSorted, sortCriteria);
    
    cout << YELLOW << "\nNhấn Enter để tiếp tục..." << RESET;
    cin.get();
}
