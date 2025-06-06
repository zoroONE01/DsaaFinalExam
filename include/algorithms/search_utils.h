#ifndef SEARCH_UTILS_H
#define SEARCH_UTILS_H

#include "../core/student.h"

using namespace std;

// ========== Utility Functions cho tìm kiếm ==========

// --- Hàm tiện ích so sánh chuỗi ---
bool caseInsensitiveMatch(const char* str1, const char* str2);
bool caseInsensitiveContains(const char* str, const char* substring);

// --- Hàm kiểm tra tiêu chí tìm kiếm ---
bool matchesSearchCriteria(const Student& student, const char* keyword, int searchCriteria);

// --- Hàm đảo ngược chuỗi ---
char* reverseString(const char* str);
char* reverseFullName(const char* firstName, const char* lastName);

// --- Hàm hiển thị có màu sắc ---
void printHighlighted(const char* text, const char* keyword, int searchCriteria);
void printRedBold(const char* text);
void resetTextColor();

// --- Hàm đo thời gian ---
struct SearchTimer {
    long long startTime;
    long long endTime;
};

SearchTimer startTimer();
void stopTimer(SearchTimer& timer);
double getElapsedTimeMs(const SearchTimer& timer);
double getElapsedTimeSeconds(const SearchTimer& timer);

#endif // SEARCH_UTILS_H
