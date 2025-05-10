# Data Structures and Algorithms - PTIT

## Tổng hợp giáo trình Cấu trúc dữ liệu và Giải thuật PTIT

Dưới đây là tổng hợp nội dung từ các slide bài giảng môn Cấu trúc dữ liệu và Giải thuật của trường PTIT, bao gồm các ví dụ minh họa.

### Chương 1: Tổng quan về cấu trúc dữ liệu và giải thuật

Chương này giới thiệu các khái niệm cơ bản về dữ liệu, cấu trúc dữ liệu và giải thuật.

* **Dữ liệu (Data):** Thông tin được dịch sang định dạng hiệu quả cho việc di chuyển/xử lý[cite: 473].
* **Cấu trúc dữ liệu (Data Structure):** Phương pháp lưu trữ dữ liệu trong máy tính để sử dụng hiệu quả dữ liệu này[cite: 473]. Vai trò của cấu trúc dữ liệu[cite: 442]:
  * Đóng vai trò quan trọng trong việc kết hợp thuật toán để đưa ra cách giải quyết bài toán.
  * Hỗ trợ các thuật toán thao tác trên các đối tượng hiệu quả hơn.
  * **Tiêu chuẩn:** Phản ánh đúng thực tế, phù hợp với các thao tác của chương trình, tiết kiệm tài nguyên hệ thống.
* **Các loại cấu trúc dữ liệu:** List, Stack (Ngăn xếp), Queue (Hàng đợi), Tree (Cây), Heap, Graph [Đồ thị](cite: 443, 444, 445, 446, 447).
* **Giải thuật (Algorithms):** Một chuỗi hữu hạn các lệnh, mỗi lệnh có ngữ nghĩa rõ ràng và có thể được thực hiện với một lượng hữu hạn tài nguyên trong một khoảng hữu hạn thời gian[cite: 448].
  * **Đặc điểm của giải thuật:** Tính chính xác, tính hữu hạn, tính đơn trị, tính tổng quát[cite: 449].
  * **Cách biểu diễn giải thuật:** Ngôn ngữ tự nhiên, lưu đồ (flowchart), mã giả (pseudo code), ngôn ngữ lập trình[cite: 450, 451, 453].
* **Độ phức tạp của thuật toán:** Đánh giá hiệu quả của thuật toán dựa trên thời gian thực thi và tài nguyên sử dụng[cite: 456].
  * **Ước lượng thời gian thực hiện chương trình:** Sử dụng ký hiệu O(n) để biểu thị cấp độ tăng của hàm thời gian T(n) theo kích thước dữ liệu đầu vào n[cite: 458, 459].
  * **Các quy tắc tính toán thời gian thực hiện:** Quy tắc cộng và nhân cấp độ tăng[cite: 461].
  * **Các độ phức tạp cơ bản:** O(1), O(log2 n), O(n), O(n log2 n), O(n^b), O(b^n), O[n!](cite: 462).

**Ví dụ về kiểu dữ liệu có cấu trúc:**

* **Thông tin sinh viên:** [cite: 438, 439, 440, 441]
  * Nếu tổ chức dưới dạng mảng 1 chiều:
    * Họ tên: Nguyễn Hoa Hậu, Mã SV: D11K7, Năm sinh: 2002, Lớp: D20
    * Họ tên: Đỗ Lực Sĩ, Mã SV: D11K8, Năm sinh: 2000, Lớp: D20
    * Họ tên: Lý Minh Tinh, Mã SV: D11K9, Năm sinh: 2003, Lớp: D21
    * Họ tên: Trần Đại Gia, Mã SV: D11K10, Năm sinh: 2003, Lớp: D21
  * Nếu tổ chức dưới dạng đối tượng `SinhVien`:

        Sinh vien {
           Ho_ten : String
           Ma_SV: String
           Nam_sinh: int
           Lop: String
        }

**Ví dụ tính thời gian thực hiện của thuật toán (Bubble Sort):** [cite: 464]

    void buble (int a[n]){
        int i, j, temp;
    1.  for (i = 0; i < n-1; i++)
    2.      for (j = n-1; j>= i+1; j--)
    3.          if (a[j-1] > a[j]){
                    // Đổi chỗ cho a[j] và a[j-1]
    4.              temp = a[j-1];
    5.              a[j-1] = a[j];
    6.              a[j] = temp;
                }
    }

