#ifndef EIGHTQUEENSSOLVER_H
#define EIGHTQUEENSSOLVER_H

#include <vector>
#include <string>

// Board size constant. (The lab references 8, but we avoid “magic numbers.”)
constexpr int BOARD_SIZE = 8;

/**
 * @class EightQueensSolver
 * @brief Solves the Eight Queens puzzle using recursion or a stack-based backtracking approach.
 *
 * Precondition: BOARD_SIZE is defined (8 by default).
 * Postcondition: The solver will find at least one valid arrangement of 8 queens on the board,
 *                or indicate no solution if it fails (should not happen for 8 queens).
 */
class EightQueensSolver {
private:
    // A 2D board representation: 0 means empty, 1 means a queen is placed.
    int board[BOARD_SIZE][BOARD_SIZE];

    /**
     * @brief Recursively attempts to place queens row by row.
     * @param row The current row to place a queen.
     * @return true if a full solution is found, false otherwise.
     *
     * Precondition: board has partial placements for rows < row.
     * Postcondition: If successful, the board will contain a valid arrangement of queens.
     */
    bool placeQueen(int row);

    /**
     * @brief Checks if placing a queen at (row, col) is safe (no conflicts).
     * @param row Row index.
     * @param col Column index.
     * @return true if safe, false otherwise.
     *
     * Precondition: board has partial placements up to the current row.
     * Postcondition: Does not modify the board; only checks for conflicts.
     */
    bool isSafe(int row, int col) const;

public:
    /**
     * @brief Constructor that initializes the board to empty (all zeros).
     */
    EightQueensSolver();

    /**
     * @brief Solves the Eight Queens puzzle and returns the board as a string.
     * @return A string showing the final arrangement of queens, or an error message.
     */
    std::string solve();

    /**
     * @brief Converts the internal board representation into a printable string.
     * @return A string that visually shows the board with 'Q' for queens and '.' for empty spaces.
     */
    std::string boardToString() const;
};

#endif // EIGHTQUEENSSOLVER_H
