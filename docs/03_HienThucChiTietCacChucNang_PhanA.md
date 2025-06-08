# 3. Hiện thực Chi tiết các Chức năng (Phần A)

### 3.1. Nhập dữ liệu từ File CSV

**Mô tả:** Chức năng này chịu trách nhiệm đọc thông tin sinh viên từ một file CSV (ví dụ: `data/students.csv`) và nạp vào cấu trúc dữ liệu mà người dùng đã chọn khi khởi động chương trình.

**Thư viện sử dụng:** `<fstream>` cho các thao tác vào/ra file, `<cstring>` cho các hàm xử lý chuỗi C (như `strcpy`, `strtok`), `<iostream>` cho việc thông báo lỗi, `<regex>` cho validation pattern, `<string>` cho xử lý chuỗi.

**Cấu trúc dữ liệu Student:**

```cpp
// filepath: /Users/tuthanhnguyen/Workspace/CPP/DsaaFinalExam/include/core/student.h
struct Student
{
    char studentID[MAX_STUDENT_ID_LENGTH];    // Mã sinh viên
    char firstName[MAX_NAME_LENGTH];          // Họ và tên đệm
    char lastName[MAX_NAME_LENGTH];           // Tên
    char studentClass[MAX_CLASS_LENGTH];      // Lớp
    float score;                              // Điểm số
};
```

**Thuật toán:**

1. Yêu cầu người dùng nhập tên file CSV hoặc sử dụng tên file mặc định (`data/students.csv`).
2. Mở file CSV ở chế độ đọc. Kiểm tra xem file có mở thành công không. Nếu không, thông báo lỗi và thoát chức năng.
3. Đọc file theo từng dòng. Bỏ qua dòng tiêu đề (header) đầu tiên.
4. Với mỗi dòng dữ liệu:

   a. Sử dụng hàm `strtok()` để phân tách dòng thành các trường thông tin (Mã SV, Họ, Tên, Lớp, Điểm) dựa trên dấu phẩy (`,`).

   b. Sử dụng hàm `trim()` để loại bỏ khoảng trắng thừa ở đầu và cuối mỗi trường.

   c. Kiểm tra tính hợp lệ của từng trường dữ liệu bằng các hàm validation:
      - **Mã sinh viên:** Sử dụng regex pattern `^[a-zA-Z0-9]{3,19}$`, kiểm tra tính duy nhất trong danh sách hiện tại.
      - **Họ và Tên:** Không được để trống, độ dài không vượt quá giới hạn.
      - **Lớp:** Không được để trống, độ dài không vượt quá giới hạn.
      - **Điểm:** Phải là số thực hợp lệ trong khoảng từ 0.0 đến 10.0.

   d. Nếu tất cả các trường đều hợp lệ, tạo một `struct Student` mới và thêm vào danh sách.

   e. Nếu có lỗi validation, ghi nhận lỗi và hiển thị thông báo chi tiết.

5. Đóng file và hiển thị thống kê kết quả (số dòng hợp lệ/không hợp lệ).
6. Chuyển dữ liệu từ ArrayStudentList sang cấu trúc dữ liệu người dùng đã chọn (nếu khác Array).

**Trích dẫn Code:**

**1. Hàm đọc file CSV chính (`readFromCSVFile` trong `src/utils/common_utils.cpp`):**

```cpp
// src/utils/common_utils.cpp
bool readFromCSVFile(const char *filename, ArrayStudentList &list)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        return false; // Không thể mở file
    }

    // Khởi tạo danh sách rỗng
    initArrayList(list);

    string line;
    // Đọc dòng tiêu đề (nếu có)
    getline(file, line);

    int lineNumber = 1; // Bắt đầu từ dòng 1 (sau header)
    int validCount = 0;
    int invalidCount = 0;

    // Đọc từng dòng dữ liệu
    while (getline(file, line))
    {
        lineNumber++;

        if (line.empty())
        {
            continue; // Bỏ qua dòng trống
        }

        Student student;
        char buffer[200];
        strcpy(buffer, line.c_str());

        // Phân tích dữ liệu CSV bằng phân tách dấu phẩy
        char *token = strtok(buffer, ",");
        string studentID = token ? token : "";

        token = strtok(NULL, ",");
        string firstName = token ? token : "";

        token = strtok(NULL, ",");
        string lastName = token ? token : "";

        token = strtok(NULL, ",");
        string className = token ? token : "";

        token = strtok(NULL, ",");
        string scoreStr = token ? token : "";

        // Trim các chuỗi để loại bỏ khoảng trắng thừa
        studentID = trim(studentID);
        firstName = trim(firstName);
        lastName = trim(lastName);
        className = trim(className);
        scoreStr = trim(scoreStr);

        // Biến để kiểm tra tính hợp lệ của dòng hiện tại
        bool isLineValid = true;
        string errorMessages = "";

        // Kiểm tra mã sinh viên
        if (!validateStudentID(studentID))
        {
            isLineValid = false;
            errorMessages += "Mã sinh viên không hợp lệ. ";
        }
        else
        {
            // Kiểm tra trùng mã sinh viên trong danh sách hiện tại
            bool isDuplicate = false;
            for (int i = 0; i < list.count; i++)
            {
                if (strcmp(list.students[i].studentID, studentID.c_str()) == 0)
                {
                    isDuplicate = true;
                    break;
                }
            }
            if (isDuplicate)
            {
                isLineValid = false;
                errorMessages += "Mã sinh viên bị trùng lặp. ";
            }
        }

        // Kiểm tra họ và tên đệm
        if (!validateName(firstName))
        {
            isLineValid = false;
            errorMessages += "Họ và tên đệm không hợp lệ. ";
        }

        // Kiểm tra tên
        if (!validateName(lastName))
        {
            isLineValid = false;
            errorMessages += "Tên không hợp lệ. ";
        }

        // Kiểm tra tên lớp
        if (!validateClassName(className))
        {
            isLineValid = false;
            errorMessages += "Tên lớp không hợp lệ. ";
        }

        // Kiểm tra điểm số
        float score = 0.0f;
        try
        {
            if (!scoreStr.empty())
            {
                score = stof(scoreStr);
                if (!validateScore(score))
                {
                    isLineValid = false;
                    errorMessages += "Điểm số không hợp lệ (phải từ 0.0 đến 10.0). ";
                }
            }
            else
            {
                isLineValid = false;
                errorMessages += "Thiếu điểm số. ";
            }
        }
        catch (const exception &e)
        {
            isLineValid = false;
            errorMessages += "Điểm số không đúng định dạng. ";
        }

        // Nếu dòng hợp lệ, thêm vào danh sách
        if (isLineValid)
        {
            strcpy(student.studentID, studentID.c_str());
            strcpy(student.firstName, firstName.c_str());
            strcpy(student.lastName, lastName.c_str());
            strcpy(student.studentClass, className.c_str());
            student.score = score;

            addToArrayList(list, student);
            validCount++;
        }
        else
        {
            // In thông báo lỗi cho dòng không hợp lệ
            cout << YELLOW << "⚠ Dòng " << lineNumber << ": " << RESET
                 << RED << errorMessages << RESET << endl;
            cout << "   Nội dung: " << line << endl;
            invalidCount++;
        }
    }

    file.close();

    // Hiển thị thống kê
    cout << "\n" << BOLD << "KẾT QUẢ ĐỌC FILE CSV:" << RESET << endl;
    cout << GREEN << "✓ Số dòng hợp lệ: " << validCount << RESET << endl;
    if (invalidCount > 0)
    {
        cout << RED << "✗ Số dòng không hợp lệ (bị bỏ qua): " << invalidCount << RESET << endl;
    }

    return true;
}
```

