//Partners: Declan Doss, Vahan Avetisyan, Khushkaranpreet Grewal, Andrew Smith
//Bullet Points: Declan (World Map, Puzzles), Vahan (Dialogue), Khush (World Map), Andrew (Puzzles) //TODO: Update these before submission.
//Extra Credit: Khush (Cover art/music), [Name] (Inventory system)
//URL to cover art: https://cdn.discordapp.com/attachments/1014310924435324979/1022972858617573386/76E1530D-419C-477F-A719-F8D47818B0DB.png
//URL to music:

#include <iostream>
#include <unistd.h>
#include "/public/colors.h"
using namespace std;

//Global vector. Any function can access it.
//Current: 202 x 42 map. 200 x 40 playable area. NOTE: Player moves 1 on the y axis, 2 on the x axis; this is to make the x and y feel similar. TODO: Change/fill in later; make lore friendly.
vector<string> worldMap = { //VERY IMPORTANT NOTE: For every extra special character (i.e. \, ", ') to make it appear on screen, you must add that many spaces. Will run into out of bounds errors otherwise.
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

//Global boolean. Necessary for Tower_Sequence to occur.
//Boolean is used to keep track whether a puzzle has been done or not. If it has, value will change to true in Update_Map.
bool puzzleOneDone = false, puzzleTwoDone = false, puzzleThreeDone = false, puzzleFourDone = false, puzzleFiveDone = false;

//Declarations of functions used below. NECESSARY!!!
void Main_Menu();
void Introduction();
void Draw_Map(int rowSize, int colSize, int playerPositionCol, int playerPositionRow);
void Update_Map();
void Puzzle_One();
void Puzzle_Two();
void Puzzle_Three();
void Puzzle_Four();
void Puzzle_Five();
void Tower_Sequence();
void die();
void Utility_Map_Settings();
void Utility_Text_Settings();



//Main acts as a driver program.
int main() {

	//Calls Main_Menu function to print out the main menu so it's the first screen user sees.
	Main_Menu();

	//Calls Introduction function to give exposition before putting player onto the map.
	Introduction();

	//Set cursor mode to false for it to not appear on screen and call Update_Map to draw map.
	//NOTE: Update_Map integrates the whole program together, so it acts as main in a sense. FIXME: Maybe change the aformentioned later?
	set_cursor_mode(false);
	Update_Map();

	//Clean up after yourself.
	Utility_Text_Settings();
}



//Prints initial menu screen.
void Main_Menu() {
	//Finds size of screen and stores it as ROWS, COLS (y, x).
	const auto [ROWS, COLS] = get_terminal_size();

	//Find center coordinates of screen.
	int x = COLS / 2;
	int y = ROWS / 2;

	clearscreen();

	//Places cursor in the middle. x must be changed to accomodate for movecursor putting the "W" in the middle, not the sentence in the middle.
	//Same goes for below print statements; adjust them to fit where on the screen you want them to be.
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

		//If player wants to play, return to main() so next function can be called.
		if (keyPress == 'p' or keyPress == 'P') {
			return;
		} else if (keyPress == 'q' or keyPress == 'Q') { //Else if player wants to quit, reset settings (clean up after yourself) and exit.
			Utility_Text_Settings();
			exit(0);
		}
	}
}

void Introduction() {
	//TODO: Introduce player to world and exposition stuff.
	//LORE NOTE: PLAYER STARTS AT THE GATES OF THE CASTLE, DON'T CONTRADICT THAT STARTING POSITION PLEASE. (Compile and run program to see where if needed.)
}

//Draws the map initially, and when player moves.
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
			else if (worldMap.at(row) == "/" and worldMap.at(col) == "/") cout << CYAN << worldMap.at(row).at(col);
			else cout << worldMap.at(row).at(col);
		}
		cout << endl;
	}
}

