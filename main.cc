#include <iostream>
#include <unistd.h>
#include "/public/colors.h"
using namespace std;

//Global vector. Any function can access it.
//Current: 100 x 30 map. TODO: Change/fill in later; make lore friendly.
vector<string> worldMap = {
	"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"*                                                                                                 *",
	"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *",
};


//Draws the map initially and after player moves.
void Draw_Map(int rowSize, int colSize, int playerPositionCol, int playerPositionRow) {
	clearscreen();

	//Keeps map in top left. Change 0 0 to whatever to have map in another spot.
	movecursor(0, 0);

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
	//Spawn player in the middle of the world. TODO: Change to a lore-friendly starting point.
	int currentPlayerCol = colSize / 2, currentPlayerRow = rowSize / 2;
	int previousPlayerCol = currentPlayerCol, previousPlayerRow = currentPlayerRow;

	//Draw map initially.
	Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);

	//Continuously checks for user input.
	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();

		//If user wants to quit, breaks out and returns.
		if (keyPress == 'q' or keyPress == 'Q') break;
		else { //Else if user wants to move, change their current coordinates.
			if (keyPress == UP_ARROW) currentPlayerRow--;
			if (keyPress == DOWN_ARROW)	currentPlayerRow++;
			if (keyPress == LEFT_ARROW) currentPlayerCol -= 2;
			if (keyPress == RIGHT_ARROW) currentPlayerCol += 2;

			//Prevents player from going outside the map.
			currentPlayerCol = clamp(currentPlayerCol, 1, colSize - 1);
			currentPlayerRow = clamp(currentPlayerRow, 1, rowSize - 1);

			//If player position has moved, redraw map and update player position.
			if (previousPlayerCol != currentPlayerCol or previousPlayerRow != currentPlayerRow) {
				previousPlayerRow = currentPlayerRow;
				previousPlayerCol = currentPlayerCol;
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
		}
	}
}


void Puzzle_1() {

}

void Puzzle_2() {

}

void Puzzle_3() {

}

void Puzzle_4() {

}

void Puzzle_5() {

}

//Main acts as a driver program.
int main() {

	//TODO: If statement for if user picks/presses something then prompt the user if they want to go to the map.
	string userChoice;

	cout << "Do you want to go to the world map (y/n): ";
	cin >> userChoice;

	if (userChoice == "Yes" or userChoice == "yes" or userChoice == "y" or userChoice == "Y") {
		set_cursor_mode(false);
		Update_Map();
	}

	//TODO: If statement for if user wants to go to inventory.

	//TODO: If statement for if the user wants to enter a place?

	//Clean up after yourself.
	set_cursor_mode(true);
	set_raw_mode(false);
	resetcolor();
	clearscreen();
}