**2. Hàm validation mã sinh viên (`validateStudentID` trong `src/utils/validation.cpp`):**

```cpp
// src/utils/validation.cpp
bool validateStudentID(const string &studentID)
{
    // Mã sinh viên gồm chữ và số, từ 3 đến (MAX_STUDENT_ID_LENGTH - 1) ký tự
    // (vì mảng cần 1 byte cho null terminator)
    string pattern = "^[a-zA-Z0-9]{3," + to_string(MAX_STUDENT_ID_LENGTH - 1) + "}$";
    regex regexPattern(pattern);
    return regex_match(studentID, regexPattern);
}
```

**3. Hàm điều phối nhập CSV (`handleInputFromCSV` trong `src/core/operations.cpp`):**

```cpp
// src/core/operations.cpp
bool handleInputFromCSV(const char *filePath,
                        int dataStructureType,
                        ArrayStudentList &arrayList,
                        NodeSLL *&singlyLinkedList,
                        NodeSLL *&circularLinkedList,
                        NodeDLL *&doublyLinkedListHead,
                        NodeDLL *&doublyLinkedListTail,
                        NodeBST *&binarySearchTree)
{
    cout << "Đang thử đọc từ file: " << filePath << endl;
    if (readFromCSVFile(filePath, arrayList))
    {
        printSuccess("Đã đọc dữ liệu từ file CSV thành công.");

        // Chuyển dữ liệu từ arrayList sang cấu trúc dữ liệu đã chọn
        if (dataStructureType != ARRAY_LIST)
        {
            for (int i = 0; i < arrayList.count; i++)
            {
                addStudentToDataStructure(arrayList.students[i], dataStructureType,
                                          arrayList, singlyLinkedList, circularLinkedList,
                                          doublyLinkedListHead, doublyLinkedListTail, binarySearchTree);
            }
        }
        return true;
    }
    else
    {
        string errorMsg = "Không thể đọc dữ liệu từ file CSV: " + string(filePath);
        printError(errorMsg.c_str());
        return false;
    }
}
```

**4. Cách sử dụng trong chương trình chính (`main.cpp`):**

```cpp
// src/main.cpp - Case 2: Nhập dữ liệu từ file CSV
case 2:
{
    clearScreen();
    printHeader("NHẬP DỮ LIỆU TỪ FILE CSV");
    printInfo("Lưu ý: Nhập \"00\" để hủy bỏ và trở về menu chính.");

    cout << "\nNhập đường dẫn đến file CSV (nhấn Enter để dùng mặc định 'data/students.csv'): ";

    if (cin.peek() == '\n')
    {
        cin.ignore();
    }
    getline(cin, filePathStr);
    filePathStr = trim(filePathStr);

    if (filePathStr == "00")
    {
        if (confirmCancel())
        {
            printInfo("Đã hủy thao tác nhập từ file CSV.");
            break;
        }
    }

    if (filePathStr.empty())
    {
        filePathStr = "data/students.csv"; // Default path
    }

    handleInputFromCSV(filePathStr.c_str(), dataStructureType, arrayList, singlyLinkedList, 
                       circularLinkedList, doublyLinkedListHead, doublyLinkedListTail, binarySearchTree);

    // Reset sort state after loading new data
    currentSortCriteria = -1;
    isSorted = false;
    break;
}
```

**Ví dụ dữ liệu CSV (`data/students1.csv`):**

```csv
MaSV,Ho,Ten,Lop,Diem
N18DCCN015,Hoàng Đức,Anh,D21CQCN01-N,8.7
N18DCCN017,Vũ Tuấn,Kiệt,D21CQCN02-B,10.0
N18DCCN022,Nguyễn Văn,Anh,D21CQCN01-N,9.0
N18DCCN023,Hoàng Đức,Anh,D21CQCN02-B,7.0
N18DCCN024,Phạm Thanh,Hà,D21CQCN01-B,8.5
N18DCCN025,Nguyễn Thị,Thảo,D21CQCN02-B,9.2
```

**Xử lý lỗi:**

- Thông báo rõ ràng nếu file không tồn tại hoặc không thể mở.
- Với mỗi dòng dữ liệu không hợp lệ, hiển thị số dòng và lỗi cụ thể.
- Hiển thị thống kê tổng quan về số dòng hợp lệ/không hợp lệ.
- Xử lý trường hợp file rỗng hoặc thiếu dữ liệu.

### 3.2. Thêm Sinh viên mới

