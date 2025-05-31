#ifndef KNIGHTS_TOUR_H
#define KNIGHTS_TOUR_H

#include <iostream>
#include "../utils/constants.h"

using namespace std;

// ========== Cài đặt thuật toán Mã Đi Tuần (Knight's Tour) ==========

// Bàn cờ và các bước di chuyển
int knightsTourBoard[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE];
int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// Hàm kiểm tra nước đi có hợp lệ hay không
bool isSafe(int x, int y)
{
    return (x >= 0 && x < CHESS_BOARD_SIZE && y >= 0 && y < CHESS_BOARD_SIZE && knightsTourBoard[x][y] == -1);
}

// Hàm hiển thị bàn cờ với đường đi của quân mã
void printKnightsTour()
{
    cout << "Đường đi của quân mã:\n";
    for (int i = 0; i < CHESS_BOARD_SIZE; i++)
    {
        for (int j = 0; j < CHESS_BOARD_SIZE; j++)
        {
            cout << knightsTourBoard[i][j] << "\t";
        }
        cout << "\n";
    }
}

// Hàm đệ quy giải bài toán Mã Đi Tuần sử dụng kỹ thuật quay lui (backtracking)
bool solveKnightsTour(int x, int y, int moveCount)
{
    // Nếu tất cả các ô đã được đi qua
    if (moveCount == CHESS_BOARD_SIZE * CHESS_BOARD_SIZE)
    {
        return true;
    }

    // Thử tất cả các nước đi tiếp theo từ vị trí hiện tại
    for (int k = 0; k < 8; k++)
    {
        int nextX = x + xMove[k];
        int nextY = y + yMove[k];

        if (isSafe(nextX, nextY))
        {
            knightsTourBoard[nextX][nextY] = moveCount;

            if (solveKnightsTour(nextX, nextY, moveCount + 1))
            {
                return true;
            }
            else
            {
                // Quay lui (backtrack)
                knightsTourBoard[nextX][nextY] = -1;
            }
        }
    }

    return false;
}

// Hàm khởi tạo và giải bài toán Mã Đi Tuần
bool knightsTour()
{
    // Khởi tạo bàn cờ với tất cả các ô chưa được đi qua
    for (int i = 0; i < CHESS_BOARD_SIZE; i++)
    {
        for (int j = 0; j < CHESS_BOARD_SIZE; j++)
        {
            knightsTourBoard[i][j] = -1;
        }
    }

    // Quân mã bắt đầu ở ô (0,0)
    knightsTourBoard[0][0] = 0;

    // Giải bài toán
    if (!solveKnightsTour(0, 0, 1))
    {
        cout << "Không tìm thấy giải pháp.\n";
        return false;
    }

    // Hiển thị đường đi
    printKnightsTour();
    return true;
}

#endif // KNIGHTS_TOUR_H