* Các lệnh ở dòng 4, 5, 6 có thời gian thực hiện O(1). Tổng thời gian 3 lệnh = O(max(1,1,1)) = O[1](cite: 464).
* Số vòng lặp ở dòng 2 là n-i, thời gian kiểm tra điều kiện và tăng biến là O(1). Tổng thời gian 2 lệnh lồng nhau = O((n-i)x1) = O[n-i](cite: 464).
* Các lệnh dòng 1 lặp n-1 lần, tức là O[n-1](cite: 464).
* Tổng thời gian chạy = O((n-1).(n-i)) = O(n^2) hoặc cụ thể hơn là n.(n-1)/2[cite: 464].

### Chương 2: Mảng và Danh sách liên kết

Chương này đi sâu vào hai cấu trúc dữ liệu cơ bản là mảng và danh sách liên kết.

* **Mảng (Array):** Cấu trúc dữ liệu căn bản, lưu trữ các phần tử cùng kiểu dữ liệu trong các ô nhớ liên tiếp[cite: 337, 374].
  * **Ưu điểm:** Dễ sử dụng, tốc độ truy cập cao [truy cập ngẫu nhiên](cite: 419).
  * **Nhược điểm:** Không linh hoạt về kích thước (kích thước cố định khi khai báo), phức tạp khi bố trí lại các phần tử [chèn, xóa](cite: 419, 420).
  * **Mảng 1 chiều:** `int M[8]`[cite: 337]. Thời gian duyệt: O[n](cite: 337).
  * **Mảng 2 chiều (matrix):** `int A[3][4]`[cite: 374]. Thời gian duyệt: O[n.m](cite: 374).
* **Danh sách liên kết (Linked List):** Cấu trúc dữ liệu có kiểu truy cập tuần tự, mỗi phần tử (node) chứa dữ liệu và một con trỏ (liên kết) đến phần tử tiếp theo[cite: 425].
  * **Đặc điểm:** Các node không nhất thiết lưu trữ liên tiếp trong bộ nhớ, có thể mở rộng tùy ý, thao tác chèn/xóa không cần dịch chuyển phần tử[cite: 426].
  * **Các loại danh sách liên kết:** [cite: 427]
    * Danh sách liên kết đơn (Singly Linked List)
    * Danh sách liên kết kép (Doubly Linked List)
    * Danh sách liên kết vòng (Circular Linked List)
  * **Các thao tác cơ bản:** Tạo danh sách, thêm phần tử, duyệt phần tử, truy xuất phần tử, xóa phần tử, xóa danh sách[cite: 431].

**So sánh Danh sách liên kết và Mảng:** [cite: 342]

| Đặc điểm             | Mảng                                     | Danh sách liên kết                               |
| :------------------- | :--------------------------------------- | :----------------------------------------------- |
| Số phần tử          | Xác định trước                           | Không cần xác định trước                         |
| Cấp phát bộ nhớ     | Liên tục, đủ lớn                         | Riêng lẻ cho từng phần tử                       |
| Truy xuất            | Ngẫu nhiên, nhanh, đơn giản              | Tuần tự, DSLK đơn chỉ duyệt 1 chiều              |
| Bộ nhớ cho con trỏ   | Không cần                               | Cần bộ nhớ lưu trữ con trỏ tham chiếu          |
| Thêm/xóa ở cuối      | O(1)                                     | O(1)                                             |
| Thêm/xóa ở giữa      | O(n) (do phải dịch chuyển)              | O(1) (nếu đã có con trỏ đến vị trí cần thiết) |

**Ví dụ về Danh sách liên kết đơn:**

* **Khai báo:**

    struct node {
        int info;
        struct node \*next;
    };
    typedef struct node \*PTR;
    PTR First; // Con trỏ đến phần tử đầu tiên

* **Thêm phần tử vào đầu danh sách:** [cite: 302]

    void Insert_First(PTR &First, int x) {
        PTR p;
        p = new node;
        p->info = x;
        p->next = First;
        First = p;
    }

* **Thêm phần tử vào sau node `p`:** [cite: 303]

    void Insert_after(PTR p, int x) {
        PTR q;
        if (p == NULL)
            printf("khong them phan tu vao danh sach duoc");
        else {
            q = new node;
            q->info = x;
            q->next = p->next;
            p->next = q;
        }
    }

* **Duyệt danh sách:** [cite: 306, 307]

    void Traverse(PTR First) {
        PTR p;
        int stt = 0;
        for (p = First; p != NULL; p = p->next)
            printf("\n %5d%8d", stt++, p->info);
    }

