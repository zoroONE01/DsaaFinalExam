#include "../../include/utils/common_utils.h"
#include "../../include/utils/validation.h"
#include "../../include/ui/common_ui.h"
#include <iomanip>

using namespace std;

// ========== Định nghĩa hằng số ==========
const char* CANCEL_INPUT_CODE = "00";

// ========== Đọc dữ liệu từ file CSV ==========
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

// ========== Lưu dữ liệu ra file CSV ==========
bool writeToCSVFile(const char *filename, const ArrayStudentList &list)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        return false; // Không thể tạo hoặc mở file để ghi
    }

    // Ghi dòng tiêu đề
    file << "StudentID,FirstName,LastName,Class,Score" << endl;

    // Ghi dữ liệu từng sinh viên
    for (int i = 0; i < list.count; i++)
    {
        file << list.students[i].studentID << ","
             << list.students[i].firstName << ","
             << list.students[i].lastName << ","
             << list.students[i].studentClass << ","
             << fixed << setprecision(1) << list.students[i].score;
        
        // Không thêm newline cho dòng cuối cùng để tránh dòng trống
        if (i < list.count - 1)
        {
            file << endl;
        }
    }

    file.close();
    return true;
}

// Hàm trim() để loại bỏ khoảng trắng ở đầu và cuối chuỗi
string trim(string str)
{
    // Loại bỏ khoảng trắng ở đầu chuỗi
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == string::npos)
        return "";

    // Loại bỏ khoảng trắng ở cuối chuỗi
    size_t end = str.find_last_not_of(" \t\n\r\f\v");

    // Trả về chuỗi đã được trim
    return str.substr(start, end - start + 1);
}
