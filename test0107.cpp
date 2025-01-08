#include <iostream>
#include <vector>
#include <conio.h> // For _getch()
#include <windows.h> // For SetConsoleTextAttribute()

using namespace std;


#define SIZE 4 //int SIZE


// Colors
const int DEFAULT_COLOR = 7;
const int GREEN_COLOR = 10;
const int RED_COLOR = 12;
const int HIGHLIGHT_COLOR = 11;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool isBoardValidAndComplete(const vector<vector<int>>& board) {
    for (int i = 0; i < SIZE; i++) {
        vector<bool> rowCheck(SIZE + 1, false);
        vector<bool> colCheck(SIZE + 1, false);
        for (int j = 0; j < SIZE; j++) {
            // Row validation
            if (board[i][j] == 0 || rowCheck[board[i][j]]) return false;
            rowCheck[board[i][j]] = true;
            // Column validation
            if (board[j][i] == 0 || colCheck[board[j][i]]) return false;
            colCheck[board[j][i]] = true;
        }
    }
    return true;
}

void printBoard(const vector<vector<int>>& board, int cursorX, int cursorY) { //二維 
    system("cls");//初始化 清除 
    
    // Check rows and columns for validity
    vector<bool> rowValid(SIZE, true);
    vector<bool> colValid(SIZE, true);

    for (int i = 0; i < SIZE; i++) {
        vector<bool> rowCheck(SIZE + 1, false);
        vector<bool> colCheck(SIZE + 1, false); //預設沒有數字 

        for (int j = 0; j < SIZE; j++) {
            // Row check
            if (board[i][j] != 0) {
                if (rowCheck[board[i][j]]) rowValid[i] = false;
                rowCheck[board[i][j]] = true;
            }

            // Column check
            if (board[j][i] != 0) {
                if (colCheck[board[j][i]]) colValid[i] = false;
                colCheck[board[j][i]] = true;
            }
        }
    }

    // Helper function to check if a line is complete
    auto isComplete = [](const vector<int>& line) { //auto 確保int 
        for (int x : line) { //for迴圈:line
            if (x == 0) return false;
        }
        return true;
    };

    // Print instructions
    cout << "W/A/S/D: move cursor\n1-4: fill in number\n0: clear the cell\nQ: quit\n\n";

    // Print board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Set color for cells
            if (!rowValid[i] || !colValid[j]) {
                setColor(RED_COLOR);
            } else if (isComplete(board[i]) || isComplete(vector<int>{board[0][j], board[1][j], board[2][j], board[3][j]})) {
                setColor(GREEN_COLOR);
            } else {
                setColor(DEFAULT_COLOR);
            }

            if (i == cursorY && j == cursorX) {
                setColor(HIGHLIGHT_COLOR);
                cout << " [";
                if (board[i][j] == 0) cout << " ";
                else cout << board[i][j];
                cout << "] ";
                setColor(DEFAULT_COLOR);
            } else {
                cout << "  ";
                if (board[i][j] == 0) cout << ".";
                else cout << board[i][j];
                cout << "  ";
            }
        }
        cout << "\n";
    }

    // Check if the entire board is valid and complete
    if (isBoardValidAndComplete(board)) {
        setColor(GREEN_COLOR);
        cout << "\n通關!\n";
        setColor(DEFAULT_COLOR);
    }

    // Reset color
    setColor(DEFAULT_COLOR);
}

int main() {
    const vector<vector<int>> initialBoard = { //初始板板 
        {0, 0, 1, 0},
        {0, 4, 0, 0},
        {0, 0, 2, 0},
        {0, 1, 0, 0}
    };
	
    vector<vector<int>> board = initialBoard;
    int cursorX = 0, cursorY = 0;

    while (true) {
        printBoard(board, cursorX, cursorY);

        char input = _getch();  //類input 
        if (input == 'q' || input == 'Q') {
        	cout<<"3, 2, 1, 4\n1, 4, 3, 2\n4, 3, 2, 1\n2, 1, 4, 3"<<endl; //看答案 

        	break;
		}

        switch (input) {
            case 'w': case 'W':
                if (cursorY > 0) cursorY--;
                break;
            case 's': case 'S':
                if (cursorY < SIZE - 1) cursorY++;
                break;
            case 'a': case 'A':
                if (cursorX > 0) cursorX--;
                break;
            case 'd': case 'D':
                if (cursorX < SIZE - 1) cursorX++;
                break;
            case '1': case '2': case '3': case '4':
                if (initialBoard[cursorY][cursorX] == 0) // Prevent changing initial values
                    board[cursorY][cursorX] = input - '0';
                break;
            case '0':
                if (initialBoard[cursorY][cursorX] == 0) // Prevent clearing initial values
                    board[cursorY][cursorX] = 0;
                break;
            default:
                break;
        }
    }

    return 0;
}

