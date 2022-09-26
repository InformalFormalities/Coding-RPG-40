//Partners: Declan Doss, Vahan Avetisyan, Khushkaranpreet Grewal, Andrew Smith
//Bullet Points: Declan (World Map, Puzzles, Combat), Vahan (Dialogue), Khush (World Map), Andrew (Puzzles)
//Extra Credit: Khush (Cover art/music)
//URL to cover art: https://cdn.discordapp.com/attachments/1014310924435324979/1022972858617573386/76E1530D-419C-477F-A719-F8D47818B0DB.png
//URL to music: https://youtu.be/V8_kwrMaoaM

#include <iostream>
#include "/public/colors.h"
using namespace std;

//Global vector. Any function can access it.
//Current: 202 x 42 map. 200 x 40 playable area. NOTE: Player moves 1 on the y axis, 2 on the x axis; this is to make the x and y feel similar.
vector<string> worldMap = { //VERY IMPORTANT NOTE: For every extra special character (i.e. \, ", ') to make it appear on screen, you must add that many spaces. Will run into out of bounds errors otherwise.
	"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *",
	"*                                                                                  _/              /                                                                                                        *",
	"*             /\\         /\\                                                       /               |                                                                                                         *",
	"*            /  \\       /  \\                                                    _/               /                                                                                                          *",
	"*            |/\\|       |/\\|                                                   /                /                                        /\\                                                                 *",
	"*            |--|       |--|                              /\\               ___/               /                                         /  \\                                                                *",
	"*       /----|  |-------|  |----\\                        /  \\           __/                  |                                          |  |                                                                *",
	"*       |                       |                        |  |          /                    /                                           |__|                                                                *",
	"*       |                       |                        |__|        _/                    /                                                                                                                *",
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
	"*                     ^                                    /    |                      |     \\                  ^                                                                                           *",
	"*                       ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^     |                       |       ^ ^ ^ ^ ^          ^                                                          /\\                            *",
	"*                                                               |                        |                ^          ^                                                       /  \\                           *",
	"*                                                                |                        |                ^           ^ ^ ^ ^ ^                                             |  |                           *",
	"*                                                                 |                        |        /\\      ^                   ^                                            |__|                           *",
	"*                                                                 |                        |       /  \\       ^                   ^                                                                         *",
	"*                                                                  |                       |       |  |          ^                   ^                                                                      *",
	"*                                                                   |                       |      |__|            ^ ^ ^ ^             ^ ^                                                  ""Help me!""        *",
	"*                                                                    |                       |                             ^               ^                                                   __           *",
	"*                                                                     |                       |                              ^               ^                                                /  \\          *",
	"*                                                                    |                         |                               ^               ^ ^ ^ ^ ^                                     /    \\         *",
	"*                                                                   |                          |                                 ^ ^ ^                   ^                                  /  /\\  \\        *",
	"*                                                                   |                          |                                      ^                    ^                               /  /  \\  \\       *",
	"*                                                                   |                          |                                        ^                    ^                            /  |    |  \\      *",
	"*                                                                   |                          |                                          ^ ^ ^ ^ ^ ^         ^                           |  |____|  |      *",
	"*                                                                  |                          |                                                       ^        ^                          |          |      *",
	"*                                                                 |                          |                                                         ^       ^                          |          |      *",
	"*      /\\                                                       |                          |                                                           ^        ^                         |          |      *",
	"*     /  \\                                                     |                          |                                                              ^        ^ ^ ^ ^                 |          |      *",
	"*     |  |                                                      |                          |                                                               ^               ^ ^ ^ ^ ^ ^ ^ ^|          |      *",
	"*     |__|                                                      |                          |                                                                 ^                            |          |      *",
	"*                                                              |                          |                                                                    ^                          |          |      *",
	"*                                                             |                          |                                                                       ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^|          |      *",
	"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *",
};

//Global boolean. Necessary for Tower_Sequence to occur.
//Boolean is used to keep track whether a puzzle has been done or not. If it has, value will change to true in Update_Game.
bool puzzleOneDone = false, puzzleTwoDone = false, puzzleThreeDone = false, puzzleFourDone = false, puzzleFiveDone = false;
//Kerney is alive by default.
bool kerneyAlive = true;