**Mô tả:** Cho phép người dùng nhập thông tin của một sinh viên mới từ giao diện console và thêm vào danh sách sinh viên hiện tại.

**Quy trình:**

1. Hiển thị một form nhập liệu trên console, yêu cầu người dùng nhập lần lượt các thông tin: Mã sinh viên, Họ, Tên, Lớp, Điểm.
2. Với mỗi thông tin nhập vào:

   a. **Mã sinh viên:** Kiểm tra không để trống, không chứa khoảng trắng, và **quan trọng nhất là phải kiểm tra tính duy nhất** (không trùng với bất kỳ mã sinh viên nào đã có trong danh sách). Nếu trùng, yêu cầu nhập lại.

   b. **Họ, Tên, Lớp:** Kiểm tra không được để trống. Có thể áp dụng các chuẩn hóa như viết hoa chữ cái đầu.

   c. **Điểm:** Kiểm tra phải là số thực từ 0.0 đến 10.0.
3. Sau khi người dùng nhập đầy đủ và tất cả thông tin đều hợp lệ, có thể hiển thị lại thông tin đã nhập để người dùng xác nhận.
4. Nếu người dùng xác nhận, tạo một `struct Student` mới và thêm vào cấu trúc dữ liệu đang sử dụng. Cài đặt cho các cấu trúc dữ liệu:

- **Mảng (`ArrayList`):**
  - Kiểm tra xem mảng có còn chỗ trống không (`size < capacity`).
  - Nếu đầy, thực hiện mở rộng mảng: tạo một mảng mới có `capacity` lớn hơn, sao chép tất cả sinh viên từ mảng cũ sang mảng mới, giải phóng bộ nhớ của mảng cũ, và cập nhật con trỏ `students` trỏ đến mảng mới.
  - Thêm sinh viên mới vào vị trí `size` và tăng `size` lên 1.
- **Danh sách Liên kết Đơn/Vòng/Đôi:**
  - Cấp phát động một `Node` mới.
  - Gán dữ liệu sinh viên mới vào `Node`.
  - Liên kết `Node` mới này vào vị trí thích hợp trong danh sách (ví dụ: thêm vào đầu, cuối, hoặc giữ danh sách sắp xếp theo một tiêu chí nào đó nếu có yêu cầu). Cập nhật các con trỏ `head`, `tail` (nếu có) và `size`.

**Trích dẫn Code:**

- **Thêm sinh viên mới:** Người dùng chọn chức năng "Thêm sinh viên mới" (case 3) trong hàm `main` ở `src/main.cpp`. Chương trình yêu cầu nhập mã sinh viên, kiểm tra tính hợp lệ và trùng lặp. Nếu hợp lệ, chương trình yêu cầu nhập các thông tin còn lại của sinh viên. Cuối cùng, hàm `addStudentToDataStructure` được gọi để thêm sinh viên vào cấu trúc dữ liệu đã chọn.

  ```cpp
  // src/main.cpp
  // ...existing code...
        case 3:
        {
            clearScreen();
            printHeader("THÊM SINH VIÊN MỚI");
            printInfo("Lưu ý: Nhập \"00\" để hủy bỏ và trở về menu chính.");

            char studentID[MAX_STUDENT_ID_LENGTH];
            // Bước 1: Nhập và kiểm tra mã sinh viên
            string tempID;
            bool isValid;

            // Nhập và kiểm tra mã sinh viên
            do
            {
                cout << "Nhập mã sinh viên: ";
                cin >> tempID;
                clearInputBuffer();
                tempID = trim(tempID);

                // Kiểm tra hủy bỏ
                if (tempID == CANCEL_INPUT_CODE)
                {
                    if (confirmCancel())
                    {
                        break;
                    }
                    continue;
                }

                // Kiểm tra định dạng mã sinh viên
                isValid = validateAndShowStudentID(tempID);

                // Nếu định dạng hợp lệ, kiểm tra trùng lặp
                if (isValid)
                {
                    isValid = validateAndShowDuplicateStudentID(tempID, dataStructureType, arrayList, singlyLinkedList,
                                                                circularLinkedList, doublyLinkedListHead, binarySearchTree);
                }
            } while (!isValid);

            // Nếu người dùng chọn hủy bỏ
            if (tempID == CANCEL_INPUT_CODE)
            {
                break;
            }

            // Lưu mã sinh viên hợp lệ
            strcpy(studentID, tempID.c_str());

            // Bước 2: Tiếp tục nhập thông tin chi tiết
            Student student;
            strcpy(student.studentID, studentID); // Đặt mã sinh viên đã nhập

            isValid = inputStudent(student);

            if (isValid)
            {
                addStudentToDataStructure(student, dataStructureType, arrayList, singlyLinkedList,
                                          circularLinkedList, doublyLinkedListHead, doublyLinkedListTail,
                                          binarySearchTree);

                // Reset sort state after adding new student
                currentSortCriteria = -1;
                isSorted = false;
            }
            break;
        }
  // ...existing code...
  ```

