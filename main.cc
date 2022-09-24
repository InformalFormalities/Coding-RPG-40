//Partners: Declan Doss, Vahan [last name], Khushkaranpreet Grewal, Andrew [last name]
//Bullet Points: Declan (), Vahan (), Khush (), Andrew ()
//Extra Credit: Khush (Cover art/music), [Name] (Inventory system)
//URL to Cover art and music:

#include <iostream>
#include <unistd.h>
#include "/public/colors.h"
using namespace std;

//Global vector. Any function can access it.
//Current: 200 x 40 map. TODO: Change/fill in later; make lore friendly.
vector<string> worldMap = { //For every extra special character (i.e. \, ", ') to make it appear on screen, you must add that many spaces.
	"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *",
	"*                                                                                  _/              /                                                                                                        *",
	"*             /\\         /\\                                                       /               |                                                                                                         *",
	"*            /  \\       /  \\                                                    _/               /                                                                                                          *",
	"*            |/\\|       |/\\|                                                   /                /                                                                                                           *",
	"*            |--|       |--|                                               ___/               /                                                                                                             *",
	"*       /----|  |-------|  |----\\                                       __/                  |                                                                                                              *",
	"*       |                       |                                      /                    /                                                                                                               *",
	"*       |                       |                                    _/                    /                                                                                                                *",
	"*       |          __           |                                  _/                     |                                                                                                                 *",
	"*       |         /  \\          |                                /                      _/                                                                                                                  *",
	"*       |         |  |          |                                |                     |                                                                                                                    *",
	"*       -------------------------                             = = = = = = = = = = = = = = =                                                                                                                 *",
	"*                ^    ^                                      |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|                                                                                                                *",
	"*                ^    ^                                     /                               \\                                                                                                               *",
	"*                ^     ^                                   /                                 \\                                                                                                              *",
	"*                 ^      ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^    = = = = = = = = = = = = = = =    ^ ^ ^ ^ ^ ^ ^                                                                                                *",
	"*                  ^                                         |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|                 ^                                                                                              *",
	"*                   ^                                       /   |                     |     \\                 ^                                                                                             *",
	"*                     ^                                    /    |         R            |     \\                  ^                                                                                           *",
	"*                       ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^     |         I             |       ^ ^ ^ ^ ^          ^                                                                                        *",
	"*                                                               |         V              |                ^          ^                                                                                      *",
	"*                                                                |        E               |                ^           ^ ^ ^ ^ ^                                                                            *",
	"*                                                                 |       R                |                 ^                   ^                                                                          *",
	"*                                                                 |                        |                   ^                   ^                                                                        *",
	"*                                                                  |                       |                     ^                   ^                                                                      *",
	"*                                                                   |                       |                      ^ ^ ^ ^             ^ ^                                                  ""Help me!""        *",
	"*                                                                    |                       |                             ^               ^                                                   __           *",
	"*                                                                     |                       |                              ^               ^                                                /  \\          *",
	"*                                                                    |                         |                               ^               ^ ^ ^ ^ ^                                     /    \\         *",
	"*                                                                   |                          |                                 ^ ^ ^                   ^                                  /  /\\  \\        *",
	"*                                                                   |                          |                                      ^                    ^                               /  /  \\  \\       *",
	"*                                                                   |                          |                                        ^                    ^                            /  |    |  \\      *",
	"*                                                                   |                          |                                          ^ ^ ^ ^ ^ ^         ^                           |  |____|  |      *",
	"*                                                                  |                          |                                                       ^        ^                          |          |      *",
	"*                                                                 |                          |                                                         ^       ^                          |          |      *",
	"*   /\\                                                          |                          |                                                           ^        ^                         |          |      *",
	"*  /  \\                                                        |                          |                                                              ^        ^ ^ ^ ^                 |          |      *",
	"*  |  |                                                         |                          |                                                               ^               ^ ^ ^ ^ ^ ^ ^ ^|          |      *",
	"*  |__|                                                         |                          |                                                                 ^                            |          |      *",
	"*                                                              |                          |                                                                    ^                          |          |      *",
	"*                                                             |                          |                                                                       ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^|          |      *",
	"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *",
};

