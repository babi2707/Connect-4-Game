/***********************************************************   NAMES: Barbara
Luciano and Mai DATE: June 7, 2020 ASSIGNMENT: Game Design using Arrays
DESCRIPTION: Users can either play Connect 4 against another opponent or with a
computer CONCEPTS: Switch Statements, If Statements, Functions, Arrays, Strings,
2D String, Cfail, Random computer choice, Setw. FUNCTIONS: checker(char) returns
bool - checks if a player won getNum(int, int) returns int - gets an integer
from user within a range displayBoard(int) returns nothing - displays the
gameboard dropTheChip(char) - interprets the input to drop the chip
***********************************************************/

#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

//------ DECLARING GLOBAL VARIABLES ------
// variables for the board
const int columns = 7, rows = 6;
string board[columns][rows];
int height[columns]; // to check if the columns are filled

// holding info of the players
int numOfPlayers;
string winner;
string name[2];
char chip[2];

// variables to drop the chip
int x, y, full, columnChosen;
bool columnMaxed;

// variables for the computer
int computerChipRand;
char computerChip[5] = {'!', '@', '#', '$', '%'};

// variables for exit or continuing the game
int option;
bool win, correct, again;

// variables for winnings table
int wins[2], losses[2];

string scoop; // error handling
//------ END OF DECLARING VARIABLES ------

// functions
bool checker(char winSym);
int getNum(int min, int max);
void displayBoard(int loc);
bool dropTheChip(char symbol);

