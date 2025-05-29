#ifndef KNIGHTS_TOUR_H
#define KNIGHTS_TOUR_H

// Kích thước bảng cờ
#define N 8

// Hàm chính để thực hiện và hiển thị bài toán mã đi tuần
void knightsTour();

// Kiểm tra bước đi tiếp theo có hợp lệ không
bool isSafe(int x, int y, int sol[N][N]);

// In ra bàn cờ
void printSolution(int sol[N][N]);

// Giải bài toán mã đi tuần sử dụng kỹ thuật quay lui
bool solveKnightsTour();

// Hàm đệ quy để giải bài toán
bool solveKnightsTourUtil(int x, int y, int movei, int sol[N][N],
                        int xMove[N], int yMove[N]);

// Nếu hàm isAccessible được sử dụng, định nghĩa nó ở đây
int getDegree(int x, int y, int sol[N][N], int xMove[N], int yMove[N]);

// Hàm tiện ích
int min(int x, int y);

#endif // KNIGHTS_TOUR_H