void Main_Menu();
void Draw_Map(int rowSize, int colSize, int playerPositionCol, int playerPositionRow);
void Update_Map();
void Puzzle_1();
void Puzzle_2();
void Puzzle_3();
void Puzzle_4();
void Puzzle_5();
void die();
void Utility_Back_To_Map();
void Utiliity_Exit();

//Prints initial menu screen.
void Main_Menu() {

	const auto [ROWS, COLS] = get_terminal_size();
	int x = COLS / 2;
	int y = ROWS / 2;

	clearscreen();

	movecursor(y, x - 9);
	//TODO: Change title and emoji.
	cout << "Welcome to the GAME!!!👀" << endl;

	movecursor(y + 3, x - 11);
	//TODO: Remove emoji if possible.
	cout << "Press 'p' to start the game😉" << endl;

	movecursor(y + 6, x - 10);
	cout << "Press 'q' to quit the game" << endl;

	set_cursor_mode(false);
	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();

		if (keyPress == 'p' or keyPress == 'P') {
			return;
		} else if (keyPress == 'q' or keyPress == 'Q') {
			set_cursor_mode(true);
			set_raw_mode(false);
			clearscreen();
			movecursor(0, 0);
			exit(0);
		}
	}
}

//Draws the map initially and when player moves.
void Draw_Map(int rowSize, int colSize, int playerPositionCol, int playerPositionRow) {
	clearscreen();

	//Keeps map in top left. TODO: Change 0 0 to whatever to have map in another spot.
	movecursor(0, 0);

	//FIXME: I want to access the char where the player's coordinates are so that if they're one of the building chars, we can stop them from going in. Basically a from-scratch clamp function that's supposed to be quicker.
	//NOTE FOR FIXME: If this code is uncommented, "int previousPlayerCol" and "int previousPlayerRow" needs to be passed in Draw_Map from Update_Map and included in the above Draw_Map function definition.
	/*	char temp = worldMap.at(playerPositionCol).at(playerPositionRow);
		cout << temp << " " << endl;
		if (temp == '/' or temp == '\\' or temp == '|' or temp == '-' or temp == '_' or temp == '=') {
			playerPositionRow = previousPlayerRow;
			playerPositionCol = previousPlayerCol;
		} */

//Prints map out. Repeats printing one row and all columns.
	for (size_t row = 0; row <= rowSize; row++) {
		for (size_t col = 0; col <= colSize; col++) {
			if (col == playerPositionCol and row == playerPositionRow) cout << "P"; //TODO: Change player icon.
			else cout << worldMap.at(row).at(col);
		}
		cout << endl;
	}
}

//Updates the values to pass to Draw_Map when player moves.
void Update_Map() {
	//Define how many rows/cols there are.
	const int rowSize = worldMap.size() - 1, colSize = worldMap.at(rowSize).size() - 1;
	//Spawns player at the catsle doors (19 x, 13 y).
	int currentPlayerCol = 19, currentPlayerRow = 13;
	int previousPlayerCol = currentPlayerCol, previousPlayerRow = currentPlayerRow;

	//Draw map initially.
	Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);

	//Continuously checks for user input.
	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();

		//If user wants to quit, breaks out and returns.
		if (keyPress == 'q' or keyPress == 'Q') break;
		else { //Else if user wants to move, change their current coordinates. For columns we change user position by 2 to make distances between x and y feel similar.
			if (keyPress == UP_ARROW) currentPlayerRow--;
			if (keyPress == DOWN_ARROW)	currentPlayerRow++;
			if (keyPress == LEFT_ARROW) currentPlayerCol -= 2;
			if (keyPress == RIGHT_ARROW) currentPlayerCol += 2;

			//Prevents player from going outside the map.
			currentPlayerCol = clamp(currentPlayerCol, 1, colSize - 1);
			currentPlayerRow = clamp(currentPlayerRow, 1, rowSize - 1);

			//Puzzle 1 call (for house in bottom left).
			//TODO: Make a function utility for the clearscreen, movecursor, set_cursor_mode, resetcolor, etc.
			if ((currentPlayerCol >= 4 and currentPlayerCol <= 7) and (currentPlayerRow >= 36 and currentPlayerRow <= 39)) {
				clearscreen();
				movecursor(0, 0);
				set_cursor_mode(true);
				resetcolor();
				set_raw_mode(false);
				Puzzle_1();
			}

			//If player position has moved, redraw map and update player position.
			if (previousPlayerCol != currentPlayerCol or previousPlayerRow != currentPlayerRow) {
				previousPlayerRow = currentPlayerRow;
				previousPlayerCol = currentPlayerCol;
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
		}
	}
}

