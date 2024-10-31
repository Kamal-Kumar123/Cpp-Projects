#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 10; // Width of the grid
const int HEIGHT = 10; // Height of the grid
const int MINES = 10; // Number of mines

// Function to initialize the game board
void initializeBoard(vector<vector<char>>& board, vector<vector<int>>& mineBoard) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = ' '; // Unrevealed cell
            mineBoard[i][j] = 0; // Initialize mine counts to 0
        }
    }

    // Place mines randomly on the board
    srand(time(0)); // Seed the random number generator
    for (int i = 0; i < MINES; ) {
        int x = rand() % HEIGHT; // Random row
        int y = rand() % WIDTH;  // Random column
        if (mineBoard[x][y] == 0) { // Check if there's no mine already
            mineBoard[x][y] = -1; // Place a mine
            i++;
            // Update adjacent mine counts
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (x + dx >= 0 && x + dx < HEIGHT && y + dy >= 0 && y + dy < WIDTH && mineBoard[x + dx][y + dy] != -1) {
                        mineBoard[x + dx][y + dy]++; // Increment adjacent mine count
                    }
                }
                
            }
            
        }
        
    }
    // Debugging: Print the mine positions
cout << "Mine Positions (for debugging):" << endl;
for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
        if (mineBoard[i][j] == -1) {
            cout << "* "; // Display mine as '*'
        } else {
            cout << ". "; // Display non-mine cells as '.'
        }
    }
    cout << endl;
}

}

// Function to print the game board
void printBoard(const vector<vector<char>>& board) {
    cout << "   ";
    for (int i = 0; i < WIDTH; i++) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        cout << i << " | ";
        for (int j = 0; j < WIDTH; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to reveal a cell
bool revealCell(vector<vector<char>>& board, const vector<vector<int>>& mineBoard, int x, int y) {
    if (x < 0 || x >= HEIGHT || y < 0 || y >= WIDTH || board[x][y] != ' ') {
        return false; // Out of bounds or already revealed
    }

    board[x][y] = mineBoard[x][y] + '0'; // Convert mine count to char
    if (mineBoard[x][y] == 0) { // If no adjacent mines, reveal surrounding cells
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx != 0 || dy != 0) {
                    revealCell(board, mineBoard, x + dx, y + dy);
                }
            }
        }
    }
    return true;
}

// Function to flag a cell as a mine
void flagCell(vector<vector<char>>& board, int x, int y) {
    if (board[x][y] == ' ') {
        board[x][y] = 'F'; // Mark as flagged
    } else if (board[x][y] == 'F') {
        board[x][y] = ' '; // Unflag
    }
}

// Function to check for win condition
bool checkWin(const vector<vector<char>>& board, const vector<vector<int>>& mineBoard) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (mineBoard[i][j] != -1 && board[i][j] == ' ') {
                return false; // Found an unrevealed cell that isn't a mine
            }
        }
    }
    return true; // All non-mine cells revealed
}

// Function to print the final board with mines revealed
void printFinalBoard(const vector<vector<int>>& mineBoard) {
    cout << "Final Board:" << endl;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (mineBoard[i][j] == -1) {
                cout << "* "; // Display mine as '*'
            } else {
                cout << mineBoard[i][j] << " "; // Display mine count
            }
        }
        cout << endl;
    }
}

// Main function
int main() {
    vector<vector<char>> board(HEIGHT, vector<char>(WIDTH)); // Game board for player
    vector<vector<int>> mineBoard(HEIGHT, vector<int>(WIDTH)); // Board with mine counts

    initializeBoard(board, mineBoard); // Initialize the game

    cout << "Welcome to Minesweeper!" << endl;
    cout << "Instructions: " << endl;
    cout << "1. Enter the row and column to reveal a cell (e.g., '1 2')." << endl;
    cout << "2. Enter 'f <row> <col>' to flag a suspected mine." << endl;
    cout << "3. Try to uncover all safe cells without hitting a mine!" << endl;

    bool gameOver = false;
    while (!gameOver) {
        printBoard(board); // Display the current game board
        string command;
        cout << "Enter your move: ";
        getline(cin, command); // Read the entire line of input

        if (command.substr(0, 2) == "f ") { // Check if the command is for flagging
            int x, y;
            sscanf(command.c_str() + 2, "%d %d", &x, &y); // Read coordinates
            if (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH) {
                flagCell(board, x, y); // Flag or unflag the cell
            } else {
                cout << "Invalid coordinates! Please try again." << endl;
            }
        } else { // Otherwise, it's a reveal command
            int x, y;
            sscanf(command.c_str(), "%d %d", &x, &y); // Read coordinates

            if (x < 0 || x >= HEIGHT || y < 0 || y >= WIDTH) {
                cout << "Invalid coordinates! Please try again." << endl;
                printBoard(board); // Show the board state after invalid input
                continue; // Skip the rest of the loop if invalid
            }

            if (mineBoard[x][y] == -1) {
                cout << "Game Over! You hit a mine!" << endl; // Game over condition
                printFinalBoard(mineBoard); // Reveal the final board
                gameOver = true; // Set gameOver to true to exit the loop
            } else {
                revealCell(board, mineBoard, x, y); // Reveal the cell
                if (checkWin(board, mineBoard)) {
                    cout << "Congratulations! You've cleared the minefield!" << endl;
                    printFinalBoard(mineBoard); // Reveal the final board
                    gameOver = true; // Set gameOver to true to exit the loop
                }
            }
        }
    }

    return 0; // Exit the program
}