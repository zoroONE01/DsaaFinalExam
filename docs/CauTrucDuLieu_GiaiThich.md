# Tài liệu Giải thích Cấu trúc Dữ liệu trong Hệ thống Quản lý Sinh viên

## Tổng quan

Dự án hệ thống quản lý sinh viên này sử dụng **5 cấu trúc dữ liệu chính** để lưu trữ và quản lý thông tin sinh viên. Mỗi cấu trúc có ưu nhược điểm riêng và phù hợp với các tình huống sử dụng khác nhau.

---

## 1. Danh sách Mảng (Array List) 📊

### Khái niệm

Danh sách mảng là cấu trúc dữ liệu đơn giản nhất, lưu trữ các sinh viên trong một mảng có kích thước cố định.

### Cấu trúc

```cpp
struct ArrayStudentList {
    Student students[MAX_STUDENTS];  // Mảng chứa sinh viên
    int count;                       // Số lượng sinh viên hiện tại
};
```

### Minh họa trực quan

```
Index:  [0]    [1]    [2]    [3]    [4]    ...
Data:   [SV1]  [SV2]  [SV3]  [SV4]  [   ]  ...
        ↑                           ↑
      Đầu                        Vị trí trống
      count = 4
```

### Ưu điểm ✅

- **Truy cập nhanh**: Có thể truy cập bất kỳ sinh viên nào trong O(1) thông qua chỉ số
- **Đơn giản**: Dễ hiểu và triển khai
- **Bộ nhớ liên tục**: Các phần tử được lưu trữ liên tiếp trong bộ nhớ
- **Hỗ trợ tìm kiếm nhị phân**: Khi đã sắp xếp, có thể tìm kiếm trong O(log n)

### Nhược điểm ❌

- **Kích thước cố định**: Không thể mở rộng khi cần
- **Lãng phí bộ nhớ**: Phải cấp phát bộ nhớ cho số lượng tối đa
- **Chèn/xóa chậm**: Phải dịch chuyển các phần tử (O(n))

### Thích hợp khi

- Biết trước số lượng sinh viên tối đa
- Cần truy cập ngẫu nhiên nhanh
- Ít thao tác chèn/xóa ở giữa

---

## 2. Danh sách Liên kết Đơn (Singly Linked List) 🔗

### Khái niệm

Danh sách liên kết đơn là chuỗi các node, mỗi node chứa dữ liệu sinh viên và con trỏ tới node tiếp theo.

### Cấu trúc

```cpp
struct NodeSLL {
    Student info;    // Thông tin sinh viên
    NodeSLL *next;   // Con trỏ tới node tiếp theo
};
```

### Minh họa trực quan

```
HEAD → [SV1|next] → [SV2|next] → [SV3|next] → [SV4|NULL]
       ↑             ↑             ↑             ↑
    Node đầu      Node thứ 2    Node thứ 3    Node cuối
```

### Ưu điểm ✅

- **Kích thước động**: Có thể thêm/bớt node tùy ý
- **Tiết kiệm bộ nhớ**: Chỉ cấp phát khi cần
- **Chèn/xóa ở đầu nhanh**: O(1) time complexity
- **Không giới hạn kích thước**: Chỉ bị hạn chế bởi bộ nhớ hệ thống

### Nhược điểm ❌

- **Truy cập chậm**: Phải duyệt từ đầu để tìm phần tử (O(n))
- **Bộ nhớ không liên tục**: Các node có thể rải rác trong bộ nhớ
- **Tốn bộ nhớ cho con trỏ**: Mỗi node cần thêm 8 bytes cho con trỏ
- **Không hỗ trợ tìm kiếm nhị phân**: Do không truy cập ngẫu nhiên được

### Thích hợp khi

- Không biết trước số lượng sinh viên
- Thường xuyên thêm/xóa ở đầu danh sách
- Ít cần truy cập ngẫu nhiên

---

## 3. Danh sách Liên kết Vòng (Circular Linked List) 🔄

### Khái niệm

Giống danh sách liên kết đơn nhưng node cuối trỏ về node đầu, tạo thành một vòng tròn.

### Cấu trúc

Sử dụng lại cấu trúc `NodeSLL` nhưng node cuối trỏ về node đầu thay vì NULL.

### Minh họa trực quan

```
       ┌─────────────────────────┐
       ↓                         │
HEAD → [SV1|next] → [SV2|next] → [SV3|next]
       ↑                         │
       └─────────────────────────┘
```

### Ưu điểm ✅

- **Tất cả ưu điểm của linked list đơn**
- **Duyệt vòng tròn**: Có thể duyệt liên tục không bị giới hạn
- **Không có node NULL**: Mọi node đều có next hợp lệ
- **Phù hợp với thuật toán vòng tròn**: Ví dụ như Round Robin scheduling

### Nhược điểm ❌

- **Tất cả nhược điểm của linked list đơn**
- **Dễ bị vòng lặp vô hạn**: Nếu không cẩn thận khi duyệt
- **Phức tạp hơn**: Cần xử lý đặc biệt cho các thao tác

### Thích hợp khi

- Cần duyệt danh sách theo vòng tròn
- Triển khai hàng đợi vòng (circular queue)
- Các thuật toán cần xử lý tuần hoàn

---

## 4. Danh sách Liên kết Đôi (Doubly Linked List) ↔️

### Khái niệm

Mỗi node có hai con trỏ: một trỏ tới node trước, một trỏ tới node sau.

### Cấu trúc

```cpp
struct NodeDLL {
    Student info;    // Thông tin sinh viên
    NodeDLL *next;   // Con trỏ tới node tiếp theo
    NodeDLL *prev;   // Con trỏ tới node trước đó
};
```

### Minh họa trực quan

