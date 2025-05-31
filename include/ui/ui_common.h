#ifndef UI_COMMON_H
#define UI_COMMON_H

#include <string>

// ========== Hàm xóa màn hình và điều hướng cơ bản ==========
void clearScreen();
void pauseScreen();
void showWelcomeBanner();

// ========== Hàm hiển thị header và footer cải tiến ==========
void printHeader(const char *header);
void printSubHeader(const char *subheader);
void printSeparator();
void printFooter();
void printApplicationHeader();

// ========== Hàm hiển thị thông báo cải tiến ==========
void printError(const char *message);
void printSuccess(const char *message);
void printInfo(const char *message);
void printWarning(const char *message);
void printNotification(const char *message, const char *type);

// ========== Hàm hiển thị status và loading ==========
void printStatusBar(int dataStructureType, int studentCount);
void printLoadingAnimation(const char *message, int duration = 2);
void printProgress(int current, int total, const char *label);

// ========== Hàm menu cải tiến ==========
void displayMainMenu(int dataStructureType);
void displayEnhancedMenu(const char *title, const char *options[], int optionCount, int currentSelection = -1);
int selectDataStructure();
int selectSortAlgorithm(int dataStructureType);

// ========== Hàm input cải tiến ==========
void printInputBox(const char *prompt, const char *hint = nullptr);
void printInputPrompt(const char *prompt);
bool confirmCancel();
bool confirmAction(const char *action);

// ========== Hàm hiển thị bảng cải tiến ==========
void displayStudentTableHeader();
void displayStudentRow(const struct Student &student, int rowNumber = -1);
void displayStudentTableFooter();
void displayEnhancedStudentTable(const struct Student students[], int count);
void displayEmptyMessage(const char *message);

// ========== Hàm hiển thị thống kê cải tiến ==========
void displayStatsDashboard(float minScore, float maxScore, float avgScore, int totalStudents);
void displaySearchResults(const struct Student &student);

// ========== Pagination và Navigation ==========
void displayPaginatedStudentTable(const struct Student students[], int totalCount, int currentPage, int pageSize = 15);
void displayPageNavigation(int currentPage, int totalPages, int totalItems);
void printBreadcrumbs(const char* path);
void displayQuickHelp(const char* context);

// ========== Enhanced Error Handling ==========
void displayDetailedError(const char* operation, const char* error, const char* suggestion = nullptr);
void displayValidationError(const char* field, const char* expectedFormat);
void displayProgressMessage(const char* message, bool success = true);

// ========== Interactive Elements ==========
void displayConfirmationDialog(const char* title, const char* message, const char* yesText = "Có", const char* noText = "Không");
void displayInputDialog(const char* title, const char* prompt, char* buffer, int maxLength);
void displaySelectionMenu(const char* title, const char* options[], int optionCount, int defaultSelection = 0);

// ========== Utility functions ==========
void centerText(const char *text, int width);
void centerText(const char *text); // overload with default width
void printLine(char character, int length);
void printLine(const char *character, int length); // overload for Unicode strings

// ========== UTF-8 và text processing helpers ==========
int getDisplayWidth(const char *text); // Tính độ dài hiển thị của chuỗi UTF-8
void printPaddedText(const char *text, int width, bool leftAlign = true); // In text với padding chính xác
std::string truncateText(const char *text, int maxWidth); // Cắt ngắn text nếu quá dài
int safeCalculatePadding(const char *text, int totalWidth, int usedSpace = 0); // Tính padding an toàn

#endif // UI_COMMON_H