int main() {
	srand(time(NULL)); // prepping seed for randomizing
	// preparing the IDs
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			board[j][i] = " 1111 ";
		}
	}

	//------ THE FULL GAME ------
	do {
		// prepping the number of wins per player
		wins[0] = 0;
		wins[1] = 0;
		losses[0] = 0;
		losses[1] = 0;

		// intro
		cout << "------------------- CONNECT 4 -------------------\n\n";
		cout << "Welcome to Connect 4!\n";

		// instructions
		cout << "\nINFORMATION ABOUT THE GAME: " << endl;
		cout << "1- Choices: User have the option to choose\n"
			 << setw(11) << ""
			 << "- To play against the computer OR a person\n"
			 << setw(11) << ""
			 << "- Their name(s)\n"
			 << setw(11) << ""
			 << "- The character(s) to represents their chip(s)" << endl;
		cout << "2- Game: Choose where you want to drop your chip" << endl;
		cout << "3- Goal: Make a sequence in a row, column or diagonal with 4 "
				"of your chips to win!"
			 << endl
			 << endl;
		cout << "START OF THE GAME:" << endl;

		//------ ASKING FOR NUMBER OF PLAYERS ------
		cout << "Do you want to play against another player or a "
				"computer?\n\nINPUT:\n\t- 1 if you want to play with the "
				"computer.\n\t- 2 if you want to play with another "
				"person.\nOPTION CHOSEN: ";
		numOfPlayers = getNum(1, 2);
		cout << endl;
		//------ END OF ASKING FOR NUMBER OF PLAYERS ------

		//------ INSERT PLAYER 1 VALUES ------
		// gets name of player 1
		cout << "Enter name of player 1: ";
		while (true) {
			getline(cin, name[0]);
			// error handling
			if (name[0] == "Computer" && numOfPlayers == 1) {
				cout << "INVALID NAME! Please try again:" << endl;
				continue;
			}
			break;
		}

		// gets character of player 1
		cout << "\nEnter character of player 1 (ex: X, O): ";
		while (true) {
			cin >> chip[0];
			getline(cin, scoop);
			// error handling
			if ((int)chip[0] < 33 || (int)chip[0] > 126 || scoop.length() > 0) {
				cout << "INVALID CHARACTER! Please try again:" << endl;
				continue;
			}
			break;
		}
		//------ END OF PLAYER 1 VALUES ------

		//------ INSERT PLAYER 2 VALUES ------
		if (numOfPlayers == 1) { // against the computer
			name[1] = "Computer";

			do { // getting character of player 2
				computerChipRand = rand() % 5;
				chip[1] = computerChip[computerChipRand];
			} while (chip[0] == chip[1]); // error handling
		} else if (numOfPlayers == 2) {   // against another person
			// gets name
			cout << "\nEnter name of player 2: ";
			while (true) {
				getline(cin, name[1]);
				if (name[1] == name[0]) { // error handling
					cout << "INVALID NAME! Please try again:" << endl;
					continue;
				}
				break;
			}

			// gets character
			cout << "\nEnter character of player 2: ";
			while (true) {
				cin >> chip[1];
				getline(cin, scoop);
				if ((int)chip[1] < 33 || (int)chip[1] > 126 ||
					scoop.length() > 0 ||
					chip[0] == chip[1]) { // error handling
					cout << "INVALID CHARACTER! Please try again:" << endl;
					continue;
				}
				break;
			}
		}
		//------ END OF PLAYER 2 VALUES ------

		//------ THE INDIVIDUAL GAME ------
		do {
			//------ PREPARING THE GAME ------

			// preparing the IDs
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					board[j][i] = " 1111 ";
				}
			}

			full = 0; // to check if the board is filled

			// resetting heights of the column
			for (int b = 0; b < columns; b++) {
				height[b] = 0;
			}

			//------ END OF PREPARING THE GAME ------

			//------ THE TURNS ------
			do {
				// display board
				system("clear");
				displayBoard(0);

				// get the column of player 1
				cout << endl
					 << name[0] << ':' << endl
					 << "Which column do you want to drop your chip in: "
					 << endl;
				do {
					columnChosen = getNum(1, 7);
					columnMaxed = dropTheChip(chip[0]); // check if they won
				} while (columnMaxed == true);			// error handling

				// if win is true here, player 1 won
				if (win == true) {
					winner = name[0];
					wins[0]++;
					losses[1]++;
				}

				// get the column of player 2
				if (win == false) {
					if (numOfPlayers == 1) {
						do {
							columnChosen = rand() % 7 + 1;
							columnMaxed = dropTheChip(chip[1]);
						} while (columnMaxed == true);
					} else {
						system("clear");
						displayBoard(0);

						cout
							<< endl
							<< name[1] << ':' << endl
							<< "Which column do you want to drop your chip in: "
							<< endl;
						do {
							columnChosen = getNum(1, 7);
							columnMaxed = dropTheChip(chip[1]);
						} while (columnMaxed == true);
					}

					// if win is true here, player 2 won
					if (win == true) {
						winner = name[1];
						wins[1]++;
						losses[0]++;
					}
				}
			} while (win == false && full != 42);

			if (full == 42) {
				winner = "tie";
			}
			//------ END OF THE TURNS ------

			system("clear");
			cout << "The map:" << endl;
			displayBoard(0);
			cout << endl;

			// only show if someone won
			cout << "The in-a-row:" << endl;
			displayBoard(5);
			cout << endl;

			// displaying who won
			if (winner != "tie") {
				cout << winner << " WON!" << endl << endl;
			} else {
				cout << "TIE!" << endl << endl;
			}

			//------ ASKING TO REPEAT THE GAME ------
			cout << "Do you want to play again against the same opponent?"
				 << endl;
			cout << "1 = yes" << endl;
			cout << "2 = no" << endl;
			option = getNum(1, 2);

			// input interpretation
			switch (option) {
			case 1:
				again = true;
				break;
			case 2:
				cout << setw(8) << "" << name[0] << endl;
				cout << setw(8) << "Wins: " << wins[0] << endl;
				cout << setw(8) << "Losses: " << losses[0] << endl << endl;
				cout << setw(8) << "" << name[1] << endl;
				cout << setw(8) << "Wins: " << wins[1] << endl;
				cout << setw(8) << "Losses: " << losses[1] << endl;

				if (wins[0] == wins[1]) {
					cout << "\n\t\tTIE!\n";
				} else if (wins[0] > wins[1]) {
					cout << "\n\n\t\t" << name[0] << " IS THE WINNER!\n";
				} else if (wins[0] < wins[1]) {
					cout << "\n\n\t\t" << name[1] << " IS THE WINNER!\n";
				}
				again = false;
				break;
			}
			//------ END OF ASKING TO REPEAT THE GAME ------
		} while (again == true);
		//------END OF THE INDIVIDUAL GAME ------

		//------ ASKING TO REPEAT THE GAME ------
		cout << endl << "Do you want to Connect 4 again?" << endl;
		cout << "1 = yes" << endl;
		cout << "2 = no" << endl;
		option = getNum(1, 2);

		// input interpretation
		switch (option) {
		case 1:
			system("clear");
			again = true;
			break;
		case 2:
			cout << endl
				 << "Thank you for playing our Connect 4 game.\nHope you "
					"enjoyed it. See you next time!"
				 << endl;
			again = false;
			break;
		}
		//------ END OF ASKING TO REPEAT THE GAME ------

	} while (again == true); // repeats the whole game
							 //------ END OF THE FULL GAME ------
}

