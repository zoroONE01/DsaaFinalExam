# 1. Giới thiệu chung

### 1.1. Mục tiêu dự án

Dự án "Hệ thống Quản lý Sinh viên" được phát triển với mục tiêu chính là ứng dụng và củng cố kiến thức về Cấu trúc Dữ liệu và Giải thuật thông qua việc xây dựng một hệ thống quản lý thông tin sinh viên hoàn chỉnh. Các mục tiêu cụ thể bao gồm:

- **Thực hành cài đặt cấu trúc dữ liệu:** Tự tay cài đặt các cấu trúc dữ liệu cơ bản như mảng động (ArrayStudentList), danh sách liên kết đơn (NodeSLL), danh sách liên kết vòng (NodeSLL), danh sách liên kết đôi (NodeDLL), và cây nhị phân tìm kiếm (NodeBST) mà không sử dụng thư viện STL có sẵn.
- **Áp dụng các thuật toán cơ bản:** Cài đặt thủ công 6 thuật toán sắp xếp (Bubble Sort, Insertion Sort, Selection Sort, Quick Sort, Merge Sort, Heap Sort) và 2 thuật toán tìm kiếm (Sequential Search, Binary Search).
- **Phát triển kỹ năng lập trình thủ tục:** Sử dụng phong cách lập trình thủ tục với C++, tập trung vào việc sử dụng `struct Student` với các trường dữ liệu kiểu mảng ký tự và các hàm độc lập cho từng chức năng.
- **Quản lý bộ nhớ thủ công:** Thực hành quản lý bộ nhớ bằng cách sử dụng `new`/`delete` cho các cấu trúc dữ liệu động và tránh sử dụng các container STL.
- **Xây dựng ứng dụng thực tế:** Tạo ra một hệ thống hoàn chỉnh có thể quản lý thông tin sinh viên với đầy đủ các chức năng CRUD (Create, Read, Update, Delete), thống kê, và các tính năng nâng cao.

### 1.2. Phạm vi dự án

Dự án được chia thành hai phần chính theo yêu cầu của đồ án:

**Phần A - Chức năng bắt buộc (7 điểm):**

1. Đọc dữ liệu sinh viên từ file CSV với kiểm tra tính hợp lệ.
2. Cho phép người dùng lựa chọn cấu trúc dữ liệu lưu trữ (Mảng, DSLK Đơn, Vòng, Đôi).
3. Thêm mới thông tin sinh viên qua giao diện console.
4. Xóa hoặc cập nhật thông tin sinh viên theo mã sinh viên.
5. Thống kê sinh viên: điểm cao nhất, thấp nhất, điểm trung bình lớp, phân loại học lực.
6. Sắp xếp danh sách theo các tiêu chí khác nhau với nhiều thuật toán (cài đặt thủ công).
7. Tìm kiếm sinh viên theo các trường thông tin với các phương pháp khác nhau (cài đặt thủ công).

**Phần B - Chức năng nâng cao (2 điểm):**

**Cây Nhị Phân Tìm Kiếm theo Điểm:** Cài đặt BST hoàn chỉnh với khả năng lưu trữ nhiều sinh viên cùng điểm, bao gồm các thao tác insert, search, delete, và traverse (in-order, pre-order, post-order, level-order).

### 1.3. Môi trường phát triển và Công cụ

- **IDE:** Visual Studio Code (VS Code)
- **Hệ điều hành:** macOS
- **Ngôn ngữ:** C++ với phong cách lập trình thủ tục
- **Trình biên dịch:** Apple Clang/GCC (Thông qua Makefile)
- **Giao diện:** Console-based application (không sử dụng GUI)
- **Quản lý project:** Makefile để biên dịch và liên kết các module.

### 1.4. Đặc điểm kỹ thuật chính

**Cấu trúc dữ liệu Student:**

```cpp
struct Student {
    char studentID[20];    // Mã sinh viên
    char firstName[50];    // Tên
    char lastName[50];     // Họ và tên đệm
    char studentClass[20]; // Lớp
    float score;           // Điểm số
};
```

**Các cấu trúc dữ liệu được cài đặt:**

- **ArrayStudentList:** Danh sách mảng động với quản lý bộ nhớ thủ công
- **NodeSLL:** Danh sách liên kết đơn (Singly Linked List)
- **NodeDLL:** Danh sách liên kết đôi (Doubly Linked List)
- **CircularLinkedList:** Danh sách liên kết vòng
- **NodeBST:** Cây nhị phân tìm kiếm (Binary Search Tree)

**Thuật toán sắp xếp được cài đặt:**

- Bubble Sort, Insertion Sort, Selection Sort
- Quick Sort, Merge Sort, Heap Sort

**Thuật toán tìm kiếm được cài đặt:**

- Sequential Search (Tìm kiếm tuần tự)
- Binary Search (Tìm kiếm nhị phân)

**Chức năng nâng cao:**

- Knight's Tour (Bài toán Mã Đi Tuần) sử dụng thuật toán backtracking
- Binary Search Tree với khả năng lưu trữ nhiều sinh viên cùng điểm

### 1.5. Kiến trúc hệ thống

Dự án được tổ chức theo cấu trúc module rõ ràng:

```
DsaaFinalExam/
├── Makefile
├── build/
├── data/
├── docs/
├── include/
│   ├── algorithms/    # Chứa các thuật toán sắp xếp và tìm kiếm
│   ├── core/         # Chứa các thao tác cốt lõi
│   ├── data_structures/ # Chứa các cấu trúc dữ liệu
│   ├── ui/           # Giao diện người dùng
│   └── utils/        # Các tiện ích
├── src/
│   ├── algorithms/    # Implementation các thuật toán
│   ├── core/         # Implementation các thao tác cốt lõi
│   ├── data_structures/ # Implementation các cấu trúc dữ liệu
│   ├── ui/           # Implementation giao diện
│   └── utils/        # Implementation các tiện ích
└── student_management.dSYM/
```