//Declarations of functions used below.
void Main_Menu();
void Introduction();
void Draw_Map(int rowSize, int colSize, int playerPositionCol, int playerPositionRow);
void Update_Game();
void Puzzle_One();
void Puzzle_Two();
void Puzzle_Three();
void Puzzle_Four();
void Puzzle_Five();
void Tower_Sequence();
void Utility_Map_Settings();
void Utility_Text_Settings();
void Utility_Press_E_To_Continue();



//Main acts as a driver program.
int main() {

	//Seeding for later use (in puzzle 3 & 4).
	srand(time(NULL));

	//Calls Main_Menu function to print out the main menu so it's the first screen user sees.
	Main_Menu();

	//Calls Introduction function to give exposition before putting player onto the map.
	Introduction();

	//Set cursor mode to false for it to not appear on screen and call Update_Game to draw map.
	//NOTE: Update_Game integrates the whole program together, so it acts as main in a sense.
	set_cursor_mode(false);
	Update_Game();

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
	movecursor(y, x - 15);
	cout << BOLDYELLOW << "Stolen Seduction: Stallman Edition\n" << RESET;

	movecursor(y + 3, x - 12);
	cout << "Press" << GREEN << " 'p' " << RESET << "to start the game\n";

	movecursor(y + 6, x - 11);
	cout << "Press" << RED << " 'q' " << RESET << "to quit the game\n";

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
	clearscreen();
	movecursor(0, 0);

	cout << "Craftsman: Thank you for coming on a short notice, our kingdom has been falling apart because of Bill Kerney.\n";
	cout << "           Kerney has wanting revenge for 10 years now, and seems like he is getting ready for his attacks.\n";
	cout << "           If we want stop Kerney you will need some weapons and armor.\n";
	cout << "           As you may have already guessed, I'm a craftsman. I'll provide you with a sword, shield, and some armor.\n\n";
	cout << "You: Okay, thank you. Though, about Kerney, what is his backstory?\n\n";
	cout << "Craftsman: He was not always on the dark side, he was the kings right hand man. He knows everything about the kingdom and how it operates.\n\n";
	cout << "You: Do you know what he has been planning for his attacks?\n\n";
	cout << "Craftsman: All I know is that he has traps placed around the kingdomin in the form of riddles and puzzles. And he is after the prince, the king's son, Stallman.\n";
	cout << "           Now go and explore the kingdom and gather resources and clues to stop Kerney.\n";
	cout << "           You can find me in the castle. I'm Mencarelli, by the way.\n";

	Utility_Press_E_To_Continue();
}

//Draws the map initially, and when player moves.
void Draw_Map(int rowSize, int colSize, int playerPositionCol, int playerPositionRow) {
	clearscreen();

	//Keeps map in top left.
	movecursor(0, 0);

	//Prints map out. Repeats printing one row and all columns.
	for (size_t row = 0; row <= rowSize; row++) {
		for (size_t col = 0; col <= colSize; col++) {
			//Prints player location.
			if (col == playerPositionCol and row == playerPositionRow) cout << "P";
			//Makes castle bold black.
			else if ((row >= 2 and row <= 12) and (col >= 8 and col <= 32)) cout << BOLDWHITE << worldMap.at(row).at(col) << RESET;
			//Makes path (i.e. the ^ symbols) bold green.
			else if (worldMap.at(row).at(col) == '^') cout << BOLDGREEN << worldMap.at(row).at(col) << RESET;
			//Makes puzzle hut 1 (in bottom left) bold magenta.
			else if ((row >= 36 and row <= 39) and (col >= 6 and col <= 9)) cout << BOLDMAGENTA << worldMap.at(row).at(col) << RESET;
			//Makes puzzle hut 2 (top side of river, on the left) bold magenta.
			else if ((row >= 5 and row <= 8) and (col >= 57 and col <= 60)) cout << BOLDMAGENTA << worldMap.at(row).at(col) << RESET;
			//Makes puzzle hut 3 (bottom side of river, on the right) bold magenta.
			else if ((row >= 23 and row <= 26) and (col >= 99 and col <= 102)) cout << BOLDMAGENTA << worldMap.at(row).at(col) << RESET;
			//Makes puzzle hut 4 (top side of river, on the right) bold magenta.
			else if ((row >= 4 and row <= 7) and (col >= 135 and col <= 139)) cout << BOLDMAGENTA << worldMap.at(row).at(col) << RESET;
			//Makes puzzle hut 5 (closest to the tower) bold magenta.
			else if ((row >= 20 and row <= 23) and (col >= 172 and col <= 176)) cout << BOLDMAGENTA << worldMap.at(row).at(col) << RESET;
			//Makes river boundaries above bridge bold cyan.
			else if ((row >= 1 and row <= 11) and (col >= 64 and col <= 100)) cout << BOLDCYAN << worldMap.at(row).at(col) << RESET;
			//Makes river boundaries below bridge bold cyan.
			else if ((row >= 18 and row <= 41) and (col >= 62 and col <= 95) and (worldMap.at(row).at(col) != '\\')) cout << BOLDCYAN << worldMap.at(row).at(col) << RESET;
			//Makes tower bold red.
			else if ((row >= 27 and row <= 41) and (col >= 186 and col <= 197)) cout << BOLDRED << worldMap.at(row).at(col) << RESET;
			//Else prints map at default coloring.
			else cout << worldMap.at(row).at(col);
		}
		cout << endl;
	}
}

