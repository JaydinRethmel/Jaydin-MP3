// Title - Tic Tac D'Oh
// Author - Jaydin Rethmel
// Date Created - 4 / 29 / 2024
// Description - This program allows two people to play the game of tic-tac-toe against one another
// This program alternates which player goes at a time with one player (The First) always being an Xs and
// The other player always being Os. The program then displays the resulting gameboard and the taken positions
// by the other players. After a game comes to an end a point is added to the winning players score or if a tie 
// happens then it is counted seperately.
#include <iostream>
using namespace std;

int getPlayerInput(string playerName);
bool isLegalMove(char board[], int location);
void placeMarkOnBoard(char board[], char playerMark, int location);
void clearBoard(char board[]);
bool hasThreeInRow(char board[], char playerMark);
bool isTie(char board[]);
void displayBoard(char board[]);
void displayGameStats(int ties, int player1Score, int player2Score);

// Global Variables
const int BOARD_SIZE = 9;

int main() {
	// This section of text is the intialzation of all the main varibles including
	// player names, the size of the board, scores and ties, if players would like to play 
	// again as well as the bool variable which keeps track of whos turn is whos.
	string playerOneName = "";
	string playerTwoName = "";
	char board[BOARD_SIZE] = { '1','2','3','4','5','6','7','8','9' };
	int ties = 0;
	int playerOneScore = 0;
	int playerTwoScore = 0;
	char playAgain = 'y';
	int location = 0;
	bool isPlayerOneFirst = true;

	// Get Player's Names
	cout << "Player 1, enter your name here: ";
	cin >> playerOneName;
	cout << "Player 2, enter your name here: ";
	cin >> playerTwoName;


	do {
		bool isPlayerOnesTurn = isPlayerOneFirst;

		// This portion of the code is the where we have the players do there turn, if they 
		do {
			displayBoard(board);

			// Player 1
			if (isPlayerOnesTurn) {
				do {
					location = getPlayerInput(playerOneName);
					if (!isLegalMove(board, location)) cout << "Illegal Turn, Please go again: \n";
				} while (!isLegalMove(board, location));
				placeMarkOnBoard(board, 'X', location);
			}

			// Player 2
			else {
				do {
					location = getPlayerInput(playerTwoName);
					if (!isLegalMove(board, location)) cout << "Illegal Turn, Please go again: \n";
				} while (!isLegalMove(board, location));
				placeMarkOnBoard(board, 'O', location);
			}
			isPlayerOnesTurn = !isPlayerOnesTurn;
		} while (!hasThreeInRow(board, 'X') && !hasThreeInRow(board, 'O') && !isTie(board));

		displayBoard(board);

		// After detecting any win condition, this section checks to see if player One has won
		if (hasThreeInRow(board, 'X')) {
			cout << playerOneName << " has won this game!\n";
			playerOneScore++;
		}

		// After detecting any win condition, this section checks to see if player Two has won
		else if (hasThreeInRow(board, 'O')) {
			cout << playerTwoName << " has won this game!\n";
			playerTwoScore++;
		}

		// After detecting any win condition, this section checks to see if a tie has occured
		else if (isTie(board)) {
			cout << "The game is a tie!\n";
			ties++;
		}

		// End of Game 
		clearBoard(board);
		displayGameStats(ties, playerOneScore, playerTwoScore);
		cout << "\nWould you like to play again? (y/n): ";
		cin >> playAgain;
		isPlayerOneFirst = !isPlayerOneFirst;
	} while (playAgain == 'y');
}

// Gets the user location by prompting them to input a location, we then check to see if the input
// is not an integer, then it checks to see if it is with in the range of 1-9 and if not it fails.
int getPlayerInput(string playerName) {
	int input;
	while (true) {
		cout << "\033[0m" << playerName << ", enter where you'd like to place your mark (1-9): ";
		cin >> input;

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\033[31mERROR: Input must be an integer 1-9!\n";
		}

		else if (!(input > 0 && input < 10)) {
			cout << "\033[31mERROR: Input must be an integer 1-9!\n";
		}

		// Subtract 1 from input to convert from 1-9 input to 0-8 array index
		else return input - 1;
	}
}

// Returns true if the indicated location on the board yet not yet been played, false otherwise.
bool isLegalMove(char board[], int location) {
	if (board[location] == 'X' || board[location] == 'O') return false;
	else return true;
}

// Places the indicated mark at the specified board location; routine assumes that this is a legal placement. 
void placeMarkOnBoard(char board[], char playerMark, int location) {
	board[location] = playerMark;
}

// Restores the tic-tac-toe board to its original (i.e., with no crosses or circles being marked) configuration. 
void clearBoard(char board[]) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		board[i] = '1' + i;
	}
}

// Returns true if, for the specified mark, the board has the equivalent of three of those marks in a row, either
// vertically, horizontally, or diagonally.
bool hasThreeInRow(char board[], char playerMark) {
	// Check rows for three in a row
	for (int i = 0; i < BOARD_SIZE; i = i + 3) {
		if (board[i] == playerMark && board[i + 1] == playerMark && board[i + 2] == playerMark) return true;
	}

	// Check columns for three in a row
	for (int i = 0; i < (BOARD_SIZE / 3); i++) {
		if (board[i] == playerMark && board[i + 3] == playerMark && board[i + 6] == playerMark) return true;
	}

	// Check for diagonals
	if (board[0] == playerMark && board[4] == playerMark && board[8] == playerMark) return true;
	if (board[2] == playerMark && board[4] == playerMark && board[6] == playerMark) return true;
	return false;
}

// Checks all values in board for Xs and Os. If there are all Xs and Os, then returns true.
// board[] The array of the Tic-Tac-Toe board. False is returned if there are still
// any numbers, which are playable spaces.
bool isTie(char board[]) {
	// False is returned if there are still any numbers, which are playable spaces.
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (board[i] != 'X' && board[i] != 'O') {
			return false;
		}
	}

	return true;
}

// Prints out the current board; the board display must be as shown above.
void displayBoard(char board[]) {
	cout << "\n " << board[6] << " | " << board[7] << " | " << board[8]
		<< "\n---+---+---"
		<< "\n " << board[3] << " | " << board[4] << " | " << board[5]
		<< "\n---+---+---"
		<< "\n " << board[0] << " | " << board[1] << " | " << board[2] << "\n\n";
}

// Prints out the “stats” for all the games: number of games tied, number of games player 1 won, and number of
// games player 2 won.
void displayGameStats(int ties, int player1Score, int player2Score) {
	cout << "--- GAME STATS ---\n"
		<< "Player 1: " << player1Score << " wins\n"
		<< "Player 2: " << player2Score << " wins\n"
		<< ties << " ties\n"
		<< "------------------";
}