//Updates the values to pass to Draw_Map when player moves.
void Update_Map() {
	//Define how many rows/cols there are.
	const int rowSize = worldMap.size() - 1, colSize = worldMap.at(rowSize).size() - 1;
	//Spawns player at the castle doors (19th column, 13th row).
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

			//NOTE FOR BELOW: Else ifs are used because only one can happen at a time (player can only be at one location at a time). There's no reason to check the other statements because of that.
			//Puzzle 1 call (for house in bottom left).
			if ((currentPlayerCol >= 3 and currentPlayerCol <= 6) and (currentPlayerRow >= 36 and currentPlayerRow <= 39) and puzzleOneDone == false) {
				Puzzle_One();
				puzzleOneDone = true;
				currentPlayerRow = previousPlayerRow;
				currentPlayerCol = previousPlayerCol;
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
			//TODO: Will have to repeat the above if statement similarly for each puzzle.
			//Puzzle 2 call (for []).
			/***********else if () {
							Puzzle_Two();
							puzzleTwoDone = true;
							currentPlayerRow = previousPlayerRow;
							currentPlayerCol = previousPlayerCol;
							Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
						}
						//Puzzle 3 call (for []).
						else if () {
							Puzzle_Three();
							puzzleThreeDone = true;
							currentPlayerRow = previousPlayerRow;
							currentPlayerCol = previousPlayerCol;
							Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);

						}
						//Puzzle 4 call (for []).
						else if () {
							Puzzle_Four();
							puzzleFourDone = true;
							currentPlayerRow = previousPlayerRow;
							currentPlayerCol = previousPlayerCol;
							Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);

						}
						//Puzzle 5 call (for []).
						else if () {
							Puzzle_Five();
							puzzleFiveDone = true;
							currentPlayerRow = previousPlayerRow;
							currentPlayerCol = previousPlayerCol;
							Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);

						}*********************************/
			//Checks whether user can enter the tower or not. Area where they can enter in the line of the tower that the path leads to (184th column, and 38th-41st row). //TODO: Check to make sure this works (can't check rn as other puzzles aren't finished).
			else if ((puzzleOneDone == true and puzzleTwoDone == true and puzzleThreeDone == true and puzzleFourDone == true and puzzleFiveDone == true) and (currentPlayerCol >= 184 and currentPlayerCol <= 195) and (currentPlayerRow >= 38 and currentPlayerRow <= 41)) {
				Tower_Sequence();
				return;
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
void Puzzle_One() {
	Utility_Text_Settings();

	int puzzleAnswer = 18, userInput = 0;

	//TODO: Make text pretty when printed to screen. Applies for all text in this function.
	cout << "In an ancient wall drawing, you find images depicting a item appearing from the wall. This item seems to only be able to be accessed after solving a math problem. As you look around, hidden in a dark corner, a problem bleeds out, ""Solve the problem to pass the test: (5 * 2) (8 / 4) + 3 + 7 - 12"". What do you believe the answer to be?" << endl;
	cin >> userInput;
	if (!cin) die();

	while (userInput != puzzleAnswer) {
		cout << "You enter your answer and...nothing happens. It seems you were wrong. Thinking again, what do you believe the answer is?" << endl;
		cin >> userInput;
		if (!cin) die();
	}

	cout << "As you hear rock scraping against rock, it turns out your answer proved fruitful! Walking over and peering into the box turns up an old key. I wonder what that's used for..." << endl;
	cout << "Press E to go back to the map." << endl;
	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();
		if (keyPress == 'e' or keyPress == 'E') break;
	}

	Utility_Map_Settings();
}

//TODO: Define what kind of puzzle it is.
void Puzzle_Two() {
	Utility_Text_Settings();
	/*
		//TODO: Declare variables (if needed) here.

		//TODO: Make text pretty when printed to screen. Applies for all text in this function.
	//TODO:	cout << [Riddle text/lore/whatever here] << endl;
		cin >> userInput;
		if (!cin) die();

		while (userInput != puzzleAnswer) {
	//TODO:		cout << [If user input is wrong, give them some feedback] << endl;
			cin >> userInput;
			if (!cin) die();
		}

	//TODO:	cout << [When user gets it correct, tell them so!] << endl;
	*/
	cout << "Press E to go back to the map." << endl;
	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();
		if (keyPress == 'e' or keyPress == 'E') break;
	}

	Utility_Map_Settings();
}

//TODO: Define what kind of puzzle it is.
void Puzzle_Three() {
	Utility_Text_Settings();
	/*
		//TODO: Declare variables (if needed) here.

		//TODO: Make text pretty when printed to screen. Applies for all text in this function.
	//TODO:	cout << [Riddle text/lore/whatever here] << endl;
		cin >> userInput;
		if (!cin) die();

		while (userInput != puzzleAnswer) {
	//TODO:		cout << [If user input is wrong, give them some feedback] << endl;
			cin >> userInput;
			if (!cin) die();
		}

	//TODO:	cout << [When user gets it correct, tell them so!] << endl;
	*/
	cout << "Press E to go back to the map." << endl;
	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();
		if (keyPress == 'e' or keyPress == 'E') break;
	}

	Utility_Map_Settings();
}