* **Tìm kiếm phần tử có nội dung `x`:** [cite: 308]

    PTR Search_info(PTR First, int x) {
        PTR p;
        for (p = First; p != NULL; p = p->next)
            if (p->info == x) return p;
        return NULL;
    }

* **Xóa phần tử ở đầu danh sách:** [cite: 311, 312, 313]

    int Delete_First(PTR &First) {
        PTR p;
        if (Empty(First)) // Hàm Empty kiểm tra First == NULL [cite: 310]
            return 0;
        p = First;
        First = p->next;
        delete p; // Hủy node p [cite: 313]
        return 1;
    }

* **Xóa phần tử đứng sau node `p`:** [cite: 316, 317, 318]

    int Delete_after(PTR p) {
        PTR q;
        if ((p == NULL) || (p->next == NULL))
            return 0;
        q = p->next; // q là node cần xóa
        p->next = q->next;
        delete q; // Hủy node q [cite: 318]
        return 1;
    }

* **Xóa phần tử có nội dung `info`:** [cite: 321, 322, 323]

    int Delete_info(PTR &First, String x) { // Giả sử String là kiểu dữ liệu của info
        PTR p = First;
        if (First == NULL) return 0;
        if (First->info == x) {
            Delete_First(First); return 1;
        }
        for (p = First; p->next != NULL && p->next->info != x; p = p->next);
        if (p->next != NULL) {
            Delete_after(p); return 1; // Sửa lỗi logic: Phải là Delete_after(p)
        }
        return 0;
    }

* **Xóa phần tử cuối danh sách:** [cite: 326, 327, 328]

    int Delete_pTail(PTR &First) {
        PTR q = First;
        PTR p = NULL; // p sẽ trỏ đến node trước q
        if (First == NULL) return 0;
        if (First->next == NULL) { // Trường hợp chỉ có 1 phần tử
            delete First;
            First = NULL;
            return 1;
        }
        while (q->next != NULL) {
            p = q;
            q = q->next;
        }
        // Lúc này q là node cuối, p là node ngay trước q
        p->next = NULL;
        delete q;
        return 1;
    }

* **Xóa toàn bộ danh sách:** [cite: 330]

    void Clearlist(PTR &First) {
        while (First != NULL)
            Delete_First(First);
    }

    *Lưu ý:* Không sử dụng `First = NULL` để xóa danh sách vì sẽ gây lãng phí vùng nhớ[cite: 331].
* **Sắp xếp danh sách liên kết đơn (Selection Sort - hoán vị dữ liệu):** [cite: 332, 333, 334, 335, 336]

    void Selection_Sort(PTR &First) {
        PTR p, q, pmin;
        int min_val; // Sửa tên biến để tránh nhầm lẫn với con trỏ
        for (p = First; p != NULL && p->next != NULL; p = p->next) { // Điều kiện dừng của p
            min_val = p->info;
            pmin = p;
            for (q = p->next; q != NULL; q = q->next) {
                if (q->info < min_val) {
                    min_val = q->info;
                    pmin = q;
                }
            }
            // Hoán đổi trường info của hai nút p và pmin
            if (pmin != p) { // Chỉ hoán đổi nếu tìm thấy phần tử nhỏ hơn
                 pmin->info = p->info;
                 p->info = min_val;
            }
        }
    }

**Ví dụ về Danh sách liên kết vòng:**

* Phần tử cuối liên kết về phần tử đầu tiên, dùng con trỏ `Last` để quản lý[cite: 343].
* **Khai báo:** [cite: 343]

    struct node {
        int info;
        struct node \*next;
    };
    typedef struct node \*PTR;
    PTR Last; // Con trỏ đến phần tử cuối cùng

* **Thêm vào đầu danh sách:** [cite: 346, 347]

    void Ins_first(PTR &Last, int x) {
        PTR p;
        p = new node; // Giả sử New_node() tương đương new node
        p->info = x;
        if (Last == NULL) { // Empty(Last) [cite: 360]
            Last = p;
            p->next = p; // Nút mới trỏ tới chính nó
        } else {
            p->next = Last->next;
            Last->next = p;
        }
    }

* **Thêm vào cuối danh sách:** [cite: 348, 349]

    void Ins_last(PTR &Last, int x) {
        PTR p;
        p = new node;
        p->info = x;
        if (Last == NULL) {
            p->next = p;
            Last = p;
        } else {
            p->next = Last->next;
            Last->next = p;
            Last = p; // Cập nhật Last là node mới
        }
    }

**Ví dụ về Danh sách liên kết kép:**