//Basic arithmatic puzzle.
void Puzzle_1() {
	int puzzleAnswer = 18, userInput = 0;

	cout << "In an ancient wall drawing, you find images depicting a item appearing from the wall. This item seems to only be able to be accessed after solving a math problem. As you look around, hidden in a dark corner, a problem bleeds out, ""Solve the problem to pass the test: (5 * 2) (8 / 4) + 3 + 7 - 12"". What do you believe the answer to be?" << endl;
	cin >> userInput;

	if (userInput == 'q' or userInput == 'Q') {
		Utility_Back_To_Map();
		Update_Map();
	}

	while (userInput != puzzleAnswer) {
		cout << "You enter your answer and...nothing happens. It seems you were wrong. Thinking again, what do you believe the answer is?" << endl;
		cin >> userInput;
	}

	cout << "As you hear rock scraping against rock, it turns out your answer proved fruitful! Walking over and peering into the box turns up an old key. I wonder what that's used for..." << endl;

	Utility_Back_To_Map();
}

void Puzzle_2() {

}

void Puzzle_3() {

}

void Puzzle_4() {

}

void Puzzle_5() {

}

void die() {
	cout << "BAD INPUT!!" << endl;
	exit(1);
}

void Utility_Back_To_Map() {
	set_cursor_mode(false);
	set_raw_mode(true);
	resetcolor();
	clearscreen();
	movecursor(0, 0);
}

void Utility_Exit_Out() {
	set_cursor_mode(true);
	set_raw_mode(false);
	resetcolor();
	clearscreen();
	movecursor(0, 0);
}

//Main acts as a driver program.
int main() {

	// Calls Main_Menu function to print out the main menu so it's the first screen user sees.
	Main_Menu();

	//TODO: Need a function to be called to introduce user to the world. It will then throw the player out into the map.

	//Set cursor mode to false for it to not appear on screen, and call Update_Map to initially draw and then continuously redraw it.
	set_cursor_mode(false);
	Update_Map();

	//TODO: If statement for if user wants to go to inventory.

	//Clean up after yourself.
	Utility_Exit_Out();	
}

//Prints initial menu screen.
void Main_Menu() {

	const auto [ROWS, COLS] = get_terminal_size();
	int x = COLS / 2;
	int y = ROWS / 2;

	clearscreen();

	movecursor(y, x - 9);
	//TODO: Change title and emoji.
	cout << "Welcome to the GAME!!!👀" << endl;

	movecursor(y + 3, x - 11);
	//TODO: Remove emoji if possible.
	cout << "Press 'p' to start the game😉" << endl;

	movecursor(y + 6, x - 10);
	cout << "Press 'q' to quit the game" << endl;

	set_cursor_mode(false);
	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();

		if (keyPress == 'p' or keyPress == 'P') {
			return;
		} else if (keyPress == 'q' or keyPress == 'Q') {
			set_cursor_mode(true);
			set_raw_mode(false);
			clearscreen();
			movecursor(0, 0);
			exit(0);
		}
	}
}

//Draws the map initially and when player moves.
void Draw_Map(int rowSize, int colSize, int playerPositionCol, int playerPositionRow) {
	clearscreen();

	//Keeps map in top left. TODO: Change 0 0 to whatever to have map in another spot.
	movecursor(0, 0);

	//FIXME: I want to access the char where the player's coordinates are so that if they're one of the building chars, we can stop them from going in. Basically a from-scratch clamp function that's supposed to be quicker.
	//NOTE FOR FIXME: If this code is uncommented, "int previousPlayerCol" and "int previousPlayerRow" needs to be passed in Draw_Map from Update_Map and included in the above Draw_Map function definition.
	/*	char temp = worldMap.at(playerPositionCol).at(playerPositionRow);
		cout << temp << " " << endl;
		if (temp == '/' or temp == '\\' or temp == '|' or temp == '-' or temp == '_' or temp == '=') {
			playerPositionRow = previousPlayerRow;
			playerPositionCol = previousPlayerCol;
		} */

//Prints map out. Repeats printing one row and all columns.
	for (size_t row = 0; row <= rowSize; row++) {
		for (size_t col = 0; col <= colSize; col++) {
			if (col == playerPositionCol and row == playerPositionRow) cout << "P"; //TODO: Change player icon.
			else cout << worldMap.at(row).at(col);
		}
		cout << endl;
	}
}