//TODO: Define what kind of puzzle it is.
void Puzzle_Four() {
	Utility_Text_Settings();
	/*
		//TODO: Declare variables (if needed) here.

		//TODO: Make text pretty when printed to screen. Applies for all text in this function.
	//TODO:	cout << [Riddle text/lore/whatever here] << endl;
		cin >> userInput;
		if (!cin) die();

		while (userInput != puzzleAnswer) {
	//TODO:		cout << [If user input is wrong, give them some feedback] << endl;
			cin >> userInput;
			if (!cin) die();
		}

	//TODO:	cout << [When user gets it correct, tell them so!] << endl;
	*/
	cout << "Press E to go back to the map." << endl;
	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();
		if (keyPress == 'e' or keyPress == 'E') break;
	}

	Utility_Map_Settings();
}

//TODO: Define what kind of puzzle it is.
void Puzzle_Five() {
	Utility_Text_Settings();
	/*
		//TODO: Declare variables (if needed) here.

		//TODO: Make text pretty when printed to screen. Applies for all text in this function.
	//TODO:	cout << [Riddle text/lore/whatever here] << endl;
		cin >> userInput;
		if (!cin) die();

		while (userInput != puzzleAnswer) {
	//TODO:		cout << [If user input is wrong, give them some feedback] << endl;
			cin >> userInput;
			if (!cin) die();
		}
	//TODO:	cout << [When user gets it correct, tell them so!] << endl;
	*/
	cout << "Press E to go back to the map." << endl;
	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();
		if (keyPress == 'e' or keyPress == 'E') break;
	}

	Utility_Map_Settings();
}

void Tower_Sequence() {
	Utility_Text_Settings();

	//TODO: The final tower sequence will have to be purely text based unfortunately. So do the explanation/lore/whatever and do the whole sequence of walking up to Stallman blah blah blah.
	//TODO: ONCE THE PUZZLE WHERE YOU FIGHT KERNEY IS DONE, I'LL ADD AN IF STATEMENT FOR THE TWO SEPARATE ENDINGS: ONE WHERE KERNEY STEALS HIM FROM YOU AND THE OTHER WHERE YOU GET TO KEEP HIM.
}

//NOTE: Unfortunately at the moment, I can't figure out a way to check user input so die() is used in place when user input needs to be something specific.
void die() {
	cout << "BAD INPUT!" << endl;
	exit(1);
}

//Sets settings to what they need to be for map to work properly.
void Utility_Map_Settings() {
	set_cursor_mode(false);
	set_raw_mode(true);
	resetcolor();
	clearscreen();
	movecursor(0, 0);
}

//Resets settings back to what they should be when not displaying map.
void Utility_Text_Settings() {
	set_cursor_mode(true);
	set_raw_mode(false);
	resetcolor();
	clearscreen();
	movecursor(0, 0);
}
