#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 5;
const int MINES = 5;

void generateMines(vector<vector<bool>>& mines) {
    int placed = 0;
    while (placed < MINES) {
        int r = rand() % SIZE;
        int c = rand() % SIZE;
        if (!mines[r][c]) {
            mines[r][c] = true;
            ++placed;
        }
    }
}

int countAdjacentMines(int r, int c, const vector<vector<bool>>& mines) {
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            int nr = r + dr;
            int nc = c + dc;
            if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE) {
                if (mines[nr][nc]) ++count;
            }
        }
    }
    return count;
}

void printBoard(const vector<vector<char>>& board) {
    cout << "   ";
    for (int j = 0; j < SIZE; ++j) cout << j << " ";
    cout << "\n";

    for (int i = 0; i < SIZE; ++i) {
        cout << i << "  ";
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    vector<vector<char>> board(SIZE, vector<char>(SIZE, '*'));
    vector<vector<bool>> mines(SIZE, vector<bool>(SIZE, false));

    generateMines(mines);

    int revealed = 0;
    const int totalToReveal = SIZE * SIZE - MINES;

    while (revealed < totalToReveal) {
        printBoard(board);
        int r, c;
        cout << "Enter row and column (0 to " << SIZE - 1 << "): ";
        cin >> r >> c;

        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) {
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (board[r][c] != '*') {
            cout << "Cell already revealed. Try again.\n";
            continue;
        }

        if (mines[r][c]) {
            cout << "BOOM! You hit a mine. Game Over.\n";
            // Show final mine layout
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    if (mines[i][j]) board[i][j] = 'M';
                }
            }
            printBoard(board);
            return 0;
        } else {
            int count = countAdjacentMines(r, c, mines);
            board[r][c] = count + '0';
            ++revealed;
        }
    }

    printBoard(board);
    cout << "Congratulations! You cleared the board!\n";
cout << "Press Enter to exit...";
cin.ignore();
cin.get();

    return 0;
}