//Updates the values to pass to Draw_Map when player moves.
void Update_Map() {
	//Define how many rows/cols there are.
	const int rowSize = worldMap.size() - 1, colSize = worldMap.at(rowSize).size() - 1;
	//Spawns player at the catsle doors (19 x, 13 y).
	int currentPlayerCol = 19, currentPlayerRow = 13;
	int previousPlayerCol = currentPlayerCol, previousPlayerRow = currentPlayerRow;

	//Draw map initially.
	Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);

	//Continuously checks for user input.
	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();

		//If user wants to quit, breaks out and returns.
		if (keyPress == 'q' or keyPress == 'Q') break;
		else { //Else if user wants to move, change their current coordinates. For columns we change user position by 2 to make distances between x and y feel similar.
			if (keyPress == UP_ARROW) currentPlayerRow--;
			if (keyPress == DOWN_ARROW)	currentPlayerRow++;
			if (keyPress == LEFT_ARROW) currentPlayerCol -= 2;
			if (keyPress == RIGHT_ARROW) currentPlayerCol += 2;

			//Prevents player from going outside the map.
			currentPlayerCol = clamp(currentPlayerCol, 1, colSize - 1);
			currentPlayerRow = clamp(currentPlayerRow, 1, rowSize - 1);

			//Puzzle 1 call (for house in bottom left).
			//TODO: Make a function utility for the clearscreen, movecursor, set_cursor_mode, resetcolor, etc.
			if ((currentPlayerCol >= 4 and currentPlayerCol <= 7) and (currentPlayerRow >= 36 and currentPlayerRow <= 39)) {
				clearscreen();
				movecursor(0, 0);
				set_cursor_mode(true);
				resetcolor();
				set_raw_mode(false);
				Puzzle_1();
			}

			//If player position has moved, redraw map and update player position.
			if (previousPlayerCol != currentPlayerCol or previousPlayerRow != currentPlayerRow) {
				previousPlayerRow = currentPlayerRow;
				previousPlayerCol = currentPlayerCol;
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
		}
	}
}

//Basic arithmatic puzzle.
void Puzzle_1() {
	int puzzleAnswer = 18, userInput = 0;

	cout << "In an ancient wall drawing, you find images depicting a item appearing from the wall. This item seems to only be able to be accessed after solving a math problem. As you look around, hidden in a dark corner, a problem bleeds out, ""Solve the problem to pass the test: (5 * 2) (8 / 4) + 3 + 7 - 12"". What do you believe the answer to be?" << endl;
	cin >> userInput;

	if (userInput == 'q' or userInput == 'Q') {
		Utility_Back_To_Map();
		Update_Map();
	}

	while (userInput != puzzleAnswer) {
		cout << "You enter your answer and...nothing happens. It seems you were wrong. Thinking again, what do you believe the answer is?" << endl;
		cin >> userInput;
	}

	cout << "As you hear rock scraping against rock, it turns out your answer proved fruitful! Walking over and peering into the box turns up an old key. I wonder what that's used for..." << endl;

	Utility_Back_To_Map();
}

void Puzzle_2() {

}

void Puzzle_3() {

}

void Puzzle_4() {

}

void Puzzle_5() {

}

void die() {
	cout << "BAD INPUT!!" << endl;
	exit(1);
}

void Utility_Back_To_Map() {
	set_cursor_mode(false);
	set_raw_mode(true);
	resetcolor();
	clearscreen();
	movecursor(0, 0);
}

void Utility_Exit_Out() {
	set_cursor_mode(true);
	set_raw_mode(false);
	resetcolor();
	clearscreen();
	movecursor(0, 0);
}
