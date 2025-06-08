# 4. Hiện thực Chức năng Nâng cao (Phần B)

### 4.1. Hệ Thống Thuật Toán Sắp Xếp Nâng Cao

**Mô tả:** Hệ thống quản lý sinh viên tích hợp một bộ sưu tập hoàn chỉnh các thuật toán sắp xếp nâng cao, bao gồm cả các thuật toán cơ bản và nâng cao với khả năng đo lường hiệu suất thời gian thực.

**Các thuật toán được hỗ trợ:**

- **Thuật toán cơ bản:** Bubble Sort, Selection Sort, Insertion Sort
- **Thuật toán nâng cao:** Quick Sort, Merge Sort, Heap Sort
- **Đo lường hiệu suất:** Sử dụng `chrono::high_resolution_clock` để đo thời gian thực thi
- **Linh hoạt:** Hỗ trợ sắp xếp theo nhiều tiêu chí (mã SV, tên, điểm số)

**Hàm so sánh sinh viên:**

Hệ thống sử dụng hàm so sánh linh hoạt để hỗ trợ nhiều tiêu chí sắp xếp. Theo cài đặt trong `src/algorithms/array_sorting.cpp` (dòng 8-30):

```cpp
// Hàm so sánh hai sinh viên theo tiêu chí được chọn
bool compareStudents(const Student &a, const Student &b, int sortCriteria)
{
    switch (sortCriteria)
    {
    case SORT_BY_STUDENT_ID:
        return strcmp(a.studentID, b.studentID) < 0; // So sánh mã sinh viên
    case SORT_BY_NAME:
        // So sánh theo tên (lastName + firstName)
        {
            int lastNameCmp = strcmp(a.lastName, b.lastName);
            if (lastNameCmp != 0)
                return lastNameCmp < 0;
            return strcmp(a.firstName, b.firstName) < 0;
        }
    case SORT_BY_SCORE:
        return a.score < b.score; // So sánh điểm số
    default:
        return a.score < b.score; // Mặc định so sánh theo điểm
    }
}
```

**Thuật toán Quick Sort:**

Quick Sort là thuật toán sắp xếp nâng cao sử dụng chiến lược "chia để trị" với độ phức tạp trung bình O(n log n).

Theo cài đặt trong `src/algorithms/array_sorting.cpp`:

```cpp
// Thuật toán Quick Sort cho danh sách mảng sinh viên
void quickSortArrayList(ArrayStudentList &list, int sortCriteria)
{
    // Kiểm tra điều kiện đầu vào
    if (list.count <= 1)
    {
        return; // Danh sách rỗng hoặc có 1 phần tử đã được sắp xếp
    }

    // Gọi hàm đệ quy để sắp xếp toàn bộ mảng
    quickSortArrayListHelper(list, 0, list.count - 1, sortCriteria);
}
```

**Thuật toán Merge Sort:**

Merge Sort đảm bảo độ phức tạp O(n log n) trong mọi trường hợp.

Theo cài đặt trong `src/algorithms/array_sorting.cpp`:

```cpp
// Thuật toán Merge Sort cho danh sách mảng sinh viên
void mergeSortArrayList(ArrayStudentList &list, int sortCriteria)
{
    // Kiểm tra điều kiện đầu vào
    if (list.count <= 1)
        return; // Danh sách rỗng hoặc có 1 phần tử đã được sắp xếp

    // Gọi hàm đệ quy để sắp xếp toàn bộ mảng
    mergeSortArrayListHelper(list, 0, list.count - 1, sortCriteria);
}
```

**Đo lường hiệu suất thời gian thực:**

Hệ thống tích hợp khả năng đo lường hiệu suất trong `src/main.cpp` (dòng 452-459):

```cpp
// Đo thời gian thực thi
chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

bool success = sortStudentList(dataStructureType, sortAlgorithm, sortCriteria, arrayList,
                               singlyLinkedList, circularLinkedList, doublyLinkedListHead,
                               doublyLinkedListTail);

chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(end - start);
```

### 4.2. Cây Nhị Phân Tìm Kiếm theo Điểm (BST)

**Mô tả:** Cài đặt một Cây Nhị Phân Tìm Kiếm (Binary Search Tree) sử dụng điểm số sinh viên làm khóa để tổ chức dữ liệu. Cây BST cho phép tìm kiếm, thêm, và xóa sinh viên theo điểm số với độ phức tạp trung bình O(log n).

**Cấu trúc Node của BST:**

Theo định nghĩa trong `include/data_structures/binary_search_tree.h` (dòng 16-22):

