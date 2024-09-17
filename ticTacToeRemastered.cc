// Tic Tac Toe with a twist, built from scratch with C++
// Supports as big a grid size as you'd like!

#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int gridSize;
int maxNumDigits;

void printStarterGrid() {
    ostringstream oss;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 1; j <= gridSize; j++) {
            oss << setw(maxNumDigits) << (gridSize * i + j);
            if (j != gridSize) {
                oss << " | ";
            }
        }
        oss << "\n";
        if (i != gridSize - 1) {
            for (int j = 0; j < gridSize - 1; j++) {
                oss << setfill('-') << setw(maxNumDigits) << "" << "-+-";
            }
            oss << setfill('-') << setw(maxNumDigits) << "" << "\n";
            oss << setfill(' ');
        }
    }
    cout << oss.str() << endl;
}

bool isBoardFull(const vector<vector<int>>& gameState) {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (gameState[i][j] == 0) return false;
        }
    }
    return true;
}

void printCurrentGrid(const vector<vector<int>>& gameState) {
    ostringstream oss;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            // loc is 0 for player 1, X for player 2. Otherwise, it's the number needed to fill the location
 			if (gameState[i][j] != 0) {
                // Print '0' or 'X'
                oss << setw(maxNumDigits) << (gameState[i][j] == 1 ? '0' : 'X');
            } 
			else {
                // Print cell number
                oss << setw(maxNumDigits) << (gridSize * i + j + 1);
            }
			if (j != gridSize - 1) {
                oss << " | ";
            }
        }
        oss << "\n";
        if (i != gridSize - 1) {
            for (int j = 0; j < gridSize - 1; j++) {
                oss << setfill('-') << setw(maxNumDigits) << "" << "-+-";
            }
            oss << setfill('-') << setw(maxNumDigits) << "" << "\n";
            oss << setfill(' ');
        }
    }
    cout << oss.str() << endl;
}

bool gameWonChecker(const vector<vector<int>>& gameState, int currentPlayer) {
    // Check rows and columns
    for (int i = 0; i < gridSize; i++) {
        if (all_of(gameState[i].begin(), gameState[i].end(), [currentPlayer](int cell) { return cell == currentPlayer; })) {
            return true;
        }
        bool columnWin = true;
        for (int j = 0; j < gridSize; j++) {
            if (gameState[j][i] != currentPlayer) {
                columnWin = false;
                break;
            }
        }
        if (columnWin) {
            return true;
        }
    }

    // Check diagonals
    bool diagonal1Win = true;
    bool diagonal2Win = true;
    for (int i = 0; i < gridSize; i++) {
        if (gameState[i][i] != currentPlayer) {
            diagonal1Win = false;
        }
        if (gameState[i][gridSize - 1 - i] != currentPlayer) {
            diagonal2Win = false;
        }
    }
    return diagonal1Win || diagonal2Win;
}

void ticTacToe() {
	cout << "Welcome to Tic-Tac-Toe! Player 1 will be 0, and Player 2 will be X." << endl;
    gridSize = 0;
    cout << "Please choose how big you would like your grid to be. For example, enter 3 to have a standard game of 3x3 tic-tac-toe. Please enter an integer greater than or equal to 3. Please also note that selecting a large number may result in the grid not fitting on the current screen." << endl;
    while (gridSize < 3) {
        cin >> gridSize;
        if (cin.fail() || gridSize < 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter an integer greater than or equal to 3." << endl;
        }
    }
    cout << "Starting grid will be displayed below. Enter the number corresponding to the grid location to put in a 0 or an X." << endl;
	cout << "To win, simply get " << gridSize << " of your respective symbols in a row!" << endl;
    maxNumDigits = to_string(gridSize * gridSize).length(); // Maximum number of digits in the largest number. Useful for formatting!
    printStarterGrid();
    vector<vector<int>> gameState(gridSize, vector<int>(gridSize, 0));
    int playerInput = 0;
    int currentPlayer = 1;
    bool gameWon = false;
    bool tieGame = false;

    while (!gameWon) {
        cout << "Player " << currentPlayer << "'s turn." << endl;
        cout << "Enter a number between 1 and " << (gridSize * gridSize) << ", inclusive, that has not been claimed already: " << endl;

        cin >> playerInput;
        if (cin.fail()) {
            if (cin.eof()) {
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again, Player " << currentPlayer << endl;
        } else if (playerInput > gridSize * gridSize || playerInput < 1) {
            cout << "Please input a number between 1 and " << (gridSize * gridSize) << ", inclusive." << endl;
            playerInput = 0;
        } else if (isBoardFull(gameState)) {
            tieGame = true;
        } else {
            // Convert player input to 2D index and check if cell is occupied
            int row = (playerInput - 1) / gridSize;
            int col = (playerInput - 1) % gridSize;

            if (gameState[row][col] != 0) {
                cout << "Cell already occupied. See the grid below.\n";
                printCurrentGrid(gameState);
                playerInput = 0;
            } else {
                gameState[row][col] = currentPlayer;
                printCurrentGrid(gameState);
                gameWon = gameWonChecker(gameState, currentPlayer);
                if (!gameWon) {
                    currentPlayer = (currentPlayer == 1 ? 2 : 1);
                }
            }
        }
    }

    if (cin.eof()) {
        cout << "Program terminated. Have a nice day!" << endl;
    } else if (tieGame) {
        cout << "Tie game! Thanks for playing!" << endl;
    } else {
        cout << "Player " << currentPlayer << " wins!" << endl;
    }
}

int main() {
    ticTacToe();
	while (true)
	{
		char playAgain;
        cout << "Do you want to play again? (y/n): ";  
	    cin >> playAgain;
		if (playAgain == 'y' || playAgain == 'Y') {
			ticTacToe();
		}
		else {
			cout << "Thanks for playing!" << endl;
			break;
		}
	}
}
