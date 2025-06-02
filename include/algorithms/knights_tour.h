#ifndef KNIGHTS_TOUR_H
#define KNIGHTS_TOUR_H

#include <iostream>
#include "../utils/constants.h"

using namespace std;

// ========== Khai báo thuật toán Mã Đi Tuần (Knight's Tour) ==========

// Biến toàn cục cho bàn cờ và các bước di chuyển
extern int knightsTourBoard[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE];
extern int xMove[8];
extern int yMove[8];

// Khai báo các hàm
bool isSafe(int x, int y);
void printKnightsTour();
bool solveKnightsTour(int x, int y, int moveCount);
bool knightsTour();

#endif // KNIGHTS_TOUR_H