// function to check for the Connect 4 (more info about the algorithm's workings
// in the planning document)
bool checker(char winSym) {
	// declaring variables
	int rowSum;
	int xRestr, yRestr, xMove, yMove, loc;
	char compareDrop, compareCheck;
	bool win = false;

	// checking IDs of neighbouring chips and changing
	// the main chip's ID
	for (int i = 1; i <= 8; i++) {
		switch (i) { // checking which chip to compare
		case 1:		 // H1
			xRestr = 0;
			yRestr = -1;
			xMove = -1;
			yMove = 0;
			break;
		case 2: // L1
			xRestr = 0;
			yRestr = rows - 1;
			xMove = -1;
			yMove = 1;
			break;
		case 3: // V1
			xRestr = -1;
			yRestr = rows - 1;
			xMove = 0;
			yMove = 1;
			break;
		case 4: // R1
			xRestr = columns - 1;
			yRestr = rows - 1;
			xMove = 1;
			yMove = 1;
			break;
		case 5: // H2
			xRestr = columns - 1;
			yRestr = -1;
			xMove = 1;
			yMove = 0;
			break;
		case 6: // L2
			xRestr = columns - 1;
			yRestr = 0;
			xMove = 1;
			yMove = -1;
			break;
		case 7: // V2
			xRestr = -1;
			yRestr = 0;
			xMove = 0;
			yMove = -1;
			break;
		case 8: // R2
			xRestr = 0;
			yRestr = 0;
			xMove = -1;
			yMove = -1;
			break;
		default:
			cout << "exit" << endl;
			break;
		}

		// setting the digit of the ID to correspond with
		// the compared chip
		loc = i;
		if (i == 5) {
			loc = 1;
		}
		if (i == 6) {
			loc = 2;
		}
		if (i == 7) {
			loc = 3;
		}
		if (i == 8) {
			loc = 4;
		}

		// changing the ID of the main chip
		if (x != xRestr && y != yRestr &&
			(board[x][y].at(0) == board[x + xMove][y + yMove].at(0))) {
			// setting new digits for the IDs
			compareDrop = board[x][y].at(loc);
			compareCheck = board[x + xMove][y + yMove].at(loc);
			rowSum = (int)compareDrop - 48 + (int)compareCheck - 48;

			if (rowSum >= 4) {
				win = true;
			}

			// changing the ID of neighbouring chips and main chip
			for (int n = 0; n <= (int)compareCheck - 48; n++) {
				board[x + (n * xMove)][y + (n * yMove)].at(loc) =
					('0' + rowSum);
				if (rowSum >= 4) {
					board[x + (n * xMove)][y + (n * yMove)].at(5) = winSym;
				}
			}
			for (int n = 0; n < (int)compareDrop - 48; n++) {
				board[x - (n * xMove)][y - (n * yMove)].at(loc) =
					('0' + rowSum);
				if (rowSum >= 4) {
					board[x - (n * xMove)][y - (n * yMove)].at(5) = winSym;
				}
			}
		}
	}

	return win;
}

// this function makes it easier to input numbers
int getNum(int min, int max) {
	int num;

	while (true) {
		cin >> num;
		if (cin.fail() || num < min || num > max) { // error handling
			cin.clear();
			cin.ignore(100, '\n');
			cout << "INVALID INPUT! Please try again: ";
			continue;
		}
		cin.ignore(100, '\n');
		break;
	}
	return num;
}

// displays the board, loc is the character number of the ID
void displayBoard(int loc) {
	for (int i = rows - 1; i >= 0; i--) { // goes row by row
		cout << '|';
		for (int j = 0; j < columns; j++) { // goes column by column
			cout << board[j][i].at(loc) << '|';
		}
		cout << endl;
	}

	// display labels at the bottom
	cout << ' ';
	for (int c = 1; c <= 7; c++) {
		cout << c << ' ';
	}
	cout << endl;
}

// gives the entered chip a coordinate and error handling
bool dropTheChip(char symbol) {
	bool max;

	// give coordinates to chip
	x = columnChosen - 1;
	y = height[x];

	if (y > 6) { // if column is filled
		max = true;
		cout << "COLUMN IS FULL! Please try again:" << endl;
	} else {
		max = false;
		height[x]++;
		full++;
		board[x][y].at(0) = symbol;

		win = checker(symbol); // checks if player won
	}

	return max;
}