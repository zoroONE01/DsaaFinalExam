# GitHub Copilot Instructions for PTIT DSA Project: Student Management System (C++)

## 0. Development Environment and Constraints

- **IDE:** Visual Studio Code (VS Code)
- **Operating System:** macOS
- **User Interface:** Console-based application only. **No GUI libraries (e.g., Qt, wxWidgets, GTK+) are to be used.** All interactions must be handled through standard input/output.
- **Theoretical Foundation:** The primary reference for data structure and algorithm implementations is the provided `dsa-ptit-theory.md` file located in `.github/knowledge/dsa-ptit-theory.md`. Code generated should align closely with the examples and style presented in this theory file.

## 1. Project Overview and Goals

This project is for the Data Structures and Algorithms course at PTIT.
The main objective is to build a C++ program to manage a list of students with functionalities for inputting, storing, modifying, sorting, searching, and analyzing student data, following the examples in `dsa-ptit-theory.md`. The program will run in a console environment. The project also includes an optional advanced algorithm implementation.
Key requirements are in `.github/knowledge/das-ptit-project-requirements.md`.
The project must be implemented in C++.
**Crucial Requirement:** Implement error checking for all user inputs.

## 2. Core Data Structures and Algorithms

Implementations should closely follow the examples and explanations in `.github/knowledge/dsa-ptit-theory.md`.

### Part A: Mandatory Student Management (7 points)

**2.1. Data Storage Options (User Choice):**
Implement using approaches from `dsa-ptit-theory.md` for:

- Array
- Singly Linked List
- Circular Linked List
- Doubly Linked List

**Copilot Guidance:**

- "When implementing data storage, provide distinct C++ implementations for these four structures, referencing the style and logic shown in `dsa-ptit-theory.md` (e.g., struct definitions, pointer manipulations for linked lists)."
- "Ensure all subsequent operations can work correctly with the chosen data structure, adhering to the theory file's examples."

**2.2. Student Information:**

- Student ID (string: numbers + chars, no spaces, unique)
- First Name (string)
- Last Name (string)
- Class (string, no spaces)
- Score (float)

**Copilot Guidance:**

- "When reading student data, validate input as per requirements. Base the `Student` struct/class on similar structures if any are defined in `dsa-ptit-theory.md` or use a standard approach."

  ```cpp
  // Ví dụ cấu trúc SinhVien (Student struct example)
  // Bám sát theo cách khai báo struct/class trong dsa-ptit-theory.md nếu có
  struct Student {
      std::string studentID;
      std::string firstName;
      std::string lastName;
      std::string studentClass;
      float score;
  };
  ```

**2.3. Core Functionalities (Implementations based on `dsa-ptit-theory.md` examples):**

1. **Input from File (1 point):**
    - Read from CSV (DSSV.csv).
    - **Copilot Guidance:** "Prioritize CSV parsing. Refer to `dsa-ptit-theory.md` for any file handling examples."
2. **Add New Student (1 point):**
    - Manually input via console.
3. **Delete or Update Student (1 point):**
    - Based on Student ID.
4. **Student Statistics (1 point):**
    - List lowest/highest score(s), calculate average.
5. **Sorting (1 point):**
    - **Algorithms:** Bubble Sort, Insertion Sort, Quick Sort, Selection Sort, Heap Sort, Merge Sort. (Refer to `dsa-ptit-theory.md` for these algorithms, e.g., the Bubble Sort example provided).
        - *Constraint:* Heap Sort/Quick Sort for Array or Doubly Linked List only.
    - **Criteria:** Student ID, Name, Score.
    - **Output:** Sorted list and execution time.
    - **Copilot Guidance:** "Implement sorting algorithms as shown in `dsa-ptit-theory.md`. For instance, the theory file includes an example of Bubble Sort; try to follow that style for other algorithms too. Ensure time measurement."
6. **Searching (1 point):**
    - **Criteria:** Student ID, First Name, Last Name, Class, Score (case-insensitive).
    - **Methods:** Binary Search (if sorted), Sequential Search. (Refer to `dsa-ptit-theory.md` for search algorithm examples if available).
    - **Output:** Highlighted results, time, optional reversed name.

### Part B: Optional Advanced Algorithm (Choose 1 - 2 points, based on `dsa-ptit-theory.md` if applicable)

#### **2.4. Option 1: Knight's Tour (2 points)**