//Updates the values to pass to Draw_Map when player moves.
void Update_Game() {
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

			//NOTE FOR BELOW: Else ifs are used because only one can happen at a time (i.e. player can only be at one location at a time). There's no reason to check the other statements because of that.
			//Puzzle 1 call (for hut in bottom left).
			if ((currentPlayerCol >= 6 and currentPlayerCol <= 9) and (currentPlayerRow >= 36 and currentPlayerRow <= 39) and puzzleOneDone == false) {
				Puzzle_One();
				currentPlayerRow = previousPlayerRow;
				currentPlayerCol = previousPlayerCol;
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
			//Puzzle 2 call (for hut top side river, on left).
			else if ((currentPlayerCol >= 57 and currentPlayerCol <= 60) and (currentPlayerRow >= 5 and currentPlayerRow <= 8) and puzzleTwoDone == false) {
				Puzzle_Two();
				currentPlayerRow = previousPlayerRow;
				currentPlayerCol = previousPlayerCol;
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
			//Puzzle 3 call (for hut bottom side river, on right).
			else if ((currentPlayerCol >= 99 and currentPlayerCol <= 102) and (currentPlayerRow >= 23 and currentPlayerRow <= 26) and puzzleThreeDone == false) {
				Puzzle_Three();
				//Spawns and sets player position back at castle doors.
				currentPlayerRow = 13;
				currentPlayerCol = 19;
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
			//Puzzle 4 call (for hut top side river, on right).
			else if ((currentPlayerCol >= 136 and currentPlayerCol <= 139) and (currentPlayerRow >= 4 and currentPlayerRow <= 7) and puzzleFourDone == false) {
				Puzzle_Four();
				currentPlayerRow = previousPlayerRow;
				currentPlayerCol = previousPlayerCol;
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
			//Puzzle 5 call (for hut closest to tower).
			else if ((currentPlayerCol >= 172 and currentPlayerCol <= 176) and (currentPlayerRow >= 20 and currentPlayerRow <= 23) and puzzleFiveDone == false) {
				Puzzle_Five();
				currentPlayerRow = previousPlayerRow;
				currentPlayerCol = previousPlayerCol;
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
			//Checks whether user can enter the tower or not. Area where they can enter in the line of the tower that the path leads to (184th column, and 38th-41st row).
			else if ((puzzleOneDone == true and puzzleTwoDone == true and puzzleThreeDone == true and puzzleFourDone == true and puzzleFiveDone == true) and (currentPlayerCol == 185) and (currentPlayerRow >= 38 and currentPlayerRow <= 41)) {
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

//Basic arithmetic puzzle.
void Puzzle_One() {
	Utility_Text_Settings();

	unsigned short puzzleAnswer = 18, userInput = 0;

	cout << BOLDWHITE << "As you walk towards a wall of rock, you notice an entrance. Deciding to enter, you head into the bowels of the Earth.\n";
	cout << "Inside, you find an ancient wall drawing, with images depicting a item appearing from the stone.\n";
	cout << "This item seems to only be able to be accessed after solving a math problem.\n";
	cout << "As you look around, something catches your eye. A math equation bleeds out from a dark and gloomy corner: \n\n";
	cout << "    ""Solve the problem to pass the test: (5 * 2) (8 / 4) + 3 + 7 - 12""\n\n" << "What do you believe the answer to be?\n" << RESET;
	cin >> userInput;

	while (userInput != puzzleAnswer) {
		//Clears cin's error flag when userInput is not an acceptable input.
		cin.clear();
		//Throws out user input if not a positive number.
		//100000 parameter is larger than the size of an unsigned short, so a user cannot give more inputs than cin.ignore can handle.
		//Backslash n is where the cin.ignore stops reading.
		cin.ignore(100000, '\n');

		cout << BOLDWHITE << "\nYou enter your answer and...nothing happens. It seems you were wrong.\n" << "Thinking again, what do you believe the answer is?\n" << RESET;
		cin >> userInput;
	}

	cout << BOLDWHITE << "\nAs you hear rock scraping against rock, it turns out your answer proved fruitful!\n" << "Walking over and peering into the box turns up an old key. I wonder what that's used for...\n" << RESET;

	puzzleOneDone = true;

	Utility_Press_E_To_Continue();

	Utility_Map_Settings();
}

//Traditional riddle.
void Puzzle_Two() {
	Utility_Text_Settings();

	string puzzleAnswer = "newspaper", userInput;

	cout << BOLDWHITE << "Entering an old hut, you find a skeleton, surrounded by scraps of what appears to be paper.\n";
	cout << "One of them appears legible, reading:\n\n";
	cout << "    What is white, black, and red all over?\n\n";
	cout << "Confused by the seemingly random question, you learn there's a basement that's locked.\n";
	cout << "Unable to open it, you walk back to the piece of paper.\n" << "What's ""white, black, and red all over"" you ponder.\n" << "Could it be a..." << RESET;

	cin >> userInput;

	for (auto& ch : userInput) {
		ch = tolower(ch);
	}

	while (userInput != puzzleAnswer) {
		cin.clear();
		//The 4.3 billion parameter is larger than the size of a string, so a user cannot give more input than cin.ignore can handle.
		cin.ignore(4300000000, '\n');

		cout << BOLDWHITE << "\nHmmm, no it couldn't be that. What about a..." << RESET;
		cin >> userInput;

		for (auto& ch : userInput) {
			ch = tolower(ch);
		}
	}

	cout << BOLDWHITE << "\nA rumbling begins, and you notice the door behind you opens.\n" << "Walking down the appearing stairs, you find an old key wrapped in a cloth. I wonder what that's used for...\n" << RESET;

	puzzleTwoDone = true;

	Utility_Press_E_To_Continue();

	Utility_Map_Settings();
}

//Door puzzle and Kerney fight.
void Puzzle_Three() {
	Utility_Text_Settings();

	string userInput, puzzleAnswer = "r";
	int userHealth = 100, kerneyHealth = 100;

	cout << BOLDWHITE << "Walking underneath the bridge, you find an alcove. Coming closer, you notice there's an old door.\n";
	cout << "Becoming curious, you enter, down the long and winding stariwell.\n";
	cout << "Entering a room, you notice a slab of metal with engravings on it. Might be worth a pretty penny, you think as you pick it up.\n";
	cout << "Walking farther in, you notice this seems to be an old catacomb, with offering to the deceased still left behind.\n";
	cout << "Exploring some more, you come up against a large door, seemingly impassible. The slab of metal you have looks like it might fit into the door.\n";
	cout << "Do you choose to insert it top, bottom, left, or right first? (t/b/l/r)\n" << RESET;

	cin >> userInput;

	while (userInput != puzzleAnswer) {
		cin.clear();
		cin.ignore(4300000000, '\n');

		cout << BOLDWHITE << "\nThat didn't work, try again. Do you choose to insert it top, bottom, left, or right first? (t/b/l/r)\n" << RESET;
		cin >> userInput;
	}

	cout << BOLDWHITE << "\nStanding stunnded, it actually works and the door begins to recede into the floor.";
	cout << "\nWalking in, you notice the place looks ransacked. Intrigued, you continue on until you find...";
	cout << "\nWait is that Kerney? Is he the one who's been ransacking this place? Aghast, you go to confront him.\n" << RESET;

	while (userHealth > 0 or kerneyHealth > 0) {
		cout << BOLDWHITE << "What would you like to do?\n" << RESET;
		cout << BOLDRED << "   A) Attack\n" << BOLDBLUE << "   B) Block\n" << YELLOW << "   C) Send an extinction level asteroid into the Earth\n" << RESET;
		cin >> userInput;

		while (userInput != "a" and userInput != "b" and userInput != "A" and userInput != "B" and userInput != "c" and userInput != "C") {
			cin.clear();
			cin.ignore(4300000000, '\n');
			cin >> userInput;
		}

		clearscreen();
		movecursor(0, 0);
		//User's turn to attack or block.
		if (userInput == "a" or userInput == "A") {
			cout << BOLDRED << "Attacking Kerney, you deal 25 damage!\n" << RESET;
			kerneyHealth -= 25;
			if (kerneyHealth <= 0) kerneyHealth = 0;
		} else if (userInput == "b" or userInput == "B") {
			cout << BOLDBLUE << "Blocking, you fortify by 10 points of health.\n" << RESET;
			userHealth += 10;
			if (userHealth > 100) userHealth = 100;
		} else {
			cout << BOLDWHITE << "Wow, asshole much? Taking the whole world with you just because you don't want to fight Kerney? Shame man, shame.\n" << RESET;

			Utility_Press_E_To_Continue();

			Utility_Text_Settings();

			exit(0);
		}

		cout << GREEN << "\nYour HP: " << userHealth << "/100\n";
		cout << RED << "Kerney's HP: " << kerneyHealth << "/100\n" << RESET;

		//If Kerney is defeated...
		if (kerneyHealth <= 0) {
			string spareOrKill;
			cout << BOLDWHITE << "\nBeating Kerney in battle, you face him as he lies on the floor.\n";
			cout << "You notice a key flat on the floor in the pile of things Kerney was scavaging. Noticing it's similar to the other ones you found before, you take it.\n\n";
			cout << "Facing back to Kerney, he asks you:\n\n" << RESET;
			cout << "Kerney: Well boy? You going to kill me?\n\n";
			cout << BOLDWHITE << "   Will you spare or kill Kerney? (s/k)\n" << RESET;
			cin >> spareOrKill;

			while (spareOrKill != "s" and spareOrKill != "S" and spareOrKill != "k" and spareOrKill != "K") {
				cin.clear();
				cin.ignore(4300000000, '\n');
				cin >> spareOrKill;
			}

			if (spareOrKill == "k" or spareOrKill == "K") {
				kerneyAlive = false;
				cout << "\nYou: I'll spare the world your torture.\n\n";
				cout << "Kerney: So be it.\n";

				puzzleThreeDone = true;

				Utility_Press_E_To_Continue();

				Utility_Map_Settings();

				return;
			} else { //Lore for if Kerney is alive. kerneyAlive isn't changed since by default it's a global variable set to true.
				clearscreen();
				movecursor(0, 0);
				cout << BOLDWHITE << "Leaving the catacombs behind, you go back to the castle to talk to Mencarelli.\n\n\n" << RESET;

				cout << "You: Hey, I've been taking care of these traps and almost had Kerney. I spared him, so let's just hope he doesn't get any bright ideas.\n\n";
				cout << "Mencarelli: Don't worry about that right now. Stallman came up to me and told me to tell you that he wants to meet you in the castle. I'm thining it's about Kerney.\n\n";
				cout << BOLDWHITE << "\nSome time later...\n\n\n" << RESET;
				cout << "You: Prince Stallman you wanted to see me.\n\n";
				cout << "Stallman: Yes, good to finally see you, I wanted to thank you on taking care of the traps throughout the kingdom.\n\n";
				cout << "You: I had a chance to kill him, but didn't.\n\n";
				cout << "Kerney: (Clears throat) Am I interupting an important conversation?\n\n";
				cout << "Stallman: Kerney! What are you dong here? How did you get inside the castle?\n\n";
				cout << "Kerney: Oh I guess you have forgotten that I was once part of this royalty and know my way around.\n\n";
				cout << "You: I won't let you get to Stallman.\n\n";
				cout << "Kerney: Hahahaha, you are just a week little warrior.\n\n";

				cout << BOLDWHITE << "\nA battle ensues, leading with you being bested by Kerney and Stallman being kidnapped.\n\n\n" << RESET;

				cout << "You: Mencarelli! Kerney took Stallman! I don't know where; oh lord he probably already killed him.\n\n";
				cout << "Mencarelli: Don't jump to conclutions boy. When Kerney was exiled to the edges of the kingdom, he built a tower. He must be there. Now go!\n\n";

				puzzleThreeDone = true;

				Utility_Press_E_To_Continue();

				Utility_Map_Settings();

				return;
			}
		}

		//Kerney's turn to attack or block.
		if (rand() % 2 == 0) {
			cout << BOLDBLUE << "\nKerney blocks your next attack, fortifying by 10 health.\n" << RESET;
			kerneyHealth += 10;
			if (kerneyHealth > 100) kerneyHealth = 100;
		} else {
			cout << BOLDRED << "\nKerney attacks you, dealing 25 damage!\n" << RESET;
			userHealth -= 25;
		}
		cout << GREEN << "\nYour HP: " << userHealth << "/100\n";
		cout << RED << "Kerney's HP: " << kerneyHealth << "/100\n" << RESET;
		//If you die...
		if (userHealth <= 0) {
			Utility_Map_Settings();
			cout << BOLDWHITE << "You died, please try again!\n" << RESET;
			clearscreen();
			movecursor(0, 0);

			cout << BOLDWHITE << "Waking up, you notice you're back at the castle.\n";
			cout << "Must have been a dream, dying in a catacomb to Kerney.\n";
			cout << "I still need to take care of that puzzle on the right side of the bridge, you think as you walk outside the castle.\n" << RESET;

			Utility_Press_E_To_Continue();
			return; //...returns you to map and can retry again.
		}
	}
}

//"Answer is completely random" puzzle.
void Puzzle_Four() {
	Utility_Text_Settings();

	string userInput;

	cout << BOLDWHITE << "Entering a run down home, you notice a space on the wall engraved with a puzzle.\n";
	cout << "The puzzle reads: ""What does this spell? modnarsirewsnaeht""\n\n";
	cout << "   A) The answer is random\n   B) The answer is random\n   C) The answer is random\n   D) The answer is random\n";
	cout << "\nWhat do you think the answer is?\n" << RESET;

	cin >> userInput;

	//Picks a random number between 1 and 4 and checks whether the user chose the correct answer. Else reprompts.
	while (true) {
		int puzzleAnswer = (rand() % 4) + 1;

		if (puzzleAnswer == 1 and (userInput == "A" or userInput == "a")) {
			break;
		} else if (puzzleAnswer == 2 and (userInput == "B" or userInput == "b")) {
			break;
		} else if (puzzleAnswer == 3 and (userInput == "C" or userInput == "c")) {
			break;
		} else if (puzzleAnswer == 4 and (userInput == "D" or userInput == "d")) {
			break;
		}

		cout << BOLDWHITE << "\nPressing the button does nothing. You ponder if your answer is a bit too logical...\n" << RESET;

		cin.clear();
		cin.ignore(4300000000, '\n');
		cin >> userInput;
	}

	cout << BOLDWHITE << "\nGetting the puzzle right, an old rickety bookshelf moves out of the way.\n";
	cout << "Walking towards the bookshelf, you realize there's obviously a secret room inside.\n";
	cout << "Looking around, you find nothing of interest besides an old key. I wonder what that's used for...\n" << RESET;

	puzzleFourDone = true;

	Utility_Press_E_To_Continue();

	Utility_Map_Settings();
}

//HACKER-MAN!!!
void Puzzle_Five() {
	Utility_Text_Settings();

	string puzzleAnswer = "password", userInput;

	cout << BOLDWHITE << "A strange building resides next to the tower. Inside of it, you find a room full of...well, you're not quite sure.\n";
	cout << "There are many long wirey things around, and the walls are covered in an ugly beige coloring, with outcroppings all around\n";
	cout << "Looking around, you find what seems to be the centerpiece of the room, with a lot of things you can press. They move, so you decide to press them all to see what happens.\n";
	cout << "Hitting one button in particularl causes lights as bright as the sun to turn on. Panicking, you hide best you can in case someone comes.\n";
	cout << "After a bit's hesitation, you step out and go to a thing that's displaying some words. Looking at it, it reads:\n\n";
	cout << """Please enter your password:""\n\n" << "What do you think this ""password"" might be?\n" << RESET;

	cin >> userInput;

	while (userInput != puzzleAnswer) {
		cin.clear();
		cin.ignore(4300000000, '\n');
		cout << BOLDWHITE << "\nWords come up that read:\n\n" << RED << "    ACCESS DENIED\n\n";
		cout << BOLDWHITE << "As you figure you got it wrong, you try again. What do you think this ""password"" could be?\n" << RESET;
		cin >> userInput;
	}

	cout << BOLDWHITE << "\nAfter entering ""password"" as the password, it reads:\n\n" << GREEN << "      ACCESS GRANTED\n   Welcome Hack-er-man!\n\n" << RESET;
	cout << BOLDWHITE << "At the same time that line of text appears, a drawer opens up, revealing an old key. I wonder what that's used for...\n" << RESET;

	puzzleFiveDone = true;

	Utility_Press_E_To_Continue();

	Utility_Map_Settings();
}

void Tower_Sequence() {
	Utility_Text_Settings();

	string userInput;

	//If kerneyAlive is set to true...
	if (kerneyAlive) {
		cout << "You: Stallman, are you there?\n\n";
		cout << "Stallman: Yes, I'm here. Don't worry about me.\n\n\n";
		cout << BOLDWHITE << "As you open the door to the tower and make your way inside, you eventually reach the top.\n\n\n" << RESET;
		cout << "Kerney: There you are. What do you mean not to worry about you? I came all this way to save you and this what you say.\n\n";
		cout << "Stallman: Yes because I love Kerney and I'm going to be with him for the rest of my life.\n\n";
		cout << "You: What is this nonsense? What spell have you put on Stallman Kerney?\n\n";
		cout << "Kerney: Oh boy you never learned. I have no spell on Stallman.\n\n";
		cout << "You: Oh my god you both have lost your minds.\n\n";
		cout << "Stallman: No we haven't. We're just in love. Isn't Kerney just the most handsomestest?\n\n";

		cout << BOLDWHITE << "\nDo you concur? (y/n)\n\n" << RESET;
		cin >> userInput;

		while (userInput != "yes" and userInput != "Yes" and userInput != "y" and userInput != "Y") {
			cin.clear();
			cin.ignore(4300000000, '\n');
			cout << BOLDWHITE << "\nWrong answer bucko, try again.\n" << RESET;
			cin >> userInput;
		}

		cout << "\nYou: Yes he is the most handsomestest.\n\n";
		cout << BOLDWHITE << "Startled and unaware of why you just said that, you decide to leave.\n" << RESET;
		cout << "You: I'm getting the heck out of here.\n\n";
		cout << "Stallman: And make sure you lock the door behind you!\n";

		Utility_Press_E_To_Continue();
	} else { //Else if kerneyAlive isn't true...
		cout << "You: Stallman, are you there?\n\n";
		cout << "Stallman: Yes I am here. I'm still locked up, though.\n\n";
		cout << "You: Don't worry, I have the keys to get you out of here.\n\n";
		cout << BOLDWHITE << "\n\nOpening the door, and traveling up the tower, you eventually enter Stallman's room.\n\n" << RESET;
		cout << "Stallman: Thank you! How came I ever repay you?\n\n";
		cout << "You: You know exactly what you can do to repay me 😏😉\n\n";

		cout << BOLDWHITE << "As Prince Stallman is brought back to the castle, you're recognized as being a hero and are greeted to a banquet in your honor.\n" << RESET;

		Utility_Press_E_To_Continue();
	}
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

//Used to not repeat code in puzzle functions.
void Utility_Press_E_To_Continue() {
	cout << BOLDWHITE << "\nPress E to continue" << RESET << endl;

	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();
		if (keyPress == 'e' or keyPress == 'E') break;
	}
}