- **Nhập thông tin sinh viên:** Hàm `inputStudent` trong `src/core/operations.cpp` chịu trách nhiệm nhập các thông tin chi tiết của sinh viên như họ, tên, lớp và điểm, đồng thời kiểm tra tính hợp lệ của từng trường thông tin.

  ```cpp
  // src/core/operations.cpp
  bool inputStudent(Student &student)
  {
      string tempInput;
      bool isValid;

      // Nhập mã sinh viên (chỉ nhập nếu chưa có)
      if (student.studentID[0] == '\0' || strlen(student.studentID) == 0)
      {
          do
          {
              cout << "Nhập mã sinh viên: ";
              getline(cin, tempInput);
              tempInput = trim(tempInput);

              // Kiểm tra hủy bỏ
              if (tempInput == "00")
              {
                  if (confirmCancel())
                  {
                      student.studentID[0] = '\0';
                      return false;
                  }
                  continue;
              }

              isValid = validateAndShowStudentID(tempInput);
              if (isValid)
              {
                  strcpy(student.studentID, tempInput.c_str());
              }
          } while (!isValid);
      }

      // Nhập họ và tên đệm
      do
      {
          cout << "Nhập họ và tên đệm: ";
          getline(cin, tempInput);
          tempInput = trim(tempInput);

          // Kiểm tra hủy bỏ
          if (tempInput == "00")
          {
              if (confirmCancel())
              {
                  student.studentID[0] = '\0';
                  return false;
              }
              continue;
          }

          isValid = validateAndShowName(tempInput);
          if (isValid)
          {
              strcpy(student.firstName, tempInput.c_str());
          }
      } while (!isValid);

      // Nhập tên
      do
      {
          cout << "Nhập tên: ";
          getline(cin, tempInput);
          tempInput = trim(tempInput);

          // Kiểm tra hủy bỏ
          if (tempInput == "00")
          {
              if (confirmCancel())
              {
                  student.studentID[0] = '\0';
                  return false;
              }
              continue;
          }

          isValid = validateAndShowName(tempInput);
          if (isValid)
          {
              strcpy(student.lastName, tempInput.c_str());
          }
      } while (!isValid);

      // Nhập lớp
      do
      {
          cout << "Nhập lớp: ";
          getline(cin, tempInput);
          tempInput = trim(tempInput);

          // Kiểm tra hủy bỏ
          if (tempInput == "00")
          {
              if (confirmCancel())
              {
                  student.studentID[0] = '\0';
                  return false;
              }
              continue;
          }

          isValid = validateAndShowClassName(tempInput);
          if (isValid)
          {
              strcpy(student.studentClass, tempInput.c_str());
          }
      } while (!isValid);

      // Nhập điểm số
      float score;
      string scoreInput;
      do
      {
          cout << "Nhập điểm (0-10): ";
          cin >> scoreInput;

          // Kiểm tra hủy bỏ
          if (scoreInput == "00")
          {
              if (confirmCancel())
              {
                  student.studentID[0] = '\0';
                  return false;
              }
              continue;
          }

          // Chuyển đổi chuỗi thành số float
          try
          {
              score = stof(scoreInput);
              isValid = validateAndShowScore(score);
              if (isValid)
              {
                  student.score = score;
              }
          }
          catch (const exception &e)
          {
              printError("Điểm phải là một số thực.");
              isValid = false;
          }
      } while (!isValid);

      // Clear input buffer for next input
      clearInputBuffer();

      cout << "\n" << GREEN << "✓ Đã nhập thông tin sinh viên thành công!" << RESET << endl;
      displayStudentDetailed(student);

      return true;
  }
  ```

- **Kiểm tra tính hợp lệ của dữ liệu:** Các hàm `validateAndShowStudentID`, `validateAndShowName`, `validateAndShowClassName`, `validateAndShowScore` trong `src/utils/validation.cpp` được sử dụng để kiểm tra và hiển thị thông báo lỗi nếu dữ liệu nhập vào không hợp lệ.

  ```cpp
  // src/utils/validation.cpp
  bool validateAndShowStudentID(const string &studentID)
  {
      bool isValid = validateStudentID(studentID);
      if (!isValid)
      {
          printError(getInvalidFieldMessage("Mã sinh viên").c_str());
          printWarning("Mã sinh viên phải có từ 3-19 ký tự, chỉ bao gồm chữ cái và số, không chứa khoảng trắng.");
      }
      return isValid;
  }

  bool validateAndShowName(const string &name)
  {
      bool isValid = validateName(name);
      if (!isValid)
      {
          printError(getInvalidFieldMessage("Họ/tên").c_str());
          printWarning("Họ/tên chỉ được chứa chữ cái, dấu cách và dấu gạch ngang, tối đa 49 ký tự.");
      }
      return isValid;
  }

  bool validateAndShowClassName(const string &className)
  {
      bool isValid = validateClassName(className);
      if (!isValid)
      {
          printError(getInvalidFieldMessage("Tên lớp").c_str());
          printWarning("Tên lớp phải có từ 2-19 ký tự và chỉ chứa chữ cái, số, dấu gạch ngang, dấu chấm và gạch dưới, không chứa khoảng trắng.");
      }
      return isValid;
  }

  bool validateAndShowScore(float score)
  {
      bool isValid = validateScore(score);
      if (!isValid)
      {
          printError(getInvalidFieldMessage("Điểm số").c_str());
          printWarning("Điểm số phải nằm trong khoảng từ 0.0 đến 10.0.");
      }
      return isValid;
  }
  ```

