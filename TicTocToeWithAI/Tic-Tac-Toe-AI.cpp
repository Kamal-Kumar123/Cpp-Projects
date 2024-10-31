#include <iostream>
#include <limits.h>

using namespace std;

const char PLAYER = 'X';  // Human player
const char AI = 'O';      // Computer player
const char EMPTY = ' ';

// Function to print the Tic-Tac-Toe board
void printBoard(char board[3][3]) {
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

// Function to check if there are any moves left on the board
bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY)
                return true;
        }
    }
    return false;
}

// Function to evaluate the current board state
int evaluate(char board[3][3]) {
    // Checking for rows for X or O victory
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == PLAYER)
                return +10;
            else if (board[row][0] == AI)
                return -10;
        }
    }

    // Checking for columns for X or O victory
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == PLAYER)
                return +10;
            else if (board[0][col] == AI)
                return -10;
        }
    }

    // Checking for diagonals for X or O victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == PLAYER)
            return +10;
        else if (board[0][0] == AI)
            return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == PLAYER)
            return +10;
        else if (board[0][2] == AI)
            return -10;
    }

    // No winner yet
    return 0;
}

// Minimax algorithm to calculate the best move
int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);

    // If AI has won the game
    if (score == -10)
        return score;

    // If player has won the game
    if (score == 10)
        return score;

    // If no more moves and no winner
    if (!isMovesLeft(board))
        return 0;

    // If it's the maximizer's move (human player)
    if (isMax) {
        int best = -INT_MAX;

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (board[i][j] == EMPTY) {
                    // Make the move
                    board[i][j] = PLAYER;

                    // Call minimax recursively and choose the maximum value
                    best = max(best, minimax(board, depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
    // If it's the minimizer's move (AI player)
    else {
        int best = INT_MAX;

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (board[i][j] == EMPTY) {
                    // Make the move
                    board[i][j] = AI;

                    // Call minimax recursively and choose the minimum value
                    best = min(best, minimax(board, depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

// Function to find the best move for AI
pair<int, int> findBestMove(char board[3][3]) {
    int bestVal = INT_MAX;
    pair<int, int> bestMove = {-1, -1};

    // Traverse all cells, evaluate minimax function for all empty cells
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Check if cell is empty
            if (board[i][j] == EMPTY) {
                // Make the move
                board[i][j] = AI;

                // Compute evaluation function for this move
                int moveVal = minimax(board, 0, true);

                // Undo the move
                board[i][j] = EMPTY;

                // If the value of the current move is better than the best value, update best move
                if (moveVal < bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

// Function to check if there's a winner
bool checkWinner(char board[3][3]) {
    int score = evaluate(board);
    if (score == 10) {
        cout << "Player (X) wins!\n";
        return true;
    } else if (score == -10) {
        cout << "AI (O) wins!\n";
        return true;
    } else if (!isMovesLeft(board)) {
        cout << "It's a draw!\n";
        return true;
    }
    return false;
}

int main() {
    char board[3][3] = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };

    printBoard(board);

    while (true) {
        int x, y;
        cout << "Enter your move (row and column): ";
        cin >> x >> y;

        // Player move
        if (board[x][y] == EMPTY) {
            board[x][y] = PLAYER;
            printBoard(board);

            // Check if player won
            if (checkWinner(board))
                break;

            // AI move
            pair<int, int> bestMove = findBestMove(board);
            board[bestMove.first][bestMove.second] = AI;
            cout << "AI made its move:\n";
            printBoard(board);

            // Check if AI won
            if (checkWinner(board))
                break;
        } else {
            cout << "Invalid move! Try again.\n";
        }
    }

    return 0;
}