```cpp
// Định nghĩa cấu trúc node cho cây BST
#ifndef NODE_BST_DEFINED
#define NODE_BST_DEFINED
struct NodeBST
{
    float key;                                // Điểm số làm khóa
    Student students[MAX_STUDENTS_PER_SCORE]; // Danh sách sinh viên có điểm số này
    int count;                                // Số lượng sinh viên trong node này
    NodeBST *left;                            // Con trỏ tới node con bên trái
    NodeBST *right;                           // Con trỏ tới node con bên phải
};
#endif
```

**Hàm chèn sinh viên vào BST:**

Theo cài đặt trong `src/data_structures/binary_search_tree.cpp` (dòng 49-102):

```cpp
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
```

**Hàm tìm kiếm trong BST:**

Theo cài đặt trong `src/data_structures/binary_search_tree.cpp` (dòng 167-183):

```cpp
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
```

**Duyệt cây theo thứ tự tăng dần (In-order Traversal):**

Theo cài đặt trong `src/data_structures/binary_search_tree.cpp` (dòng 141-151):

```cpp
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
```

### 4.3. Hệ Thống Tìm Kiếm Nâng Cao với Đo Lường Hiệu Suất

**Mô tả:** Hệ thống tích hợp các thuật toán tìm kiếm nâng cao với khả năng đo lường hiệu suất thời gian thực, hỗ trợ cả tìm kiếm tuần tự và tìm kiếm nhị phân có tối ưu hóa cho nhiều tiêu chí khác nhau.

**Các tính năng nâng cao:**

- **Tìm kiếm tuần tự:** Cho dữ liệu chưa sắp xếp với độ phức tạp O(n)
- **Tìm kiếm nhị phân:** Cho dữ liệu đã sắp xếp với độ phức tạp O(log n)
- **Đo lường hiệu suất:** Sử dụng timer precision cao để so sánh hiệu suất
- **Tìm kiếm mờ:** Hỗ trợ tìm kiếm không phân biệt hoa thường với partial matching
- **Đa tiêu chí:** Hỗ trợ tìm kiếm theo mã SV, tên, họ, lớp, và điểm số

**Cấu trúc kết quả tìm kiếm:**

Theo định nghĩa trong `include/algorithms/searching.h` (dòng 15-25):

```cpp
// Cấu trúc kết quả tìm kiếm
struct SearchResult
{
    Student *students;   // Mảng sinh viên tìm được
    int count;           // Số lượng sinh viên tìm được
    double searchTimeMs; // Thời gian tìm kiếm (milliseconds)
    bool isBinarySearch; // Có sử dụng tìm kiếm nhị phân không
};

// Cấu trúc timer cho đo lường hiệu suất
struct SearchTimer
{
    long long startTime; // Thời gian bắt đầu (microseconds)
    long long endTime;   // Thời gian kết thúc (microseconds)
};
```

**Hàm đo lường thời gian tìm kiếm:**

Theo cài đặt trong `src/algorithms/searching.cpp` (dòng 154-168):

```cpp
// Bắt đầu đo thời gian
SearchTimer startTimer()
{
    SearchTimer timer;
    chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
    timer.startTime = chrono::duration_cast<chrono::microseconds>(now.time_since_epoch()).count();
    timer.endTime = 0;
    return timer;
}

// Dừng đo thời gian
void stopTimer(SearchTimer &timer)
{
    chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
    timer.endTime = chrono::duration_cast<chrono::microseconds>(now.time_since_epoch()).count();
}

// Tính thời gian đã trôi qua (milliseconds)
double getElapsedTimeMs(const SearchTimer &timer)
{
    return static_cast<double>(timer.endTime - timer.startTime) / 1000.0;
}
```

**Hàm kiểm tra khả năng sử dụng Binary Search:**

Theo cài đặt trong `src/algorithms/searching.cpp` (dòng 134-142):

```cpp
// Kiểm tra xem có thể sử dụng binary search không
bool canUseBinarySearch(int searchCriteria, int sortCriteria, bool isSorted)
{
    if (!isSorted)
        return false;

    int requiredSortCriteria = mapSearchToSortCriteria(searchCriteria);
    return (requiredSortCriteria != -1 && requiredSortCriteria == sortCriteria);
}
```

**Thuật toán tìm kiếm nhị phân tối ưu:**

Theo cài đặt trong `src/algorithms/searching.cpp` (dòng 225-295):