- **Kiểm tra trùng mã sinh viên:** Hàm `validateAndShowDuplicateStudentID` trong `src/core/operations.cpp` kiểm tra xem mã sinh viên đã tồn tại trong cấu trúc dữ liệu hiện tại hay chưa.

  ```cpp
  // src/core/operations.cpp
  bool validateAndShowDuplicateStudentID(const string &studentID, int dataStructureType,
                                       const ArrayStudentList &arrayList,
                                       NodeSLL *singlyLinkedList,
                                       NodeSLL *circularLinkedList,
                                       NodeDLL *doublyLinkedListHead,
                                       NodeBST *binarySearchTree)
  {
      bool isExist = isStudentExists(studentID.c_str(), dataStructureType, arrayList,
                                     singlyLinkedList, circularLinkedList, doublyLinkedListHead, binarySearchTree);
      if (isExist)
      {
          printError(("Mã sinh viên " + studentID + " đã tồn tại!").c_str());
      }
      return !isExist;
  }

### 3.3. Xóa hoặc Cập nhật Thông tin Sinh viên

**Mô tả:** Cho phép người dùng xóa một sinh viên khỏi danh sách hoặc cập nhật thông tin của một sinh viên đã có, dựa trên Mã sinh viên.

**Trích dẫn Code:**

- **Xóa sinh viên:** Người dùng chọn chức năng "Xóa sinh viên" (case 4) trong hàm `main` ở `src/main.cpp`. Chương trình yêu cầu nhập mã sinh viên, sau đó gọi hàm `deleteStudentFromDataStructure` để xóa sinh viên khỏi cấu trúc dữ liệu đã chọn.

  ```cpp
  // src/main.cpp
  // ...existing code...
          case 4:
          {
              char studentID[MAX_STUDENT_ID_LENGTH];
              if (inputStudentID(studentID))
              {
                  deleteStudentFromDataStructure(studentID, dataStructureType, arrayList, singlyLinkedList,
                                                 circularLinkedList, doublyLinkedListHead, doublyLinkedListTail);
              }
              break;
          }
  // ...existing code...
  ```

- **Cập nhật thông tin sinh viên:** Người dùng chọn chức năng "Cập nhật thông tin sinh viên" (case 5) trong hàm `main` ở `src/main.cpp`. Chương trình yêu cầu nhập mã sinh viên, kiểm tra sự tồn tại, sau đó yêu cầu nhập thông tin mới và gọi hàm `updateStudentInDataStructure`.

  ```cpp
  // src/main.cpp
  // ...existing code...
          case 5:
          {
              char studentID[MAX_STUDENT_ID_LENGTH];
              if (inputStudentID(studentID))
              {
                  // Kiểm tra xem sinh viên có tồn tại không
                  bool exists = isStudentExists(studentID, dataStructureType, arrayList, singlyLinkedList,
                                                circularLinkedList, doublyLinkedListHead);

                  if (exists)
                  {
                      // Lấy thông tin sinh viên hiện tại
                      Student currentStudent;
                      if (getStudentFromDataStructure(studentID, dataStructureType, arrayList, singlyLinkedList,
                                                      circularLinkedList, doublyLinkedListHead, currentStudent))
                      {
                          Student updateStudent = currentStudent; // Bắt đầu với thông tin hiện tại

                          if (inputStudentForUpdate(updateStudent))
                          {
                              updateStudentInDataStructure(updateStudent, dataStructureType, arrayList, singlyLinkedList,
                                                           circularLinkedList, doublyLinkedListHead);
                          }
                      }
                  }
                  else
                  {
                      printError(("Không tìm thấy sinh viên có mã " + string(studentID) + ".").c_str());
                  }
              }
              break;
          }
  // ...existing code...
  ```

- **Hàm xóa sinh viên khỏi cấu trúc dữ liệu:** Hàm `deleteStudentFromDataStructure` trong `src/core/operations.cpp` xử lý logic xóa cho từng loại cấu trúc dữ liệu.

  ```cpp
  // src/core/operations.cpp
  // ...existing code...
  bool deleteStudentFromDataStructure(const char *studentID, int dataStructureType,
                                      ArrayStudentList &arrayList,
                                      NodeSLL *&singlyLinkedList,
                                      NodeSLL *&circularLinkedList,
                                      NodeDLL *&doublyLinkedListHead,
                                      NodeDLL *&doublyLinkedListTail)
  {
      bool success = false;

      switch (dataStructureType)
      {
      case ARRAY_LIST:
          if (deleteFromArrayList(arrayList, studentID))
          {
              printSuccess("Đã xóa sinh viên khỏi danh sách mảng thành công.");
              success = true;
          }
          else
          {
              printError("Không tìm thấy sinh viên để xóa trong danh sách mảng.");
          }
          break;
      case SINGLY_LINKED_LIST:
          if (deleteFromSLL(singlyLinkedList, studentID))
          {
              printSuccess("Đã xóa sinh viên khỏi danh sách liên kết đơn thành công.");
              success = true;
          }
          else
          {
              printError("Không tìm thấy sinh viên để xóa trong danh sách liên kết đơn.");
          }
          break;
      case CIRCULAR_LINKED_LIST:
          if (deleteFromCLL(circularLinkedList, studentID))
          {
              printSuccess("Đã xóa sinh viên khỏi danh sách liên kết vòng thành công.");
              success = true;
          }
          else
          {
              printError("Không tìm thấy sinh viên để xóa trong danh sách liên kết vòng.");
          }
          break;
      case DOUBLY_LINKED_LIST:
          if (deleteFromDLL(doublyLinkedListHead, doublyLinkedListTail, studentID))
          {
              printSuccess("Đã xóa sinh viên khỏi danh sách liên kết đôi thành công.");
              success = true;
          }
          else
          {
              printError("Không tìm thấy sinh viên để xóa trong danh sách liên kết đôi.");
          }
          break;
      // Trường hợp BINARY_SEARCH_TREE không được xử lý ở đây vì thường xóa theo key (điểm)
      default:
          printError("Cấu trúc dữ liệu không hợp lệ hoặc không hỗ trợ xóa trực tiếp bằng ID.");
          break;
      }

      return success;
  }
  ```

- **Hàm cập nhật sinh viên trong cấu trúc dữ liệu:** Hàm `updateStudentInDataStructure` trong `src/core/operations.cpp` xử lý logic cập nhật cho từng loại cấu trúc dữ liệu.

  ```cpp
  // src/core/operations.cpp
  // ...existing code...
  bool updateStudentInDataStructure(const Student &student, int dataStructureType,
                                    ArrayStudentList &arrayList,
                                    NodeSLL *&singlyLinkedList,
                                    NodeSLL *&circularLinkedList,
                                    NodeDLL *&doublyLinkedListHead)
  {
      bool success = false;
      switch (dataStructureType)
      {
      case ARRAY_LIST:
          if (updateInArrayList(arrayList, student))
          {
              printSuccess("Đã cập nhật thông tin sinh viên trong danh sách mảng.");
              success = true;
          }
          else
          {
              printError("Không tìm thấy sinh viên để cập nhật trong danh sách mảng.");
          }
          break;
      case SINGLY_LINKED_LIST:
          if (updateInSLL(singlyLinkedList, student))
          {
              printSuccess("Đã cập nhật thông tin sinh viên trong danh sách liên kết đơn.");
              success = true;
          }
          else
          {
              printError("Không tìm thấy sinh viên để cập nhật trong danh sách liên kết đơn.");
          }
          break;
      case CIRCULAR_LINKED_LIST:
          if (updateInCLL(circularLinkedList, student))
          {
              printSuccess("Đã cập nhật thông tin sinh viên trong danh sách liên kết vòng.");
              success = true;
          }
          else
          {
              printError("Không tìm thấy sinh viên để cập nhật trong danh sách liên kết vòng.");
          }
          break;
      case DOUBLY_LINKED_LIST:
          if (updateInDLL(doublyLinkedListHead, student))
          {
              printSuccess("Đã cập nhật thông tin sinh viên trong danh sách liên kết đôi.");
              success = true;
          }
          else
          {
              printError("Không tìm thấy sinh viên để cập nhật trong danh sách liên kết đôi.");
          }
          break;
      // BST thường cập nhật bằng cách xóa node cũ và chèn node mới nếu key (điểm) thay đổi.
      // Nếu chỉ cập nhật thông tin không phải key, có thể tìm và sửa trực tiếp.
      default:
          printError("Cấu trúc dữ liệu không hợp lệ hoặc không hỗ trợ cập nhật.");
          break;
      }
      return success;
  }
  ```

#### Tìm kiếm sinh viên theo Mã số

Đây là bước chung cho cả Xóa và Cập nhật.

1. Yêu cầu người dùng nhập Mã sinh viên cần tìm.
2. Duyệt qua cấu trúc dữ liệu đang sử dụng:
   - **Mảng:** Duyệt từ đầu đến cuối, so sánh `studentID` của từng sinh viên với mã cần tìm bằng `strcmp()`.
   - **DSLK:** Duyệt từ `head` (hoặc `tail->next` cho DSLK Vòng) đến hết danh sách, so sánh tương tự.
3. Nếu tìm thấy sinh viên, trả về con trỏ tới `struct Student` đó (hoặc chỉ số trong mảng, con trỏ tới `Node` trong DSLK). Nếu không tìm thấy, thông báo cho người dùng.

### 3.4. Thống kê Sinh viên

**Mô tả:** Cung cấp các thông tin thống kê tổng quan về danh sách sinh viên.

**Các loại thống kê được cài đặt:**

- **Liệt kê sinh viên có điểm cao nhất:**
  1. Khởi tạo `maxScore` bằng điểm của sinh viên đầu tiên (hoặc giá trị rất nhỏ).
  2. Duyệt qua toàn bộ danh sách. Nếu điểm của sinh viên hiện tại lớn hơn `maxScore`, cập nhật `maxScore`.
  3. Sau khi tìm được `maxScore`, duyệt lại danh sách một lần nữa và hiển thị thông tin của tất cả sinh viên có điểm bằng `maxScore`.
- **Liệt kê sinh viên có điểm thấp nhất:** Tương tự như tìm điểm cao nhất, nhưng so sánh để tìm `minScore`.
- **Tính điểm trung bình của cả lớp:**
  1. Khởi tạo `totalScore = 0.0` và `studentCount = 0`.
  2. Duyệt qua danh sách, cộng dồn điểm của mỗi sinh viên vào `totalScore` và tăng `studentCount`.
  3. Nếu `studentCount > 0`, điểm trung bình = `totalScore / studentCount`. Hiển thị kết quả.
- **Phân loại học lực sinh viên (ví dụ):**
  - Định nghĩa các ngưỡng điểm cho từng loại học lực: Giỏi (8.0 - 10.0), Khá (6.5 - 7.9), Trung bình (5.0 - 6.4), Yếu (< 5.0).
  - Duyệt qua danh sách, với mỗi sinh viên, xác định học lực dựa trên điểm số và đếm số lượng sinh viên thuộc mỗi loại.
  - Hiển thị số lượng (hoặc tỷ lệ %) sinh viên theo từng loại học lực.
**Xử lý trường hợp đặc biệt:**
- Nếu danh sách rỗng, tất cả các chức năng thống kê nên hiển thị thông báo "Danh sách sinh viên rỗng."

**Trích dẫn Code:**

- **Thống kê sinh viên:** Người dùng chọn chức năng "Thống kê sinh viên" (case 7) trong hàm `main` ở `src/main.cpp`. Chương trình hiển thị menu con để cho phép người dùng chọn loại thống kê: tổng quát, theo lớp, hoặc cả hai.

```cpp
// From src/main.cpp
case 7: // Thống kê sinh viên
{
    performStatistics(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead);
    break;
}
```

- **Hàm thực hiện thống kê:** Hàm `performStatistics` trong `src/core/operations.cpp` hỗ trợ nhiều cấu trúc dữ liệu và cung cấp menu lựa chọn loại thống kê.

```cpp
// From src/core/operations.cpp
void performStatistics(int dataStructureType,
                       const ArrayStudentList &arrayList,
                       NodeSLL *singlyLinkedList,
                       NodeSLL *circularLinkedList,
                       NodeDLL *doublyLinkedListHead)
{
    // Kiểm tra dữ liệu có rỗng không
    if (isDataStructureEmpty(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead, NULL))
    {
        printError("Danh sách sinh viên trống. Vui lòng nhập dữ liệu trước khi thực hiện thống kê!");
        return;
    }

    // Hiển thị menu chọn loại thống kê
    printHeader("CHỌN LOẠI THỐNG KÊ");
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃                                       MENU THỐNG KÊ                                          ┃" << endl;
    cout << "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
    cout << "┃ 1. Thống kê tổng quát                                                                       ┃" << endl;
    cout << "┃ 2. Thống kê theo lớp                                                                        ┃" << endl;
    cout << "┃ 3. Cả hai loại thống kê                                                                     ┃" << endl;
    cout << "┃ 0. Quay lại                                                                                 ┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;

    int choice;
    do
    {
        cout << "Nhập lựa chọn: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            performGeneralStatistics(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead);
            break;
        case 2:
            displayAllClassStatistics(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead);
            break;
        case 3:
            performGeneralStatistics(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead);
            cout << endl;
            displayAllClassStatistics(dataStructureType, arrayList, singlyLinkedList, circularLinkedList, doublyLinkedListHead);
            break;
        case 0:
            return;
        default:
            printError("Lựa chọn không hợp lệ!");
            break;
        }
    } while (choice != 0 && choice != 1 && choice != 2 && choice != 3);
}
```

### 3.5. Sắp xếp Danh sách Sinh viên

**Mô tả:** Cho phép sắp xếp danh sách sinh viên theo các tiêu chí khác nhau (Mã SV, Tên, Điểm) bằng các thuật toán sắp xếp được cài đặt thủ công.

**Các thuật toán sắp xếp được cài đặt:**

- **Bubble Sort:**
  - So sánh các cặp phần tử liền kề và đổi chỗ nếu chúng không đúng thứ tự (ví dụ: phần tử đứng trước lớn hơn phần tử đứng sau khi sắp xếp tăng dần). Lặp lại quá trình này cho đến khi không còn sự đổi chỗ nào.
  - Độ phức tạp thời gian: O(n²) trong trường hợp xấu nhất và trung bình.
  - Cài đặt: Có thể áp dụng cho Mảng. Với DSLK, việc đổi chỗ phức tạp hơn và kém hiệu quả.
- **Selection Sort:**
  - Tìm phần tử nhỏ nhất (hoặc lớn nhất) trong phần chưa được sắp xếp của danh sách và đổi chỗ nó với phần tử đầu tiên của phần chưa sắp xếp. Lặp lại cho đến khi toàn bộ danh sách được sắp xếp.
  - Độ phức tạp thời gian: O(n²) trong mọi trường hợp.
  - Cài đặt: Tương tự Bubble Sort, dễ áp dụng cho Mảng.
- **Insertion Sort:**
  - Duyệt qua danh sách từ phần tử thứ hai. Với mỗi phần tử, so sánh nó với các phần tử đã được sắp xếp ở phía trước và chèn nó vào đúng vị trí.
  - Độ phức tạp thời gian: O(n²) trong trường hợp xấu nhất, O(n) trong trường hợp tốt nhất (danh sách đã sắp xếp).
  - Cài đặt: Hiệu quả cho danh sách nhỏ hoặc gần như đã sắp xếp. Áp dụng được cho cả Mảng và DSLK.
- **Quick Sort (khuyến khích cho Mảng/DSLK Đôi):**
  - Chọn một phần tử làm "pivot". Phân hoạch các phần tử khác thành hai nhóm: nhóm nhỏ hơn pivot và nhóm lớn hơn pivot. Đệ quy sắp xếp hai nhóm này.
  - Độ phức tạp thời gian trung bình: O(n log n). Xấu nhất: O(n²).
  - Cài đặt: Hiệu quả nhất cho Mảng. Với DSLK Đôi cũng có thể cài đặt hiệu quả. Với DSLK Đơn khó hơn.
- **Merge Sort (khuyến khích cho Mảng/DSLK):**
  - Chia danh sách thành hai nửa bằng nhau. Đệ quy sắp xếp từng nửa. Sau đó, trộn (merge) hai nửa đã sắp xếp lại thành một danh sách duy nhất đã sắp xếp.
  - Độ phức tạp thời gian: O(n log n) trong mọi trường hợp.
  - Cài đặt: Phù hợp cho cả Mảng và DSLK. Cần thêm không gian phụ để trộn.
  
**Trích dẫn Code:**

- **Sắp xếp sinh viên:** Người dùng chọn chức năng "Sắp xếp sinh viên theo tiêu chí" (case 8) trong hàm `main` ở `src/main.cpp`. Chương trình cho phép người dùng chọn thuật toán sắp xếp và tiêu chí sắp xếp, sau đó đo thời gian thực thi.

```cpp
// From src/main.cpp
        case 8: // Sắp xếp sinh viên theo tiêu chí
        {
            int sortAlgorithm = selectSortAlgorithm(dataStructureType);
            if (sortAlgorithm != -1)
            {
                int sortCriteria = selectSortCriteria();
                if (sortCriteria != -1)
                {
                    // Đo thời gian thực thi
                    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

                    bool success = sortStudentList(dataStructureType, sortAlgorithm, sortCriteria, arrayList,
                                                   singlyLinkedList, circularLinkedList, doublyLinkedListHead,
                                                   doublyLinkedListTail);

                    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
                    chrono::microseconds duration = chrono::duration_cast<chrono::microseconds>(end - start);

                    if (success)
                    {
                        // Update sort state for enhanced search optimization
                        currentSortCriteria = sortCriteria;
                        isSorted = true;

                        cout << BOLD << GREEN << "\n✓ Thời gian thực thi: " << duration.count() << " microseconds ("
                             << (double)duration.count() / 1000.0 << " ms)" << RESET << endl;
                    }
                }
            }
            break;
        }
