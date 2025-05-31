# GitHub Copilot Instructions for PTIT DSA Project: Student Management System (C++)

## 0. Development Environment and Constraints

- **IDE:** Visual Studio Code (VS Code)
- **Operating System:** macOS
- **User Interface:** Console-based application only. **No GUI libraries are to be used.**
- **Core Philosophy:** Prioritize fundamental C++ and a procedural programming style. **Minimize reliance on external libraries and advanced C++ features (like extensive OOP or STL containers/algorithms).** All data structures and algorithms should be implemented manually, closely following the examples, style, and concepts presented in the `dsa-ptit-theory.md` file.
- **Theoretical Foundation:** The primary reference is `.github/copilot-knowledge/dsa-ptit-theory.md`. Code should align with its C-style/procedural C++ examples.

## 1. Project Overview and Goals

This project is for the Data Structures and Algorithms course at PTIT.
The main objective is to build a C++ program using a procedural approach to manage student data. This involves manual implementation of data structures and algorithms based on `.github/copilot-knowledge/dsa-ptit-theory.md`. The program will run in a console environment.
Key requirements are in `.github/copilot-knowledge/das-ptit-project-requirements.md`.
The project must be implemented in C++, focusing on core algorithmic logic.
**Crucial Requirement:** Implement error checking for all user inputs.

## 2. Core Data Structures and Algorithms

**Implementations must strictly follow the procedural style (using structs and functions), pointer manipulations, and manual memory management (e.g., `new`/`delete` or `malloc`/`free` if shown) as demonstrated in `.github/copilot-knowledge/dsa-ptit-theory.md`. Avoid STL containers like `std::vector` or `std::list` for core data storage; implement these structures from scratch.**

### Part A: Mandatory Student Management (7 points)

**2.1. Data Storage Options (User Choice):**
Manually implement using approaches from `dsa-ptit-theory.md` for:

- Array (e.g., `int M[8];`)
- Singly Linked List (e.g., `struct node { int info; struct node *next; }; typedef struct node *PTR;`)
- Circular Linked List
- Doubly Linked List

**Copilot Guidance:**

- "Generate C++ code for these data structures using `struct` for nodes and global/static functions for operations, as seen in `dsa-ptit-theory.md`. For example, linked list node definitions and operations (add, delete, traverse) should be implemented manually using pointers."
- "Do not suggest using `std::list`, `std::vector`, etc., for the primary student list storage."

**2.2. Student Information:**
Define as a simple `struct`. Operations on student data should be done by functions taking this struct (or pointers/references to it) as arguments.

```cpp
// Ví dụ cấu trúc SinhVien (Student struct example)
// Sử dụng struct đơn giản, không dùng class với methods.
struct Student {
    char studentID[20]; // Hoặc std::string nếu là lựa chọn tối thiểu được chấp nhận
    char firstName[50];
    char lastName[50];
    char studentClass[20];
    float score;
};
// Các hàm thao tác với Student sẽ nhận Student* hoặc Student&
// Ví dụ: void hienThiSinhVien(const Student* sv);
```

**Copilot Guidance:**

- "Define `Student` as a plain `struct`. Prefer C-style strings (`char[]`) if `dsa-ptit-theory.md` leans heavily C-style, or basic `std::string` if it's used minimally and consistently in theory examples for string types. Avoid complex string operations if using `char[]` without guidance from theory."
- "All operations related to `Student` data should be implemented as standalone functions."

**2.3. Core Functionalities (Implement algorithms manually based on `dsa-ptit-theory.md`):**

1. **Input from File (1 point):**
    - Read from CSV. Focus on fundamental file I/O (e.g., using `<fstream>` with `getline` or C-style `<cstdio>` with `fscanf` if theory shows this).
2. **Add New Student (1 point):**
    - Manually input via console.
3. **Delete or Update Student (1 point):**
    - Based on Student ID.
4. **Student Statistics (1 point):**
    - List lowest/highest score(s), calculate average.
5. **Sorting (1 point):**
    - **Algorithms:** Manually implement Bubble Sort, Insertion Sort, Quick Sort, Selection Sort, Heap Sort, Merge Sort, following examples/logic in `dsa-ptit-theory.md`.
        - *Constraint:* Heap Sort/Quick Sort for Array or Doubly Linked List only.
    - **Copilot Guidance:** "Do not use `std::sort`. Provide C++ code for the chosen sorting algorithm implemented from scratch, operating on the manually implemented data structures."
6. **Searching (1 point):**
    - **Methods:** Manually implement Binary Search (if sorted) and Sequential Search.
    - **Copilot Guidance:** "Do not use `std::binary_search` or other STL search functions. Implement search algorithms manually."

### Part B: Optional Advanced Algorithm (Choose 1 - 2 points, procedural implementation)

#### **2.4. Option 1: Knight's Tour (2 points)**

- Use a 2D array and a procedural backtracking algorithm.

#### **2.5. Option 2: Binary Search Tree (BST) for Students by Score (2 points)**