```cpp
// Tìm kiếm nhị phân trong mảng đã sắp xếp
SearchResult binarySearchArray(const ArrayStudentList &list, const char *keyword, 
                              int searchCriteria, int sortCriteria)
{
    SearchResult result;
    result.students = nullptr;
    result.count = 0;
    result.isBinarySearch = true;

    SearchTimer timer = startTimer();

    // Kiểm tra xem có thể sử dụng binary search không
    if (!canUseBinarySearch(searchCriteria, sortCriteria, true))
    {
        result.isBinarySearch = false;
        stopTimer(timer);
        return sequentialSearch(const_cast<Student *>(list.students), list.count, keyword, searchCriteria);
    }

    // Thực hiện binary search theo từng tiêu chí
    if (searchCriteria == SEARCH_BY_SCORE && sortCriteria == SORT_BY_SCORE)
    {
        // Binary search cho điểm số
        float searchScore = atof(keyword);
        int left = 0, right = list.count - 1;
        int foundIndex = -1;

        while (left <= right)
        {
            int mid = (left + right) / 2;
            float midScore = list.students[mid].score;

            if (midScore == searchScore)
            {
                foundIndex = mid;
                break;
            }
            else if (midScore < searchScore)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        if (foundIndex != -1)
        {
            // Tìm tất cả sinh viên có cùng điểm số
            int startIndex = foundIndex, endIndex = foundIndex;

            // Tìm về phía trước
            while (startIndex > 0 && list.students[startIndex - 1].score == searchScore)
            {
                startIndex--;
            }

            // Tìm về phía sau
            while (endIndex < list.count - 1 && list.students[endIndex + 1].score == searchScore)
            {
                endIndex++;
            }

            result.count = endIndex - startIndex + 1;
            result.students = new Student[result.count];

            for (int i = 0; i < result.count; i++)
            {
                result.students[i] = list.students[startIndex + i];
            }
        }
    }
    
    stopTimer(timer);
    result.searchTimeMs = getElapsedTimeMs(timer);
    return result;
}
```

**Hàm kiểm tra khớp tiêu chí tìm kiếm:**

Theo cài đặt trong `src/algorithms/searching.cpp` (dòng 64-87):

```cpp
// Kiểm tra sinh viên có khớp với tiêu chí tìm kiếm không
bool checkStudentMatch(const Student &student, const char *keyword, int searchCriteria)
{
    if (!keyword || strlen(keyword) == 0)
        return true;

    switch (searchCriteria)
    {
    case SEARCH_BY_STUDENT_ID:
        return containsIgnoreCase(student.studentID, keyword);
    case SEARCH_BY_FIRST_NAME:
        return containsIgnoreCase(student.firstName, keyword);
    case SEARCH_BY_LAST_NAME:
        return containsIgnoreCase(student.lastName, keyword);
    case SEARCH_BY_CLASS:
        return containsIgnoreCase(student.studentClass, keyword);
    case SEARCH_BY_SCORE:
    {
        float searchScore = atof(keyword);
        return (student.score >= searchScore - 0.01 && student.score <= searchScore + 0.01);
    }
    default:
        return false;
    }
}
```

**Tìm kiếm mờ không phân biệt hoa thường:**

Theo cài đặt trong `src/algorithms/searching.cpp` (dòng 18-34):

```cpp
// So sánh chuỗi không phân biệt hoa thường
bool compareIgnoreCase(const char *str1, const char *str2)
{
    if (!str1 || !str2)
        return false;

    while (*str1 && *str2)
    {
        if (tolower(*str1) != tolower(*str2))
        {
            return false;
        }
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

// Kiểm tra chuỗi con (không phân biệt hoa thường)
bool containsIgnoreCase(const char *str, const char *substring)
{
    if (!str || !substring)
        return false;
    if (strlen(substring) == 0)
        return true;

    int strLen = strlen(str);
    int subLen = strlen(substring);

    for (int i = 0; i <= strLen - subLen; i++)
    {
        bool match = true;
        for (int j = 0; j < subLen; j++)
        {
            if (tolower(str[i + j]) != tolower(substring[j]))
            {
                match = false;
                break;
            }
        }
        if (match)
            return true;
    }
    return false;
}
```

**Tìm kiếm trong các cấu trúc dữ liệu khác:**

**1. Tìm kiếm trong Singly Linked List:**

Theo cài đặt trong `src/algorithms/searching.cpp` (dòng 435-467):

```cpp
// Tìm kiếm trong Singly Linked List (luôn dùng tìm kiếm tuần tự)
SearchResult sequentialSearchSLL(NodeSLL *head, const char *keyword, int searchCriteria)
{
    SearchResult result;
    result.students = nullptr;
    result.count = 0;
    result.isBinarySearch = false;

    SearchTimer timer = startTimer();

    // Đếm số lượng kết quả trước
    int matchCount = 0;
    NodeSLL *current = head;
    while (current != nullptr)
    {
        if (checkStudentMatch(current->info, keyword, searchCriteria))
        {
            matchCount++;
        }
        current = current->next;
    }

    if (matchCount > 0)
    {
        result.students = new Student[matchCount];
        result.count = matchCount;

        int resultIndex = 0;
        current = head;
        while (current != nullptr)
        {
            if (checkStudentMatch(current->info, keyword, searchCriteria))
            {
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
```