```

**Các tính năng nổi bật:**

1. **Lựa chọn thuật toán:** Hàm `selectSortAlgorithm()` cho phép người dùng chọn thuật toán sắp xếp phù hợp với cấu trúc dữ liệu đang sử dụng.

2. **Lựa chọn tiêu chí:** Hàm `selectSortCriteria()` cho phép sắp xếp theo mã sinh viên, tên, hoặc điểm số.

3. **Đo thời gian thực thi:** Sử dụng `chrono::high_resolution_clock` để đo và hiển thị thời gian thực thi chính xác.

4. **Tối ưu hóa tìm kiếm:** Sau khi sắp xếp, hệ thống ghi nhớ trạng thái đã sắp xếp để tối ưu hóa các tìm kiếm tiếp theo.

```cpp
// From src/algorithms/sorting.cpp
// --- QuickSort cho danh sách mảng ---
// Hàm phân vùng (partition) cho thuật toán QuickSort
int partitionArrayList(ArrayStudentList &list, int low, int high)
{
    float pivot = list.students[high].score; // Chọn phần tử cuối làm pivot
    int i = low - 1;                         // Vị trí của phần tử nhỏ hơn

    for (int j = low; j < high; j++)
    {
        // Nếu phần tử hiện tại nhỏ hơn hoặc bằng pivot
        if (list.students[j].score <= pivot)
        {
            i++;
            // Hoán đổi list.students[i] và list.students[j]
            Student temp = list.students[i];
            list.students[i] = list.students[j];
            list.students[j] = temp;
        }
    }

    // Hoán đổi list.students[i+1] và list.students[high] (pivot)
    Student temp = list.students[i + 1];
    list.students[i + 1] = list.students[high];
    list.students[high] = temp;

    return i + 1;
}