- Node: `struct NodeBST { float key; /* manually implemented list/array of Student structs */ Student studentsWithScore[MAX_STUDENTS_PER_SCORE]; int count; struct NodeBST *left, *right; };`
- Functions for add, delete, traversals should be standalone, operating on `NodeBST*`.
- **Copilot Guidance:** "For BST `Info` (list of students with the same score), use a simple array within the BST node struct or a manually implemented linked list if dynamic sizing is essential and shown in theory. Avoid `std::vector` here."

## 3. C++ Language and Coding Conventions

- **Language Standard:** C++ (as minimally featured as possible, aligning with C++03 or C++11 if `new`/`delete` are from there, but with a C-like procedural style).
- **Style Guide:**
  - **Procedural Focus:** **Strictly prefer a procedural programming style.** Use `struct` for data aggregation and standalone functions for operations. **Avoid OOP concepts: do not use `class` keyword, methods within structs (unless `dsa-ptit-theory.md` explicitly does so for a specific data structure in a very simple way), inheritance, or polymorphism.**
  - **Namespace:** **Start main C++ source files with `using namespace std;`** after include directives. This is for convenience in this project.

      ```cpp
      #include <iostream>
      // other includes
      using namespace std;

      // rest of the code
      ```

  - **Naming:** Follow conventions in `dsa-ptit-theory.md`. If it uses Vietnamese terms in code examples (e.g., `struct nut`), replicate that. Otherwise, meaningful English names for structs, functions, variables.
  - **Comments:** **All comments MUST be in clear, understandable Vietnamese.**

      ```cpp
      // Ví dụ comment bằng tiếng Việt
      // Hàm này dùng để khởi tạo một danh sách liên kết đơn rỗng
      void khoiTaoDanhSach(PTR& First) {
          First = NULL; // Gán con trỏ đầu bằng NULL
      }
      ```

  - **Error Checking:** Mandatory for console inputs.
- **Headers:**
  - **Prioritize C-style headers if `dsa-ptit-theory.md` uses them (e.g., `<cstdio>`, `<cstring>`, `<cstdlib>`).**
  - Use C++ headers like `<iostream>` for console I/O. `<fstream>` for file I/O.
  - Basic `<string>` if `std::string` is chosen for student info fields.
  - **Avoid including STL container headers (`<vector>`, `<list>`, `<map>`, etc.) or `<algorithm>` unless for a very specific, unavoidable, and simple utility not related to core data structures/algorithms that are meant to be manually implemented.**
- **Memory Management:** Manual `new`/`delete` (C++) or `malloc`/`free` (C-style), strictly following examples in `dsa-ptit-theory.md`. **No smart pointers.**

## 4. Key Libraries and Frameworks

- **Allowed:** Minimal use of Standard C++ libraries, focusing on those providing basic I/O and fundamental types.
  - Essential: `<iostream>` (for `cin`, `cout`), `<fstream>` (for file operations).
  - Potentially: `<string>` (for `std::string` if used for student fields, basic usage only), `<cstring>` (for C-string functions), `<cstdlib>` (for `malloc`/`free` if C-style).
- **Strongly Discouraged/Disallowed for Core Logic:** STL containers (`std::vector`, `std::list`, `std::map`, `std::stack`, `std::queue`), STL algorithms (`std::sort`, `std::find`, etc.). These must be manually implemented. No GUI libraries.

## 5. Guidance from Reference Codebases (and `dsa-ptit-theory.md`)

- **Absolute Primary Source:** `.github/copilot-knowledge/dsa-ptit-theory.md`. Code MUST mirror its procedural style, data representation, and algorithmic logic.
- Other student projects: Secondary reference, mainly for console menu structure if not detailed in the theory file. Ensure their approach doesn't violate the "minimal libraries/procedural" principle.

## 6. Specific Task Focus

(User to update this section)
Example: "Currently, I am implementing the `Insert_First` function for a singly linked list using `struct node*` as shown in `dsa-ptit-theory.md` (Chapter 2). The code should be procedural, include `using namespace std;` at the top, use manual pointer assignment, and all comments must be in Vietnamese. Avoid suggesting `std::list` or OOP classes."

- "Generate C++ code reflecting the procedural, manual implementations from `.github/copilot-knowledge/dsa-ptit-theory.md`."
- "Ensure all C++ files start with necessary includes followed by `using namespace std;`."
- "Ensure no OOP `class` suggestions, prefer `struct` and functions."
- "Minimize STL usage to bare essentials for I/O."

## 7. Input/Output Format and Error Handling (Console Focus)

- All I/O via console. Error messages preferably in Vietnamese.

## 8. General Guidance

- **Adherence to Theory & Procedural Style:** "Implement data structures and algorithms strictly as procedural C/C++ code, based on examples in `.github/copilot-knowledge/dsa-ptit-theory.md`. Avoid OOP and STL for core logic."
- **Vietnamese Comments:** "All C++ code comments must be in Vietnamese."
- **Namespace `std`:** "Always include `using namespace std;` at the beginning of C++ source files after includes."
- **Simplicity:** "Favor the simplest possible C++ constructs that achieve the task, as would be typical in an introductory DSA course focusing on fundamentals rather than advanced language features."
- **Library Minimization:** "Actively avoid suggesting C++ STL containers or algorithms for tasks where the learning objective is to implement them manually. Only suggest essential libraries for I/O or basic types if absolutely necessary and not conflicting with manual implementation goals."
