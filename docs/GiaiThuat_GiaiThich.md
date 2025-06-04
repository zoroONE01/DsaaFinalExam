# Tài liệu Giải thích Thuật toán trong Hệ thống Quản lý Sinh viên 🧠

## Mục lục

1. [Giới thiệu](#1-giới-thiệu)
2. [Thuật toán CRUD (Create, Read, Update, Delete)](#2-thuật-toán-crud-create-read-update-delete)
3. [Thuật toán Tìm kiếm](#3-thuật-toán-tìm-kiếm)
4. [Thuật toán Sắp xếp](#4-thuật-toán-sắp-xếp)
5. [Thuật toán Xử lý File CSV](#5-thuật-toán-xử-lý-file-csv)
6. [Thuật toán Xác thực Dữ liệu](#6-thuật-toán-xác-thực-dữ-liệu)
7. [Thuật toán Quản lý Bộ nhớ](#7-thuật-toán-quản-lý-bộ-nhớ)
8. [Thuật toán Thống kê](#8-thuật-toán-thống-kê)
9. [So sánh hiệu suất](#9-so-sánh-hiệu-suất)
10. [Kết luận](#10-kết-luận)

---

## 1. Giới thiệu

Trong hệ thống quản lý sinh viên này, chúng ta sử dụng nhiều thuật toán khác nhau để thực hiện các chức năng cốt lõi. Tất cả thuật toán đều được cài đặt thủ công (không sử dụng STL) nhằm mục đích học tập và hiểu sâu về cấu trúc dữ liệu và giải thuật.

### Phân loại thuật toán trong hệ thống

1. **CRUD Operations** - Thao tác cơ bản trên dữ liệu
2. **Search Algorithms** - Thuật toán tìm kiếm
3. **Sorting Algorithms** - Thuật toán sắp xếp
4. **File Processing** - Xử lý file CSV
5. **Data Validation** - Xác thực dữ liệu
6. **Memory Management** - Quản lý bộ nhớ
7. **Statistics** - Tính toán thống kê

---

## 2. Thuật toán CRUD (Create, Read, Update, Delete) 📊

### 2.1. CREATE (Thêm sinh viên)

#### 🎯 Mục đích

Thêm một sinh viên mới vào cấu trúc dữ liệu đã chọn.

#### 🔄 Quy trình hoạt động

```
1. Kiểm tra tính hợp lệ của dữ liệu đầu vào
2. Kiểm tra trùng lặp mã sinh viên
3. Thêm vào cấu trúc dữ liệu tương ứng
4. Thông báo kết quả
```

#### 📈 Độ phức tạp

- **Array List**: O(1) - Thêm vào cuối mảng
- **Singly Linked List**: O(1) - Thêm vào đầu/cuối
- **Circular Linked List**: O(1) - Thêm vào vị trí head
- **Doubly Linked List**: O(1) - Thêm vào đầu/cuối
- **Binary Search Tree**: O(log n) trung bình, O(n) xấu nhất

#### 💡 Ví dụ minh họa (Array List)

```
Ban đầu: [SV1, SV2, SV3] (count = 3)
Thêm SV4: [SV1, SV2, SV3, SV4] (count = 4)
```

### 2.2. READ (Hiển thị sinh viên)

#### 🎯 Mục đích

Hiển thị toàn bộ danh sách sinh viên trong cấu trúc dữ liệu.

#### 🔄 Quy trình hoạt động

```
1. Kiểm tra cấu trúc dữ liệu có rỗng không
2. Duyệt qua tất cả phần tử
3. Hiển thị thông tin từng sinh viên
4. Hiển thị tổng số sinh viên
```

#### 📈 Độ phức tạp

- **Tất cả cấu trúc**: O(n) - Phải duyệt qua tất cả phần tử

#### 💡 Ví dụ minh họa (Linked List)

```
HEAD -> [SV1] -> [SV2] -> [SV3] -> NULL
Duyệt: SV1 → SV2 → SV3
```

### 2.3. UPDATE (Cập nhật sinh viên)

#### 🎯 Mục đích

Cập nhật thông tin của sinh viên dựa trên mã sinh viên.

#### 🔄 Quy trình hoạt động

```
1. Tìm kiếm sinh viên theo mã
2. Nếu tìm thấy: cập nhật thông tin mới
3. Nếu không tìm thấy: thông báo lỗi
4. Thông báo kết quả
```

#### 📈 Độ phức tạp

- **Array List**: O(n) - Tìm kiếm tuần tự
- **Linked Lists**: O(n) - Duyệt từ đầu
- **BST**: O(log n) trung bình

#### 💡 Ví dụ minh họa

```
Tìm SV002:
[SV001, SV002, SV003] → Tìm thấy tại vị trí 1
Cập nhật: SV002.score = 8.5
```

### 2.4. DELETE (Xóa sinh viên)

#### 🎯 Mục đích

Xóa sinh viên khỏi cấu trúc dữ liệu dựa trên mã sinh viên.

#### 🔄 Quy trình hoạt động

```
1. Tìm kiếm sinh viên theo mã
2. Nếu tìm thấy:
   - Xóa phần tử
   - Điều chỉnh cấu trúc (nếu cần)
   - Giải phóng bộ nhớ (đối với linked list)
3. Thông báo kết quả
```

#### 📈 Độ phức tạp

- **Array List**: O(n) - Tìm + dịch chuyển phần tử
- **Singly Linked List**: O(n) - Tìm + xóa
- **Doubly Linked List**: O(n) tìm, O(1) xóa khi biết vị trí
- **Circular Linked List**: O(n) - Xử lý đặc biệt cho vòng

#### 💡 Ví dụ minh họa (Array List)

```
Trước xóa: [SV1, SV2, SV3, SV4]
Xóa SV2:   [SV1, __, SV3, SV4]
Dịch chuyển: [SV1, SV3, SV4, __]
Kết quả:   [SV1, SV3, SV4] (count = 3)
```

---

## 3. Thuật toán Tìm kiếm 🔍

### 3.1. Sequential Search (Tìm kiếm tuần tự)

#### 🎯 Mục đích

Tìm sinh viên bằng cách duyệt tuần tự từ đầu đến cuối.

#### 🔄 Thuật toán

```cpp
int sequentialSearch(array, target) {
    for (int i = 0; i < array.size; i++) {
        if (array[i].studentID == target) {
            return i;  // Tìm thấy
        }
    }
    return -1;  // Không tìm thấy
}
```

#### 📈 Độ phức tạp

- **Thời gian**: O(n)
- **Không gian**: O(1)

#### ✅ Ưu điểm

- Đơn giản, dễ hiểu
- Hoạt động với mọi cấu trúc dữ liệu
- Không yêu cầu dữ liệu được sắp xếp

#### ❌ Nhược điểm

- Chậm với dữ liệu lớn
- Phải duyệt toàn bộ trong trường hợp xấu nhất

### 3.2. Binary Search (Tìm kiếm nhị phân)

#### 🎯 Mục đích

Tìm kiếm nhanh trên mảng đã được sắp xếp.

#### 🔄 Thuật toán

```cpp
int binarySearch(sortedArray, target) {
    int left = 0, right = array.size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (array[mid].score == target) {
            return mid;  // Tìm thấy
        }
        else if (array[mid].score < target) {
            left = mid + 1;  // Tìm bên phải
        }
        else {
            right = mid - 1; // Tìm bên trái
        }
    }
    return -1;  // Không tìm thấy
}
```

#### 📈 Độ phức tạp

- **Thời gian**: O(log n)
- **Không gian**: O(1)

#### ✅ Ưu điểm

- Rất nhanh với dữ liệu lớn
- Hiệu quả cho các thao tác tìm kiếm thường xuyên

#### ❌ Nhược điểm

- Yêu cầu dữ liệu phải được sắp xếp trước
- Chỉ áp dụng được cho mảng (truy cập ngẫu nhiên)

#### 💡 Ví dụ minh họa

```
Mảng đã sắp xếp: [1.5, 3.2, 5.7, 7.8, 9.1]
Tìm 5.7:
  Bước 1: left=0, right=4, mid=2 → array[2]=5.7 ✓
  Kết quả: Tìm thấy tại vị trí 2
```

---

## 4. Thuật toán Sắp xếp 📊

### 4.1. Bubble Sort (Sắp xếp nổi bọt)

#### 🎯 Mục đích

Sắp xếp bằng cách so sánh và hoán đổi các cặp phần tử liền kề.

#### 🔄 Thuật toán

```cpp
void bubbleSort(array) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (array[j].score > array[j+1].score) {
                swap(array[j], array[j+1]);
            }
        }
    }
}
```

#### 📈 Độ phức tạp

- **Thời gian**: O(n²) - Tất cả trường hợp
- **Không gian**: O(1)

#### ✅ Ưu điểm

- Thuật toán ổn định (stable)
- Đơn giản, dễ hiểu
- Phát hiện được dữ liệu đã sắp xếp

#### ❌ Nhược điểm

- Chậm với dữ liệu lớn
- Nhiều phép so sánh và hoán đổi

#### 💡 Ví dụ minh họa

```
Ban đầu: [64, 34, 25, 12, 22]
Lần 1:    [34, 25, 12, 22, 64] (64 "nổi" lên cuối)
Lần 2:    [25, 12, 22, 34, 64] (34 "nổi" lên)
...
Kết quả:  [12, 22, 25, 34, 64]
```

### 4.2. Insertion Sort (Sắp xếp chèn)

#### 🎯 Mục đích

Xây dựng dãy sắp xếp bằng cách chèn từng phần tử vào đúng vị trí.

#### 🔄 Thuật toán

```cpp
void insertionSort(array) {
    for (int i = 1; i < n; i++) {
        Student key = array[i];
        int j = i - 1;
        
        while (j >= 0 && array[j].score > key.score) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }
}
```

#### 📈 Độ phức tạp

- **Thời gian**: O(n) tốt nhất, O(n²) xấu nhất
- **Không gian**: O(1)

#### ✅ Ưu điểm

- Hiệu quả với dữ liệu nhỏ hoặc gần như đã sắp xếp
- Thuật toán ổn định
- Sắp xếp online (có thể sắp xếp khi nhận dữ liệu)

#### ❌ Nhược điểm

- Chậm với dữ liệu lớn và ngẫu nhiên

#### 💡 Ví dụ minh họa

```
Ban đầu: [5, 2, 4, 6, 1, 3]
Bước 1:   [2, 5, 4, 6, 1, 3] (chèn 2)
Bước 2:   [2, 4, 5, 6, 1, 3] (chèn 4)
Bước 3:   [2, 4, 5, 6, 1, 3] (6 đã đúng vị trí)
Bước 4:   [1, 2, 4, 5, 6, 3] (chèn 1)
Bước 5:   [1, 2, 3, 4, 5, 6] (chèn 3)
```

### 4.3. Selection Sort (Sắp xếp chọn)

#### 🎯 Mục đích

Tìm phần tử nhỏ nhất và đặt vào đúng vị trí.

#### 🔄 Thuật toán

```cpp
void selectionSort(array) {
    for (int i = 0; i < n-1; i++) {
        int minIndex = i;
        for (int j = i+1; j < n; j++) {
            if (array[j].score < array[minIndex].score) {
                minIndex = j;
            }
        }
        swap(array[i], array[minIndex]);
    }
}
```

#### 📈 Độ phức tạp

- **Thời gian**: O(n²) - Tất cả trường hợp
- **Không gian**: O(1)

#### ✅ Ưu điểm

- Số lần hoán đổi ít (tối đa n-1 lần)
- Hoạt động tốt khi việc ghi dữ liệu tốn kém

#### ❌ Nhược điểm

- Không ổn định
- Luôn là O(n²) dù dữ liệu đã sắp xếp

### 4.4. Quick Sort (Sắp xếp nhanh)

#### 🎯 Mục đích

Sắp xếp bằng chiến lược "chia để trị" với pivot.

#### 🔄 Thuật toán

```cpp
void quickSort(array, low, high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

int partition(array, low, high) {
    float pivot = array[high].score;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (array[j].score <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i+1], array[high]);
    return i + 1;
}
```

#### 📈 Độ phức tạp

- **Thời gian**: O(n log n) trung bình, O(n²) xấu nhất
- **Không gian**: O(log n) (do đệ quy)

#### ✅ Ưu điểm

- Rất nhanh trong thực tế
- Sắp xếp tại chỗ (in-place)

#### ❌ Nhược điểm

- Không ổn định
- Hiệu suất xấu với dữ liệu đã sắp xếp (nếu chọn pivot đầu/cuối)

#### 💡 Ví dụ minh họa

```
Mảng: [10, 80, 30, 90, 40, 50, 70] (pivot = 70)
Partition: [10, 30, 40, 50] + [70] + [80, 90]
Đệ quy sắp xếp từng phần
```

### 4.5. Merge Sort (Sắp xếp trộn) - Cho Doubly Linked List

#### 🎯 Mục đích

Sắp xếp danh sách liên kết đôi bằng thuật toán chia để trị.

#### 🔄 Thuật toán

```cpp
void mergeSort(NodeDLL** headRef) {
    NodeDLL* head = *headRef;
    NodeDLL* firstHalf, *secondHalf;
    
    if (head == NULL || head->next == NULL) {
        return;  // Danh sách rỗng hoặc 1 phần tử
    }
    
    // Chia đôi danh sách
    split(head, &firstHalf, &secondHalf);
    
    // Đệ quy sắp xếp hai nửa
    mergeSort(&firstHalf);
    mergeSort(&secondHalf);
    
    // Trộn hai nửa đã sắp xếp
    *headRef = merge(firstHalf, secondHalf);
}
```

#### 📈 Độ phức tạp

- **Thời gian**: O(n log n) - Tất cả trường hợp
- **Không gian**: O(log n) (do đệ quy)

#### ✅ Ưu điểm

- Thuật toán ổn định
- Hiệu suất nhất quán O(n log n)
- Phù hợp với linked list

#### ❌ Nhược điểm

- Phức tạp hơn các thuật toán đơn giản
- Cần thêm bộ nhớ cho đệ quy

---

## 5. Thuật toán Xử lý File CSV 📁

### 5.1. Đọc File CSV

#### 🎯 Mục đích

Đọc dữ liệu sinh viên từ file CSV và chuyển đổi thành cấu trúc Student.

#### 🔄 Thuật toán

```cpp
bool readFromCSVFile(filename, studentList) {
    1. Mở file
    2. Kiểm tra file có mở được không
    3. Đọc dòng header (bỏ qua)
    4. Cho mỗi dòng dữ liệu:
       a. Đọc toàn bộ dòng
       b. Tách chuỗi theo dấu phẩy (,)
       c. Gán vào các trường của Student
       d. Thêm vào danh sách
    5. Đóng file
}
```

#### 📈 Độ phức tạp

- **Thời gian**: O(n × m) (n dòng, m ký tự/dòng)
- **Không gian**: O(n) (lưu trữ n sinh viên)

#### 🔧 Xử lý lỗi

- File không tồn tại
- Định dạng dữ liệu không hợp lệ
- Dữ liệu thiếu hoặc thừa cột
- Ký tự đặc biệt trong dữ liệu

#### 💡 Ví dụ CSV

```csv
StudentID,FirstName,LastName,Class,Score
SV001,Nguyen,Van A,CNTT01,8.5
SV002,Tran,Thi B,CNTT02,7.8
```

### 5.2. Parsing CSV

#### 🔄 Thuật toán phân tách chuỗi

```cpp
parseCSVLine(line) {
    1. Sử dụng strtok(line, ",")
    2. Lần lượt lấy từng token
    3. Gán vào các trường:
       - Token 1: StudentID
       - Token 2: FirstName
       - Token 3: LastName
       - Token 4: Class
       - Token 5: Score (chuyển đổi string → float)
}
```

#### 🔧 Xử lý đặc biệt

- Khoảng trắng thừa
- Dấu phẩy trong dữ liệu
- Ký tự Unicode (tiếng Việt)

---

## 6. Thuật toán Xác thực Dữ liệu ✅

### 6.1. Validation Pattern

#### 🎯 Mục đích

Đảm bảo dữ liệu đầu vào hợp lệ trước khi lưu trữ.

#### 🔄 Quy trình chung

```
Input → Validate → Process/Reject
```

### 6.2. Xác thực Mã sinh viên

#### 📋 Quy tắc

- Chứa chữ và số
- Độ dài từ 3 đến MAX_STUDENT_ID_LENGTH-1 ký tự
- Không chứa ký tự đặc biệt

#### 🔄 Thuật toán

```cpp
bool validateStudentID(studentID) {
    1. Kiểm tra độ dài
    2. Kiểm tra ký tự hợp lệ (regex: ^[a-zA-Z0-9]{3,n}$)
    3. Return true/false
}
```

### 6.3. Xác thực Họ tên

#### 📋 Quy tắc

- Chỉ chứa chữ cái, khoảng trắng, dấu gạch ngang
- Hỗ trợ tiếng Việt có dấu
- Độ dài tối đa MAX_NAME_LENGTH-1

#### 🔄 Thuật toán

```cpp
bool validateName(name) {
    1. Kiểm tra độ dài
    2. Kiểm tra ký tự (bao gồm Unicode tiếng Việt)
    3. Không cho phép số hoặc ký tự đặc biệt
}
```

### 6.4. Xác thực Điểm số

#### 📋 Quy tắc

- Giá trị từ MIN_SCORE đến MAX_SCORE
- Thường là 0.0 đến 10.0

#### 🔄 Thuật toán

```cpp
bool validateScore(score) {
    return score >= MIN_SCORE && score <= MAX_SCORE;
}
```

### 6.5. Xác thực Lớp học

#### 📋 Quy tắc

- Định dạng chuẩn (VD: CNTT01, KTPM02)
- Độ dài giới hạn

---

## 7. Thuật toán Quản lý Bộ nhớ 🧠

### 7.1. Cấp phát bộ nhớ (Allocation)

#### 🎯 Mục đích

Cấp phát bộ nhớ cho các node trong linked list và BST.

#### 🔄 Quy trình

```cpp
NodeType* createNode(data) {
    1. Cấp phát bộ nhớ: new NodeType
    2. Khởi tạo dữ liệu
    3. Khởi tạo con trỏ = NULL
    4. Return địa chỉ node
}
```

### 7.2. Giải phóng bộ nhớ (Deallocation)

#### 🎯 Mục đích

Giải phóng toàn bộ bộ nhớ khi thoát chương trình.

#### 🔄 Thuật toán cho Singly Linked List

```cpp
void freeSLL(NodeSLL*& head) {
    while (head != NULL) {
        NodeSLL* temp = head;
        head = head->next;
        delete temp;
    }
}
```

#### 🔄 Thuật toán cho Doubly Linked List

```cpp
void freeDLL(NodeDLL*& head, NodeDLL*& tail) {
    while (head != NULL) {
        NodeDLL* temp = head;
        head = head->next;
        delete temp;
    }
    tail = NULL;
}
```

#### 🔄 Thuật toán cho Circular Linked List

```cpp
void freeCLL(NodeSLL*& head) {
    if (head == NULL) return;
    
    NodeSLL* current = head;
    do {
        NodeSLL* next = current->next;
        delete current;
        current = next;
    } while (current != head);
    
    head = NULL;
}
```

#### 🔄 Thuật toán cho Binary Search Tree

```cpp
void freeBST(NodeBST*& root) {
    if (root != NULL) {
        freeBST(root->left);   // Giải phóng cây con trái
        freeBST(root->right);  // Giải phóng cây con phải
        delete root;           // Giải phóng node hiện tại
        root = NULL;
    }
}
```

### 7.3. Phát hiện Memory Leak

#### 🔧 Chiến lược

- Đảm bảo mỗi `new` có một `delete` tương ứng
- Giải phóng bộ nhớ theo thứ tự đúng
- Sử dụng destructor trong class (nếu có)

---

## 8. Thuật toán Thống kê 📈

### 8.1. Tìm điểm cao nhất

#### 🔄 Thuật toán

```cpp
float findHighestScore(arrayList) {
    if (arrayList.count == 0) return -1;
    
    float maxScore = arrayList.students[0].score;
    for (int i = 1; i < arrayList.count; i++) {
        if (arrayList.students[i].score > maxScore) {
            maxScore = arrayList.students[i].score;
        }
    }
    return maxScore;
}
```

#### 📈 Độ phức tạp: O(n)

### 8.2. Tìm điểm thấp nhất

#### 🔄 Thuật toán

```cpp
float findLowestScore(arrayList) {
    if (arrayList.count == 0) return -1;
    
    float minScore = arrayList.students[0].score;
    for (int i = 1; i < arrayList.count; i++) {
        if (arrayList.students[i].score < minScore) {
            minScore = arrayList.students[i].score;
        }
    }
    return minScore;
}
```

#### 📈 Độ phức tạp: O(n)

### 8.3. Tính điểm trung bình

#### 🔄 Thuật toán

```cpp
float calculateAverageScore(arrayList) {
    if (arrayList.count == 0) return 0;
    
    float totalScore = 0;
    for (int i = 0; i < arrayList.count; i++) {
        totalScore += arrayList.students[i].score;
    }
    return totalScore / arrayList.count;
}
```

#### 📈 Độ phức tạp: O(n)

### 8.4. Đếm sinh viên theo tiêu chí

#### 🔄 Thuật toán

```cpp
int countStudentsWithScore(arrayList, targetScore) {
    int count = 0;
    for (int i = 0; i < arrayList.count; i++) {
        if (arrayList.students[i].score == targetScore) {
            count++;
        }
    }
    return count;
}
```

---

## 9. So sánh hiệu suất ⚡

### 9.1. Bảng so sánh thuật toán sắp xếp

| Thuật toán | Tốt nhất | Trung bình | Xấu nhất | Bộ nhớ | Ổn định |
|------------|----------|------------|----------|---------|---------|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | ✅ |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | ✅ |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | ❌ |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | ❌ |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | ✅ |

### 9.2. Bảng so sánh thuật toán tìm kiếm

| Thuật toán | Độ phức tạp | Điều kiện | Ưu điểm | Nhược điểm |
|------------|-------------|-----------|---------|------------|
| Sequential | O(n) | Không yêu cầu | Đơn giản, hoạt động với mọi cấu trúc | Chậm |
| Binary Search | O(log n) | Dữ liệu đã sắp xếp | Rất nhanh | Yêu cầu sắp xếp trước |

### 9.3. Hiệu suất theo cấu trúc dữ liệu

#### Array List

- ✅ **Ưu điểm**: Truy cập nhanh O(1), cache-friendly
- ❌ **Nhược điểm**: Chèn/xóa giữa mảng O(n), kích thước cố định

#### Singly Linked List

- ✅ **Ưu điểm**: Chèn/xóa đầu O(1), kích thước linh hoạt
- ❌ **Nhược điểm**: Truy cập tuần tự O(n), tốn bộ nhớ cho pointer

#### Doubly Linked List

- ✅ **Ưu điểm**: Duyệt hai chiều, xóa node O(1) khi biết vị trí
- ❌ **Nhược điểm**: Tốn nhiều bộ nhớ hơn (2 pointer/node)

#### Circular Linked List

- ✅ **Ưu điểm**: Duyệt vòng tròn, tiết kiệm 1 pointer so với doubly
- ❌ **Nhược điểm**: Dễ tạo vòng lặp vô hạn, phức tạp hơn

---

## 10. Kết luận 🎯

### 10.1. Điểm mạnh của hệ thống

1. **Đa dạng thuật toán**: Cài đặt nhiều thuật toán khác nhau cho cùng một mục đích
2. **Tối ưu cho từng cấu trúc**: Mỗi cấu trúc dữ liệu có thuật toán phù hợp
3. **Xử lý lỗi tốt**: Validation đầy đủ, thông báo lỗi rõ ràng
4. **Quản lý bộ nhớ**: Cấp phát và giải phóng bộ nhớ chính xác

### 10.2. Bài học về hiệu suất

1. **Không có thuật toán nào tối ưu cho mọi trường hợp**
2. **Lựa chọn cấu trúc dữ liệu ảnh hưởng lớn đến hiệu suất**
3. **Trade-off giữa thời gian và bộ nhớ luôn tồn tại**
4. **Thuật toán đơn giản đôi khi hiệu quả hơn với dữ liệu nhỏ**

### 10.3. Khuyến nghị sử dụng

#### Cho dữ liệu nhỏ (< 100 sinh viên)

- **Cấu trúc**: Array List
- **Sắp xếp**: Insertion Sort hoặc Selection Sort
- **Tìm kiếm**: Sequential Search

#### Cho dữ liệu trung bình (100-1000 sinh viên)

- **Cấu trúc**: Array List hoặc Doubly Linked List
- **Sắp xếp**: Quick Sort (Array), Merge Sort (Linked List)
- **Tìm kiếm**: Binary Search (sau khi sắp xếp)

#### Cho dữ liệu lớn (> 1000 sinh viên)

- **Cấu trúc**: Binary Search Tree hoặc Hash Table (nếu có)
- **Sắp xếp**: Merge Sort hoặc Heap Sort
- **Tìm kiếm**: Binary Search Tree traversal

### 10.4. Hướng phát triển

1. **Thêm thuật toán mới**: Heap Sort, Radix Sort
2. **Tối ưu hóa**: Hybrid sorting, adaptive algorithms
3. **Đa luồng**: Parallel sorting algorithms
4. **Cấu trúc nâng cao**: AVL Tree, Red-Black Tree, Hash Table

---

## 📚 Tài liệu tham khảo

- Introduction to Algorithms (CLRS)
- Data Structures and Algorithm Analysis in C++ (Mark Allen Weiss)
- Algorithms (Robert Sedgewick)
- Tài liệu môn Cấu trúc Dữ liệu và Giải thuật - PTIT

---

**📝 Ghi chú**: Tài liệu này tập trung vào việc giải thích các thuật toán đã được cài đặt trong hệ thống quản lý sinh viên. Mỗi thuật toán đều có ví dụ cụ thể và phân tích độ phức tạp để hỗ trợ việc học tập và hiểu sâu về cấu trúc dữ liệu và giải thuật.
