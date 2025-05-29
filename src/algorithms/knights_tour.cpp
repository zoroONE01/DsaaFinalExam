#include "../../include/algorithms/knights_tour.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

// Mảng lưu các bước đi có thể của mã (quân ngựa) theo quy tắc chữ L
int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// Kiểm tra bước đi tiếp theo có hợp lệ không
bool isSafe(int x, int y, int sol[N][N])
{
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
}

// In ra bàn cờ với các số hiển thị thứ tự các bước đi
void printSolution(int sol[N][N])
{
    cout << "Thứ tự các bước đi của quân mã trên bàn cờ " << N << "x" << N << ":" << endl;

    // In số cột để dễ đọc
    cout << "   ";
    for (int i = 0; i < N; i++)
        cout << setw(3) << i;
    cout << endl;

    // In dòng phân cách
    cout << "  +" << string(N * 3, '-') << "+" << endl;

    for (int x = 0; x < N; x++)
    {
        // In số hàng
        cout << setw(2) << x << "|";

        for (int y = 0; y < N; y++)
            cout << setw(3) << sol[x][y];

        cout << " |" << endl;
    }

    // In dòng phân cách cuối
    cout << "  +" << string(N * 3, '-') << "+" << endl;
}

// Function to min of two numbers
int min(int x, int y)
{
    return (x <= y) ? x : y;
}

// Tìm mức độ tiếp cận (số bước đi có thể tiếp theo) từ vị trí hiện tại
int getDegree(int x, int y, int sol[N][N], int xMove[8], int yMove[8])
{
    int count = 0;
    for (int i = 0; i < 8; i++)
        if (isSafe(x + xMove[i], y + yMove[i], sol))
            count++;

    return count;
}

// Hàm đệ quy để giải bài toán sử dụng Warnsdorff's Algorithm
bool solveKnightsTourUtil(int x, int y, int movei, int sol[N][N],
                          int xMove[8], int yMove[8])
{
    int nx, ny, min_deg_idx, c, min_deg;

    // Nếu đã đi hết N*N ô
    if (movei == N * N)
        return true;

    // Thử tất cả các bước đi tiếp theo từ vị trí hiện tại
    min_deg = 9; // Giá trị lớn hơn mức độ tiếp cận tối đa có thể (8)
    min_deg_idx = -1;

    // Thử tất cả 8 hướng có thể
    for (int i = 0; i < 8; i++)
    {
        nx = x + xMove[i];
        ny = y + yMove[i];

        if (isSafe(nx, ny, sol))
        {
            // Tìm mức độ tiếp cận của ô tiếp theo
            c = getDegree(nx, ny, sol, xMove, yMove);

            // Nếu mức độ tiếp cận nhỏ hơn mức tối thiểu hiện tại, cập nhật
            if (c < min_deg)
            {
                min_deg = c;
                min_deg_idx = i;
            }
        }
    }

    // Nếu không tìm thấy bước đi tiếp theo
    if (min_deg_idx == -1)
        return false;

    // Thực hiện bước đi với mức độ tiếp cận nhỏ nhất
    nx = x + xMove[min_deg_idx];
    ny = y + yMove[min_deg_idx];

    sol[nx][ny] = movei;

    // Đệ quy để tìm giải pháp từ vị trí mới
    if (solveKnightsTourUtil(nx, ny, movei + 1, sol, xMove, yMove))
        return true;

    // Nếu hướng đi này không dẫn đến giải pháp, quay lui
    sol[nx][ny] = -1;
    return false;
}

// Giải bài toán mã đi tuần
bool solveKnightsTour()
{
    // Khởi tạo ma trận giải pháp
    int sol[N][N];

    // Khởi tạo mảng giải pháp với -1
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            sol[x][y] = -1;

    // Vị trí xuất phát của mã (ngựa)
    int start_x = 0;
    int start_y = 0;

    // Đặt vị trí xuất phát
    sol[start_x][start_y] = 0;

    // Bắt đầu thuật toán quay lui từ vị trí xuất phát
    if (!solveKnightsTourUtil(start_x, start_y, 1, sol, xMove, yMove))
    {
        cout << "Không tìm thấy giải pháp cho bài toán mã đi tuần với điểm bắt đầu ("
             << start_x << "," << start_y << ")" << endl;
        return false;
    }
    else
    {
        printSolution(sol);
        return true;
    }
}

// Hàm chính để thực hiện và hiển thị bài toán mã đi tuần
void knightsTour()
{
    cout << "Bài toán Mã đi tuần\n";
    cout << "====================\n\n";
    cout << "Tìm một đường đi cho quân mã trên bàn cờ " << N << "x" << N << " sao cho quân mã đi qua mỗi ô đúng một lần.\n\n";

    solveKnightsTour();

    cout << "\nGiải thích:\n";
    cout << "- Số 0 là vị trí bắt đầu.\n";
    cout << "- Các số từ 1 đến " << (N * N - 1) << " là thứ tự các bước đi tiếp theo.\n";
    cout << "- Quân mã di chuyển theo hình chữ L (đi 2 ô theo một hướng rồi rẽ ngang để đi thêm 1 ô).\n";
}