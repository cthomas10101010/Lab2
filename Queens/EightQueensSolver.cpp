#include "EightQueensSolver.h"
#include <sstream>   // for std::ostringstream

EightQueensSolver::EightQueensSolver() {
    // Initialize the board to 0 (empty).
    for(int r = 0; r < BOARD_SIZE; ++r) {
        for(int c = 0; c < BOARD_SIZE; ++c) {
            board[r][c] = 0;
        }
    }
}

bool EightQueensSolver::isSafe(int row, int col) const {
    // Check column conflicts above current row.
    for(int r = 0; r < row; ++r) {
        if(board[r][col] == 1) {
            return false;
        }
    }

    // Check upper-left diagonal conflicts.
    for(int r = row, c = col; r >= 0 && c >= 0; --r, --c) {
        if(board[r][c] == 1) {
            return false;
        }
    }

    // Check upper-right diagonal conflicts.
    for(int r = row, c = col; r >= 0 && c < BOARD_SIZE; --r, ++c) {
        if(board[r][c] == 1) {
            return false;
        }
    }

    return true; // If no conflicts, it's safe to place a queen.
}

bool EightQueensSolver::placeQueen(int row) {
    // Base case: if row == BOARD_SIZE, we placed queens in all rows successfully.
    if(row == BOARD_SIZE) {
        return true;
    }

    // Try each column in this row.
    for(int col = 0; col < BOARD_SIZE; ++col) {
        if(isSafe(row, col)) {
            // Place a queen here.
            board[row][col] = 1;

            // Recursively place the rest.
            if(placeQueen(row + 1)) {
                return true; // If successful, we’re done.
            }
            // Otherwise, backtrack.
            board[row][col] = 0;
        }
    }

    // If no column worked, return false to trigger backtracking.
    return false;
}

std::string EightQueensSolver::solve() {
    // Initiate the recursive backtracking from row 0.
    bool solved = placeQueen(0);
    if(solved) {
        return boardToString();
    } else {
        return "No solution found (unexpected for an 8x8 board).";
    }
}

std::string EightQueensSolver::boardToString() const {
    std::ostringstream oss;
    for(int r = 0; r < BOARD_SIZE; ++r) {
        for(int c = 0; c < BOARD_SIZE; ++c) {
            oss << (board[r][c] == 1 ? 'Q' : '.');
            if(c < BOARD_SIZE - 1) oss << " ";
        }
        oss << "\n";
    }
    return oss.str();
}