// Thuật toán QuickSort
void quickSortArrayList(ArrayStudentList &list, int low, int high)
{
    if (low < high)
    {
        // Tìm vị trí phân vùng
        int pi = partitionArrayList(list, low, high);

        // Sắp xếp các phần tử trước và sau vị trí phân vùng
        quickSortArrayList(list, low, pi - 1);
        quickSortArrayList(list, pi + 1, high);
    }
}

// Hàm gọi QuickSort
void quickSortArrayList(ArrayStudentList &list)
{
    if (list.count <= 1)
    {
        return; // Danh sách đã sắp xếp
    }

    quickSortArrayList(list, 0, list.count - 1);
}
```

**Tiêu chí sắp xếp:**

- Theo Mã sinh viên (thứ tự từ điển, tăng dần).
- Theo Tên (thứ tự từ điển, tăng dần). Nếu tên trùng thì có thể sắp xếp theo Họ.
- Theo Điểm (tăng dần hoặc giảm dần).

**Đo thời gian thực hiện:** Sử dụng thư viện `<chrono>` của C++ để đo thời gian bắt đầu và kết thúc quá trình sắp xếp để so sánh hiệu suất của các thuật toán.

### 3.6. Tìm kiếm Sinh viên

**Mô tả:** Cung cấp các phương pháp tìm kiếm sinh viên dựa trên các trường thông tin khác nhau (Mã SV, Tên, Lớp, Điểm) với các thuật toán tìm kiếm được cài đặt thủ công.

**Trích dẫn Code từ `src/main.cpp` (Xử lý lựa chọn tìm kiếm):**

- **Tìm kiếm nâng cao:** Người dùng chọn chức năng "Tìm kiếm nâng cao với nhiều tiêu chí" (case 9) trong hàm `main`. Hệ thống sử dụng thông tin trạng thái sắp xếp để tối ưu hóa tìm kiếm.

```cpp
// From src/main.cpp
        case 9: // Tìm kiếm nâng cao với nhiều tiêu chí
        {
            searchStudentInDataStructure(dataStructureType, arrayList, singlyLinkedList,
                                         circularLinkedList, doublyLinkedListHead, doublyLinkedListTail,
                                         isSorted ? currentSortCriteria : -1);
            break;
        }
