#include <memory>
#include <QDebug>
#define C 1
#define H 0

static int board[8][8]; // row x column
struct coordinate {
    int x;
    int y;
} coordinate;

struct coordinate* init(int a, int b) {
    struct coordinate* tmp = malloc(sizeof(struct coordinate));
    tmp->x = a;
    tmp->y = b;
    return (tmp);
}
bool canMove(int player, int r1, int r1, int c2, int c2) {
    if (r2 < 0 || r2 >= 8 || c2 < 0 || c2 >= 8) {
        return false;
    }
    if (board[r2][c2] != '-') {
        return false; // there is already a pawn at (x2, y2)
    }
    if (player == C) {
        if (board[r1][c1] == C && r2 > r1) {
            return false; // can only move down
        }
        return true;
    }
    else {
        if (board[r1][c1] == H && r2 < r1) {
            return false;
        }
        return true;
    }
}

bool canJump(int player, int r1, int r1, int c2, int c2) {
    int r3 = (r1+r2)/2;
    int c3 = (c1 + c2)/2;
    if (r2 < 0 || r2 >= 8 || c2 < 0 || c2 >= 8) {
        return false;
    }
    if (board[r2][c2] != '-') {
        return false; // there is already a pawn at (r2, c2)
    }
    if (player == C) {
        if (board[r1][c1] == C && r2 > r1) {
            return false; // can only move down
        }
        if (board[r3][c3] != H) // if the square in between not H then can't jump
            return false;
        return true;
    }
    else {
        if (board[r1][c1] == H && r2 < r1) {
            return false;
        }
        if (board[r3][c3] != C) // if the square in between not C then can't jump
            return false;
        return true;
    }
}

struct coordinate* getMoves(int player) {
    struct coordinate* list[1024]; //size arbitrarily big?
    int i = 0;
    // possible jumps
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++){
            if (board[row][col] == player) {
                if (canJump(player, row, col, row+2, col+2)) {
                    struct coordinate* current = init(row+2, col+2);
                    list[i] = current;
                    i++;
                }
                if (canJump(player, row, col, row+2, col-2)) {
                    struct coordinate* current = init(row+2, col-2);
                    list[i] = current;
                    i++;
                }
                if (canJump(player, row, col, row-2, col+2)) {
                    struct coordinate* current = init(row-2, col+2);
                    list[i] = current;
                    i++;
                }
                if (canJump(player, row, col, row-2, col-2)) {
                    struct coordinate* current = init(row-2, col-2);
                    list[i] = current;
                    i++;
                }
            }
        }
    }

    // possible moves
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++){
                if (board[row][col] == player) {
                    if (canMove(player, row, col, row+1, col+1)) {
                        struct coordinate* current = init(row+1, col+1);
                        list[i] = current;
                        i++;
                    }
                    if (canMove(player, row, col, row+1, col-1)) {
                        struct coordinate* current = init(row+1, col-1);
                        list[i] = current;
                        i++;
                    }
                    if (canMove(player, row, col, row-1, col+1)) {
                        struct coordinate* current = init(row-1, col+1);
                        list[i] = current;
                        i++;
                    }
                    if (canMove(player, row, col, row-1, col-1)) {
                        struct coordinate* current = init(row-1, col-1);
                        list[i] = current;
                        i++;
                    }
                }
            }
        }
    return list;
}