```
HEAD ↔ [NULL|SV1|next] ↔ [prev|SV2|next] ↔ [prev|SV3|next] ↔ [prev|SV4|NULL] ← TAIL
       ↑                 ↑                 ↑                 ↑
    Node đầu          Node thứ 2        Node thứ 3        Node cuối
```

### Ưu điểm ✅

- **Duyệt hai chiều**: Có thể đi từ đầu xuống cuối hoặc ngược lại
- **Xóa node nhanh**: Khi biết địa chỉ node, xóa trong O(1)
- **Chèn ở cuối nhanh**: O(1) với con trỏ tail
- **Linh hoạt**: Hỗ trợ nhiều thuật toán phức tạp

### Nhược điểm ❌

- **Tốn bộ nhớ nhiều hơn**: Mỗi node cần 2 con trỏ (16 bytes)
- **Phức tạp hơn**: Phải quản lý cả next và prev
- **Vẫn truy cập chậm**: O(n) để tìm phần tử

### Thích hợp khi

- Cần duyệt cả hai chiều
- Thường xuyên thêm/xóa ở cả đầu và cuối
- Triển khai các thuật toán sắp xếp như Merge Sort

---

## 5. Cây Tìm kiếm Nhị phân (Binary Search Tree) 🌳

### Khái niệm

Cây nhị phân đặc biệt được tổ chức theo điểm số: node trái có điểm nhỏ hơn, node phải có điểm lớn hơn.

### Cấu trúc

```cpp
struct NodeBST {
    float key;                                // Điểm số làm khóa
    Student students[MAX_STUDENTS_PER_SCORE]; // Sinh viên có cùng điểm
    int count;                                // Số sinh viên trong node
    NodeBST *left;                            // Cây con trái
    NodeBST *right;                           // Cây con phải
};
```

### Minh họa trực quan

```
                [7.5, 2 sinh viên]
               /                  \
        [6.0, 1 SV]              [8.5, 3 SV]
       /           \            /           \
  [5.0, 1 SV]  [6.8, 2 SV]  [8.0, 1 SV]  [9.0, 1 SV]
```

### Ưu điểm ✅

- **Tìm kiếm nhanh**: O(log n) trong trường hợp cân bằng
- **Sắp xếp tự động**: Duyệt in-order cho kết quả đã sắp xếp
- **Nhóm theo điểm**: Sinh viên cùng điểm được lưu trong một node
- **Linh hoạt**: Hỗ trợ nhiều cách duyệt (pre-order, in-order, post-order)

### Nhược điểm ❌

- **Có thể mất cân bằng**: Worst case O(n) khi cây thành dạng list
- **Phức tạp**: Khó triển khai so với các cấu trúc khác
- **Không phù hợp tìm theo ID**: Chỉ tối ưu khi tìm theo điểm số
- **Bộ nhớ cho con trỏ**: Mỗi node cần 2 con trỏ

### Thích hợp khi

- Cần tìm kiếm sinh viên theo điểm số thường xuyên
- Muốn nhóm sinh viên có cùng điểm
- Cần duyệt sinh viên theo thứ tự điểm số

---

## So sánh Hiệu suất

| Thao tác | Array | Singly LL | Circular LL | Doubly LL | BST |
|----------|--------|-----------|-------------|-----------|-----|
| **Truy cập** | O(1) | O(n) | O(n) | O(n) | O(log n) |
| **Tìm kiếm** | O(n) | O(n) | O(n) | O(n) | O(log n) |
| **Chèn đầu** | O(n) | O(1) | O(1) | O(1) | - |
| **Chèn cuối** | O(1) | O(n) | O(n) | O(1) | - |
| **Chèn BST** | - | - | - | - | O(log n) |
| **Xóa** | O(n) | O(n) | O(n) | O(1)* | O(log n) |
| **Bộ nhớ** | Cố định | Động | Động | Động | Động |

*O(1) khi biết địa chỉ node cần xóa

---

## Khi nào nên sử dụng cấu trúc nào?

### 🎯 Chọn Array List khi

- Số lượng sinh viên ít và cố định
- Cần truy cập nhanh theo chỉ số
- Thường xuyên tìm kiếm nhị phân

### 🎯 Chọn Singly Linked List khi

- Số lượng sinh viên thay đổi thường xuyên
- Chủ yếu thêm sinh viên vào đầu danh sách
- Bộ nhớ hệ thống hạn chế

### 🎯 Chọn Circular Linked List khi

- Cần duyệt danh sách theo vòng tròn
- Triển khai hệ thống quản lý theo lượt

### 🎯 Chọn Doubly Linked List khi

- Cần duyệt cả hai chiều
- Thường xuyên sắp xếp danh sách
- Thêm/xóa ở cả đầu và cuối

### 🎯 Chọn Binary Search Tree khi

- Tìm kiếm theo điểm số là ưu tiên
- Cần nhóm sinh viên theo điểm
- Muốn duyệt theo thứ tự điểm số

---

## Lời khuyên thực tế

1. **Bắt đầu đơn giản**: Sử dụng Array List cho các dự án nhỏ
2. **Phân tích nhu cầu**: Xác định thao tác nào được sử dụng nhiều nhất
3. **Cân nhắc bộ nhớ**: Doubly Linked List tốn bộ nhớ gấp đôi Singly
4. **Hiệu suất vs Phức tạp**: BST nhanh nhưng khó triển khai
5. **Test thực tế**: Đo lường hiệu suất với dữ liệu thật

---

*Tài liệu này giải thích các cấu trúc dữ liệu được sử dụng trong hệ thống quản lý sinh viên. Mỗi cấu trúc có điểm mạnh riêng và phù hợp với các tình huống khác nhau.*