- Input: Board size `n x n`, start (u,v).
- Storage: 2D array.
- Task: List all moves.
- Output: `k : (u,v)`.
- **Copilot Guidance:** "Suggest a backtracking algorithm. If `dsa-ptit-theory.md` covers graph traversal or backtracking, align with its principles."

#### **2.5. Option 2: Binary Search Tree (BST) for Students by Score (2 points)**

- Node: `key` (score), `Info` (list of `Student` objects).
- Functions: Add, Delete (by key), Traversals (PreOrder, InOrder, PostOrder).
- **Copilot Guidance:** "Define BST node and operations based on tree examples in `dsa-ptit-theory.md`. Pay attention to how nodes, pointers, and recursive/iterative traversals are handled in the theory file."

## 3. C++ Language and Coding Conventions

- **Language Standard:** C++11 or newer.
- **Style Guide:**
  - **Primary Goal:** Follow coding style and conventions (variable naming, function structure, struct/class definitions) demonstrated in the C++ examples within `dsa-ptit-theory.md`.
  - Use meaningful English names for variables, functions, classes, and structs, unless the theory file consistently uses Vietnamese terms in examples (then clarify).
  - **Comments:** **All comments in the code MUST be written in clear, understandable Vietnamese.** Explain complex logic or the purpose of code blocks.

      ```cpp
      // Ví dụ comment bằng tiếng Việt
      // Hàm này dùng để thêm một sinh viên mới vào đầu danh sách
      void themSinhVienDauDanhSach(Node*& head, Student sv) {
          // Tạo một node mới
          Node* newNode = new Node();
          newNode->data = sv; // Gán dữ liệu cho node
          newNode->next = head; // Con trỏ next của node mới trỏ tới head cũ
          head = newNode;     // Cập nhật head là node mới
      }
      ```

  - **Mandatory:** Thorough error checking for console inputs.
  - Proper indentation.
- **Headers:** Standard C++: `<iostream>`, `<vector>`, `<string>`, etc.
- **Memory Management:** Follow examples in `dsa-ptit-theory.md` for `new`/`delete` or smart pointers if shown.
- **Input/Output:** Console-based (`std::cin`, `std::cout`).

## 4. Key Libraries and Frameworks

- **Allowed:** Standard C++ libraries.
- **Disallowed:** No third-party libraries (except for CSV/Excel if permitted), no GUI libraries.
- **Guidance:** If `dsa-ptit-theory.md` uses specific standard libraries for its examples (e.g., `<list>` for `std::list` vs. custom linked list), prioritize those when relevant.

## 5. Guidance from Reference Codebases (and `dsa-ptit-theory.md`)

- **Primary Source of Truth for Implementation Style:** `.github/knowledge/dsa-ptit-theory.md`. Code should mirror the style, structure, and logic of examples in this file.
- Other student projects (e.g., `phong-kaster-ptit-cau-truc-du-lieu-va-giai-thuat-quan-ly-may-bay.txt`) can be secondary references for overall program structure or menu handling if `dsa-ptit-theory.md` doesn't cover these aspects.

## 6. Specific Task Focus

(User to update this section based on current work)
Example: "Currently, I am implementing the Singly Linked List operations (Insert_First, Delete_after, Traverse) as described in Chapter 2 of `dsa-ptit-theory.md`. I need help ensuring my C++ code for `Delete_after` correctly matches the logic and pointer manipulation shown in the theory file's example, and that all comments are in Vietnamese."

- "Generate C++ code that directly reflects the algorithms and data structure representations from `dsa-ptit-theory.md`."
- "Ensure all generated comments are in Vietnamese."

## 7. Input/Output Format and Error Handling (Console Focus)

- Consistent with previous instructions, ensure all I/O is console-based.
- Error messages should be clear and preferably in Vietnamese if the application's user interface is intended to be Vietnamese. (This can be a secondary point, primary is Vietnamese comments in code).

## 8. General Guidance

- **Adherence to Theory:** "The absolute priority is to implement data structures and algorithms as closely as possible to the examples and explanations provided in `.github/knowledge/dsa-ptit-theory.md`."
- **Vietnamese Comments:** "All C++ code comments must be in Vietnamese, providing clear explanations."
- "Prioritize correctness and efficiency as per the theory file's guidelines."
- "Structure the console application with clear menus and prompts. If `dsa-ptit-theory.md` offers guidance on program structure, follow it."
