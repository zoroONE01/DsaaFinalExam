#ifndef SEARCH_MENU_H
#define SEARCH_MENU_H

#include "student_search.h"

using namespace std;

// ========== Hàm menu tìm kiếm ==========

// Hiển thị menu chọn tiêu chí tìm kiếm
int displaySearchCriteriaMenu();

// Nhập từ khóa tìm kiếm
bool inputSearchKeyword(char* keyword, int maxLength, int searchCriteria);

// Hiển thị menu tùy chọn hiển thị kết quả
bool askForReversedNameDisplay();

// Hàm tìm kiếm tổng hợp cho tất cả cấu trúc dữ liệu
void performSearch(int dataStructureType, void* dataStructure, bool isSorted = false, int sortCriteria = 0);

// Hàm nhập điều kiện tìm kiếm từ người dùng
void searchStudentInterface(int dataStructureType, void* dataStructure, bool isSorted = false, int sortCriteria = 0);

#endif // SEARCH_MENU_H