* Mỗi phần tử có 2 liên kết: đến phần tử trước (`left`) và sau nó (`right`)[cite: 384].
* **Khai báo:** [cite: 385]

    struct node {
        int info;
        struct node \*left, \*right;
    };
    typedef struct node \*PTR;
    PTR First, Last; // Con trỏ đến phần tử đầu và cuối

* **Thêm vào đầu danh sách:** [cite: 388, 389, 390, 391]

    void Insert_First(PTR &First, PTR &Last, int D) {
        PTR p;
        p = new node;
        p->info = D;
        p->left = NULL;
        p->right = First;
        if (First == NULL) // Danh sách rỗng
            Last = p;
        else
            First->left = p;
        First = p;
    }

* **Thêm vào bên phải (sau) node `p`:** [cite: 392, 394, 395, 396, 397]

    void Insert_right(PTR p, PTR &Last, int x) {
        PTR q, r;
        if (p == NULL)
            printf("Nut p khong hien huu, khong them nut duoc\n");
        else {
            q = new node;
            q->info = x;
            r = p->right; // r là node sau p (có thể NULL)

            q->right = r;
            if (r != NULL) // Nếu r tồn tại
                r->left = q;
            else // Nếu p là node cuối
                Last = q;

            q->left = p;
            p->right = q;
        }
    }

### Chương 3: Ngăn xếp và Hàng đợi

Chương này trình bày về hai cấu trúc dữ liệu trừu tượng quan trọng là Ngăn xếp (Stack) và Hàng đợi (Queue).

* **Ngăn xếp (Stack):** Danh sách các đối tượng làm việc theo cơ chế LIFO [Last-In, First-Out - Vào sau, ra trước](cite: 285, 268).
  * **Đặc điểm:** Thêm (Push) và loại bỏ (Pop) phần tử diễn ra ở cùng một đầu (đỉnh - top) của danh sách[cite: 286]. Con trỏ `SP` (Stack Pointer) trỏ tới phần tử cuối (đỉnh) stack[cite: 286].
  * **Ứng dụng:** [cite: 287]
    * Redo/Undo.
    * Đảo ngược xâu ký tự.
    * Tính giá trị biểu thức hậu tố.
    * Chuyển biểu thức trung tố sang hậu tố.
    * Gỡ đệ quy.
  * **Các thao tác cơ bản:** Khởi tạo, kiểm tra rỗng/đầy, Push, Pop, lấy thông tin phần tử đầu[cite: 288].
  * **Lưu trữ:** Bằng mảng hoặc danh sách liên kết[cite: 288].

* **Hàng đợi (Queue):** Danh sách các đối tượng làm việc theo cơ chế FIFO [First-In, First-Out - Vào trước, ra trước](cite: 253, 268).
  * **Đặc điểm:** Thêm phần tử (Enqueue) ở một đầu (cuối - rear) và loại bỏ phần tử (Dequeue) ở đầu còn lại [đầu - front](cite: 253).
  * **Ứng dụng:** [cite: 254, 255]
    * Xếp hàng mua vé, khám bệnh.
    * Quản lý các công việc đang đợi phục vụ trong hệ điều hành.
    * Quản lý hàng đợi in.
  * **Các thao tác cơ bản:** Khởi tạo, kiểm tra rỗng/đầy, Enqueue (Put/Insert), Dequeue (Get/Pop), lấy thông tin phần tử đầu[cite: 256].
  * **Lưu trữ:** Bằng mảng hoặc danh sách liên kết[cite: 256].

**Ví dụ về Ngăn xếp lưu trữ bằng Mảng:**

* **Khai báo:** [cite: 289, 290]

    #define STACKSIZE 6
    struct stack {
        int sp = -1; // Stack rỗng
        int nodes[STACKSIZE];
    };
    stack st;

* **Push (thêm phần tử `x`):** [cite: 291, 292]

    int push(stack &st, int x) {
        if (st.sp == STACKSIZE - 1) return 0; // Stack đầy
        st.nodes[++(st.sp)] = x;
        return 1;
    }

* **Pop (lấy phần tử, lưu vào `x`):** [cite: 294, 295]

    int pop(stack &st, int &x) {
        if (st.sp == -1) return 0; // Stack rỗng
        x = st.nodes[(st.sp)--];
        return 1; // Nên trả về giá trị của x hoặc bool thành công
    }

**Ví dụ về Ngăn xếp lưu trữ bằng Danh sách liên kết đơn:**