```

**Tính năng nổi bật:**

1. **Tìm kiếm đa tiêu chí:** Hỗ trợ tìm kiếm theo mã sinh viên, tên, lớp, và điểm số.

2. **Tối ưu hóa thông minh:** Sử dụng thông tin về trạng thái sắp xếp hiện tại (`isSorted ? currentSortCriteria : -1`) để áp dụng thuật toán tìm kiếm phù hợp.

3. **Hỗ trợ đa cấu trúc:** Hoạt động với tất cả các cấu trúc dữ liệu được hỗ trợ.

**Các thuật toán tìm kiếm được cài đặt:**

- **Sequential Search (Tìm kiếm tuần tự):**
  - Duyệt qua từng phần tử trong danh sách từ đầu đến cuối để tìm phần tử có giá trị trùng khớp.
  - Độ phức tạp thời gian: O(n) trong trường hợp xấu nhất.
  - Áp dụng được cho tất cả các cấu trúc dữ liệu và không yêu cầu danh sách được sắp xếp trước.

  **Ví dụ cài đặt (`src/algorithms/searching.cpp`):**

  ```cpp
  // From src/algorithms/searching.cpp
  // Tìm kiếm tuần tự trong mảng sinh viên
  SearchResult sequentialSearchArray(const ArrayStudentList &list, const char *keyword, int searchCriteria)
  {
      return sequentialSearch(const_cast<Student *>(list.students), list.count, keyword, searchCriteria);
  }

  // Hàm tìm kiếm tuần tự chính
  SearchResult sequentialSearch(Student *students, int totalCount, const char *keyword, int searchCriteria)
  {
      SearchResult result;
      result.students = nullptr;
      result.count = 0;
      result.isBinarySearch = false;

      SearchTimer timer = startTimer();

      // Đếm số lượng kết quả trước
      int matchCount = 0;
      for (int i = 0; i < totalCount; i++)
      {
          if (checkStudentMatch(students[i], keyword, searchCriteria))
          {
              matchCount++;
          }
      }

      if (matchCount > 0)
      {
          result.students = new Student[matchCount];
          result.count = matchCount;

          int resultIndex = 0;
          for (int i = 0; i < totalCount; i++)
          {
              if (checkStudentMatch(students[i], keyword, searchCriteria))
              {
                  result.students[resultIndex] = students[i];
                  resultIndex++;
              }
          }
      }

      stopTimer(timer);
      result.searchTimeMs = getElapsedTimeMs(timer);

      return result;
  }
  ```

- **Binary Search (Tìm kiếm nhị phân):**
  - Chỉ áp dụng được khi danh sách đã được sắp xếp theo trường cần tìm kiếm.
  - So sánh giá trị cần tìm với phần tử ở giữa danh sách. Nếu bằng nhau thì tìm thấy. Nếu nhỏ hơn thì tìm ở nửa trái, nếu lớn hơn thì tìm ở nửa phải.
  - Độ phức tạp thời gian: O(log n).
  - Chỉ hiệu quả với mảng do yêu cầu truy cập ngẫu nhiên nhanh.

  **Ví dụ cài đặt (`src/algorithms/searching.cpp`):**

  ```cpp
  // From src/algorithms/searching.cpp
  // Tìm kiếm nhị phân trong mảng đã sắp xếp
  SearchResult binarySearchArray(const ArrayStudentList &list, const char *keyword, int searchCriteria, int sortCriteria)
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
      // Xử lý các tiêu chí khác...

      stopTimer(timer);
      result.searchTimeMs = getElapsedTimeMs(timer);

      return result;
  }
  ```