**2. Tìm kiếm trong Doubly Linked List với Binary Search:**

Hệ thống hỗ trợ binary search cho Doubly Linked List đã sắp xếp:

```cpp
// Tìm kiếm trong Doubly Linked List với khả năng binary search
SearchResult searchDoublyLinkedList(NodeDLL *head, const char *keyword, 
                                   int searchCriteria, bool isSorted, int sortCriteria)
{
    SearchResult result;
    result.students = nullptr;
    result.count = 0;
    result.isBinarySearch = false;

    SearchTimer timer = startTimer();

    // Kiểm tra xem có thể dùng binary search không
    bool useBinarySearch = canUseBinarySearch(searchCriteria, sortCriteria, isSorted);

    if (useBinarySearch && (searchCriteria == SEARCH_BY_SCORE || searchCriteria == SEARCH_BY_STUDENT_ID))
    {
        result.isBinarySearch = true;

        // Đếm tổng số node
        int totalNodes = 0;
        NodeDLL *temp = head;
        while (temp != nullptr)
        {
            totalNodes++;
            temp = temp->next;
        }

        if (searchCriteria == SEARCH_BY_SCORE)
        {
            float searchScore = atof(keyword);
            // Thực hiện binary search trên doubly linked list
            // ... logic binary search ...
        }
    }
    else
    {
        // Fallback về sequential search
        result.isBinarySearch = false;
        // ... logic sequential search ...
    }

    stopTimer(timer);
    result.searchTimeMs = getElapsedTimeMs(timer);
    return result;
}
```

### 4.4. Tích Hợp Đa Cấu Trúc Dữ Liệu

**Mô tả:** Hệ thống hỗ trợ đa dạng các cấu trúc dữ liệu với thuật toán sắp xếp và tìm kiếm riêng biệt được tối ưu hóa cho từng loại:

**Các cấu trúc được hỗ trợ:**

- **Array List:** Mảng động với các thuật toán sắp xếp cơ bản và nâng cao, hỗ trợ binary search
- **Singly Linked List:** Danh sách liên kết đơn với thuật toán sắp xếp được tối ưu, chỉ hỗ trợ sequential search
- **Doubly Linked List:** Danh sách liên kết đôi với sắp xếp hai chiều và binary search
- **Circular Linked List:** Danh sách liên kết vòng với xử lý đặc biệt, chỉ hỗ trợ sequential search
- **Binary Search Tree:** Cây nhị phân tìm kiếm với sắp xếp tự động theo điểm số

**Ví dụ sắp xếp cho Singly Linked List:**

Theo cài đặt trong `src/algorithms/singly_linked_list_sorting.cpp`:

```cpp
// Merge Sort cho Singly Linked List
NodeSLL* mergeSortSinglyLinkedList(NodeSLL* head, int sortCriteria)
{
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    // Chia danh sách thành hai phần
    NodeSLL* middle = getMiddleNode(head);
    NodeSLL* nextToMiddle = middle->next;
    middle->next = NULL;
    
    // Đệ quy sắp xếp hai phần
    NodeSLL* left = mergeSortSinglyLinkedList(head, sortCriteria);
    NodeSLL* right = mergeSortSinglyLinkedList(nextToMiddle, sortCriteria);
    
    // Hợp nhất hai phần đã sắp xếp
    return mergeTwoSortedLists(left, right, sortCriteria);
}
```

**Hiệu suất và So sánh:**

| Cấu trúc dữ liệu | Sắp xếp | Tìm kiếm Sequential | Tìm kiếm Binary |
|------------------|---------|-------------------|-----------------|
| Array List | O(n log n) | O(n) | O(log n) |
| Singly Linked List | O(n log n) | O(n) | Không hỗ trợ |
| Doubly Linked List | O(n log n) | O(n) | O(log n) |
| Circular Linked List | O(n log n) | O(n) | Không hỗ trợ |
| Binary Search Tree | O(log n) | O(n) | O(log n) |

**Tổng kết:**

Hệ thống quản lý sinh viên đã cài đặt thành công nhiều thuật toán nâng cao:

- **6 thuật toán sắp xếp** với đo lường hiệu suất thời gian thực
- **Cây BST** với các phép duyệt và tìm kiếm theo điểm số
- **Tìm kiếm nâng cao** với binary search và sequential search tối ưu
- **Đa cấu trúc dữ liệu** với thuật toán riêng biệt cho từng loại
- **Đo lường hiệu suất** thời gian thực với độ chính xác microsecond
- **Tìm kiếm mờ** không phân biệt hoa thường với partial matching
- **Tích hợp linh hoạt** giữa các thuật toán và cấu trúc dữ liệu khác nhau