* **Khai báo:** [cite: 297]

    struct node {
        int item;
        struct node \*next;
    };
    typedef struct node \*stacknode;
    typedef struct {
        stacknode sp; // Trỏ tới đỉnh stack
    } stack_dslk; // Đổi tên để tránh trùng

* **Khởi tạo:** [cite: 246]

    void stackInitialize(stack_dslk *s) {
        s->sp = NULL; // Stack rỗng
    }

* **Push (thêm `x`):** [cite: 249, 250, 251]

    void Push(stack_dslk *s, int x) {
        stacknode p;
        p = (stacknode)malloc(sizeof(struct node));
        p->item = x;
        p->next = s->sp;
        s->sp = p;
    }

* **Pop (lấy phần tử):** [cite: 252]

    int Pop(stack_dslk *s, int &item_val) { // Trả về giá trị qua tham chiếu
        stacknode p;
        if (s->sp == NULL) { // stackEmpty(*s) [cite: 248]
            printf("stack rỗng ! ");
            return 0; // Thất bại
        } else {
            p = s->sp;
            item_val = p->item; // Lấy giá trị
            s->sp = s->sp->next;
            free(p);
            return 1; // Thành công
        }
    }

**Ví dụ về Hàng đợi lưu trữ bằng Mảng (tuyến tính hoặc vòng):**

* **Khai báo (tuyến tính đơn giản):** [cite: 257]

    #define QUEUESIZE 100
    struct queue_arr { // Đổi tên
        int front = -1, rear = -1; // Khởi tạo hàng đợi rỗng
        int nodes[QUEUESIZE];
    };
    queue_arr q_arr;

* **Insert/Enqueue (thêm `x` - xử lý mảng vòng):** [cite: 265, 266, 267]

    int Insert_queue(queue_arr &q, int x) {
        if ((q.front == 0 && q.rear == QUEUESIZE - 1) || (q.rear == (q.front - 1) % (QUEUESIZE -1) )) { // Hàng đợi đầy
            return 0;
        } else if (q.front == -1) { // Hàng đợi rỗng
            q.front = q.rear = 0;
            q.nodes[q.rear] = x;
        } else if (q.rear == QUEUESIZE - 1 && q.front != 0) { // Cuối mảng còn chỗ ở đầu
            q.rear = 0;
            q.nodes[q.rear] = x;
        } else {
            q.rear++;
            q.nodes[q.rear] = x;
        }
        return 1;
    }

* **Delete/Dequeue (lấy phần tử, lưu vào `x` - xử lý mảng vòng):** [cite: 270, 271, 272, 273, 274]

    int Delete_queue(queue_arr &q, int &x) {
        if (q.front == -1) { // Hàng đợi rỗng
            return 0;
        }
        x = q.nodes[q.front];
        if (q.front == q.rear) { // Chỉ có 1 phần tử
            q.front = q.rear = -1;
        } else if (q.front == QUEUESIZE - 1) { // front ở cuối mảng
            q.front = 0;
        } else {
            q.front++;
        }
        return 1;
    }

**Ví dụ về Hàng đợi lưu trữ bằng Danh sách liên kết đơn:**

* **Khai báo:** [cite: 276]

    struct node_q { // Đổi tên node
        int item;
        struct node_q \*next;
    };
    typedef struct node_q \*queuenode;
    typedef struct {
        queuenode front;
        queuenode rear;
    } queue_dslk; // Đổi tên

* **Khởi tạo:** [cite: 278]

    void queueInitialize(queue_dslk *q) {
        q->front = q->rear = NULL;
    }

* **Put/Enqueue (thêm `x`):** [cite: 280, 281, 282]

    void Put(queue_dslk *q, int x) {
        queuenode p;
        p = (queuenode)malloc(sizeof(struct node_q));
        p->item = x;
        p->next = NULL;
        if (q->rear == NULL) { // Hàng đợi rỗng
            q->front = q->rear = p;
        } else {
            q->rear->next = p;
            q->rear = p;
        }
    }

* **Pop/Dequeue (lấy phần tử, trả về giá trị):** [cite: 283, 284]

    int Pop_queue(queue_dslk *q, int &item_val) { // Trả về giá trị qua tham chiếu
        queuenode p;
        if (q->front == NULL) { // queueEmpty(*q) [cite: 279]
            printf("Queue rỗng !");
            return 0; // Thất bại
        } else {
            p = q->front;
            item_val = p->item;
            q->front = q->front->next;
            if (q->front == NULL) { // Nếu sau khi xóa, hàng đợi trở rỗng
                q->rear = NULL;
            }
            free(p);
            return 1; // Thành công
        }
    }
