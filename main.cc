//Cover art and music for this project by ChachaTeraSira (Github), @chachaterasira (Instagram).
//URL to cover art: 	https://cdn.discordapp.com/attachments/1014310924435324979/1022972858617573386/76E1530D-419C-477F-A719-F8D47818B0DB.png
//URL to music: 		https://youtu.be/V8_kwrMaoaM

//All code is original unless otherwise indicated. Original code begins line 308.
//Code encompased between the block comment lines belong to Professor William Kerney of Clovis Community College, Clovis, California. Contact information: https://www.cloviscollege.edu/directory/william-kerney.html
//Originally included in "/public/colors.h". GPL licensed.

/******************************************************************************************************************************************************************************************************************************************/
#ifndef __COLORS_H__
#define __COLORS_H__
//colors.h - A lightweight replacement for NCURSES that does 24 bit color, cursor movement, and nonblocking I/O
//It uses standard ANSI escape codes to set the foreground and background text colors for a terminal
//Prerequisite: Use with a modern terminal emulator, such as iterm2 for Mac or PuTTY for PC
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <utility>
#include <cassert>
#include <functional>
#include <queue>

//Usage:
//Echo RED as part of a cout to turn the following text red
//Echo RESET after you are done and it will go back to normal
//Example: cout << RED << "Hello World" << RESET << endl;
const std::string RESET   = "\033[0m";
const std::string BLACK   = "\033[30m";      /* Black */
const std::string RED     = "\033[31m";      /* Red */
const std::string GREEN   = "\033[32m";      /* Green */
const std::string YELLOW  = "\033[33m";      /* Yellow */
const std::string BLUE    = "\033[34m";      /* Blue */
const std::string MAGENTA = "\033[35m";      /* Magenta */
const std::string CYAN    = "\033[36m";      /* Cyan */
const std::string WHITE   = "\033[37m";      /* White */
const std::string BOLDBLACK   = "\033[1m\033[30m";      /* Bold Black */
const std::string BOLDRED     = "\033[1m\033[31m";      /* Bold Red */
const std::string BOLDGREEN   = "\033[1m\033[32m";      /* Bold Green */
const std::string BOLDYELLOW  = "\033[1m\033[33m";      /* Bold Yellow */
const std::string BOLDBLUE    = "\033[1m\033[34m";      /* Bold Blue */
const std::string BOLDMAGENTA = "\033[1m\033[35m";      /* Bold Magenta */
const std::string BOLDCYAN    = "\033[1m\033[36m";      /* Bold Cyan */
const std::string BOLDWHITE   = "\033[1m\033[37m";      /* Bold White */


//24-bit color support.
//NCURSES refuses to implement it since implementation is nonstandard -
//https://invisible-island.net/ncurses/ncurses.faq.html#xterm_16MegaColors

//Sets the background color for all text printed from this point on
//Values range from 0 to 255 in each color channel
//Example: setbgcolor(255,0,255) will set the background color to purple
inline void setbgcolor(uint8_t R, uint8_t G, uint8_t B) {
	std::cerr << "\033[48;2;" << (int)R << ";" << (int)G << ";" << (int)B << "m";
}

//Sets the foreground color for all text printed from this point on
//Example: setcolor(128,128,128) will set the foreground color to 50% grey
inline void setcolor(uint8_t R, uint8_t G, uint8_t B) {
	std::cerr << "\033[38;2;" << (int)R << ";" << (int)G << ";" << (int)B << "m";
}

//Sets the foreground and background colors back to the default
//Example: resetcolor();
inline void resetcolor() {
	std::cerr << "\033[0m";
}

//These functions are like a mini NCURSES library

//Returns the ROWS and COLS of the current terminal
//Example: auto [rows,cols] = get_terminal_size() will make a variable named rows that has the number of rows of the current screen, and cols with the number of columns
inline std::pair<int, int> get_terminal_size() {
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	return {w.ws_row - 1, w.ws_col}; //Subtract 1 to give room for the UNIX prompt at the bottom of the screen
}

//Moves the cursor to the indicated row and column
//Example: movecursor(10,40) will move the cursor to the row 10 down from the top and 40 to the right of the left edge
inline void movecursor(uint32_t row, uint32_t col) {
	std::cerr << "\033[" << row << ";" << col << "H";
}

//Clears the screen
//Example: clearscreen();
inline void clearscreen() {
	std::cerr << "\033[2J";
}

//Allows you to turn the cursor on or off
//Example: show_cursor(false) will turn off the cursor (the little green box)
inline void show_cursor(bool flag) {
	if (flag)
		std::cerr << "\033[?25h";
	else
		std::cerr << "\033[?25l";
}
inline void set_cursor_mode(bool flag) {
	show_cursor(flag);    //Alias
}

//Mouse support - there may be a bug with the first click
inline static bool mouse_mode = false; //We default to not reading mouse events
inline void remind_about_callbacks(int row, int col);
//With mouse events on, if they don't set a handler for mousedown events we will remind them
inline static std::function<void(int, int)> mousedown_callback = remind_about_callbacks;
inline static std::function<void(int, int)> mouseup_callback = [](int, int) {}; //Ignore mouseup events by default

//The default function reminds users how to set up a callback then disables itself
inline void remind_about_callbacks([[maybe_unused]] int row, [[maybe_unused]] int col) {
	std::cerr << "You enabled mouse events but you didn't call 'on_mousedown' to set up a callback, so enabling mouse events was pointless.\n";
	std::cerr << "Write code like this: 'void mousedown(int row, int col) { std::cout << row << \",\" << col << std::endl; }\nand then in main: on_mousedown(mousedown);\nDitto for mouseup. Then whenever the user clicks, it will call these two functions." << std::endl;
	std::cerr << "If you instead want to disable, for example, mouseup events, do this: on_mouseup([](int,int){});" << std::endl;

	//Disable reminders
	mousedown_callback = [](int, int) {};
}

//Register callback - every time there is a click it will call this function
//Once you've enabled mouse events with set_mouse_mode(true), you need to set up a callback
// for mousedown and/or mouseup events.
//To set up a callback (a function that will get called when the user clicks), do this:
//  on_mousedown(your_function_name);
//Where your_function_name is something like this:
//  void your_function_name(int row, int col) { cout << row << "," << col << endl; }
inline void on_mousedown(std::function<void(int, int)> f) {
	mousedown_callback = f;
}
inline void on_mouseup(std::function<void(int, int)> f) {
	mouseup_callback = f;
}


//This function changes the standard input from "canonical" mode (which means it buffers until a newline is read) into raw mode, where it'll return one keystroke at a time
//Example: set_raw_mode(true) will turn on nonblocking I/O for cin
//Example: set_raw_mode(false) will reset I/O to work like normal
static bool raw_mode = false; //We default to canonical mode
inline void set_raw_mode(bool flag) {
	static struct termios old_tio; //Save old settings
	if (flag and !raw_mode) { //Save original terminal settings
		tcgetattr(STDIN_FILENO, &old_tio);
		raw_mode = true;
		termios tio = old_tio;
		tio.c_lflag &= ~(ICANON | ECHO); // Disable echo and canonical (cooked) mode
		tcsetattr(STDIN_FILENO, TCSANOW, &tio);
		//std::cerr << "^[[?1049h" << std::endl;
	} else if (!flag and raw_mode) { //Restore original settings
		tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
		raw_mode = false;
	}
	//else, do nothing since it's already set one way or the other
}

//TODO: Figure out a better way of doing smcup & rmcup
//Switches between alternate buffers, like Vim
//This lets you switch the whole contents of the screen
inline void set_alternate_window(bool flag) {
	if (flag) {
		std::cerr << "^[[?1049h";
		std::cerr.flush();
		//std::cerr << "^[[?1049h" << std::endl;
	} else {
		std::cerr << "^[[22;0;0t";
		std::cerr.flush();
		//std::cerr << "^[[22;0;0t" << std::endl;
	}
}

//Many terminals support the ability to send mouse events
//Example: set_mouse_mode(true) will give us the ability to read clicks
inline void set_mouse_mode(bool flag) {
	if (flag) { //Enable mouse
		//Why == true? It makes the assertion failed message understandable
		assert(raw_mode == true); //Mouse can only be enabled in raw_mode
		std::cerr << "\033[?1000;1006;1015h";
	} else {
		//We can disable it outside of raw mode so no assert here
		std::cerr << "\033[?1000;1006;1015l";
	}
	mouse_mode = flag;
}

//Returns how many bytes are waiting in the input buffer
//Precondition: Requires set_raw_mode(true) to work
//Example: int bytes_available = kbhit() will return how many bytes are in the input queue to be read
inline int kbhit() {
	assert(raw_mode == true); //This code only works in raw mode
	int count = 0;
	ioctl(STDIN_FILENO, FIONREAD, &count);
	return count;
}

//Output values for quick_read() (in addition to ASCII codes)
//Some contants for making reading non-ASCII keys easy
//These might change, so be prepared to just deal with raw numbers from quick_read
const int ERR           = -1;
const int ESC           = 27; //ASCII code 27 is Escape
const int KEY_EOF       = 4;
const int ARROW_UP      = 156;
const int ARROW_DOWN    = 157;
const int ARROW_RIGHT   = 158;
const int ARROW_LEFT    = 159;
const int UP_ARROW      = ARROW_UP; //Alias
const int DOWN_ARROW    = ARROW_DOWN; //Alias
const int RIGHT_ARROW   = ARROW_RIGHT; //Alias
const int LEFT_ARROW    = ARROW_LEFT; //Alias
const int HOME          = 266;
const int INSERT        = 267;
const int DEL           = 268;
const int DELETE        = DEL; //Alias
const int END           = 269;
const int PAGE_UP       = 270;
const int PAGE_DOWN     = 271;
const int F1            = 315;
const int F2            = 316;
const int F3            = 317;
const int F4            = 318;
const int F5            = 319;
const int F6            = 321; //Hmm
const int F7            = 322;
const int F8            = 323;
const int F9            = 324;
const int F10           = 325;
const int F11           = 327; //Hmm
const int F12           = 328;
const int MOUSE_WHEEL_UP    = 650;
const int MOUSE_WHEEL_DOWN  = 658;

//TODO: Improve escape sequence parsing, especially if two are hit between polls
//Does a non-blocking I/O read from standard input, returns one keystroke
//Lightweight Equivalent to NCURSES getch()
//Precondition: Requires set_raw_mode(true) to work
//Example: int ch = quick_read() will return ERR if no key has been hit, or 'A' if they hit A, or PAGE_DOWN if they hit page down, etc.
inline int quick_read() {
	assert(raw_mode == true); //This code only works in raw mode
	int bytes_available = kbhit();
	if (bytes_available) {
		char c = getchar();
		if (c != 27) //The escape key is ASCII code 27
			return c;
		//Happy fun escape code parsing time
		bytes_available--; //We've already pulled off the escape character
		if (!bytes_available) return c; //They just hit Escape in this case
		//Mouse click looks like \e[<0;3;21M and a release \e[<0;3;21. Where 2 is x (from left) and 22 is y (from top)
		//[<0;111;2m

		//Grab remaining bytes into a deque
		std::deque<char> input;
		for (int i = 0; i < bytes_available; i++)
			input.push_back(getchar());

		//See if it contains the 4 byte escape sequence for a mouse event
		while (input.size() > 4) {
			auto [rows, cols] = get_terminal_size(); //Make sure we're returning an int in range
			if (input[0] == '[' and
			        input[1] == '<' and
			        input[2] == '0' and
			        input[3] == ';') { //Mouse event
				for (int i = 0; i < 4; i++) input.pop_front();
				bool reading_col = true; //Col is read first, then row after a ;
				int temp_col = 0, temp_row = 0;
				while (input.size()) {
					c = input.front();
					input.pop_front();
					if (c == ';') {
						reading_col = false;
						continue;
					} else if (c == 'M') { //Mousedown event
						mousedown_callback(temp_row, temp_col);
					} else if (c == 'm') { //Mouseup event
						mouseup_callback(temp_row, temp_col);
					} else if (isdigit(c)) {
						int temp = c - '0';
						if (reading_col) temp_col = 10 * temp_col + temp;
						else temp_row = 10 * temp_row + temp;
						//Double clicks aren't handled, so just pretend nothing happened
						if (temp_col > cols or temp_row > rows) return ERR;
					}
				}

			} else break;
		}
		if (!input.size()) return ERR;

		//The magic number we return is the sum of the escape sequence, which works adequately
		int sum = 0;
		for (size_t i = 0; i < input.size(); i++) {
			c = input[i];
			//Special case F9 to F12 since they overlap with other F keys
			if (c == '2' and i == 1 and bytes_available == 4) {
				sum += 9;
			}
			sum += c;
		}
		return sum; //This should match ARROW_UP and so forth above
	}
	return ERR; //Nothing was read
}
#endif
/******************************************************************************************************************************************************************************************************************************************/

//Original code below...
#include "Character.h"
#include <map>
using namespace std;

//Global vector. Any function can access it.
//202 x 42 map; 200 x 40 playable area. NOTE: Player moves 1 on the y axis, 2 on the x axis; this is to make the x and y feel similar when moving.
//VERY IMPORTANT NOTE: For every extra special character (i.e. \, ", ', etc.) in order to make it appear on screen, you must add that many spaces.
//                     Will run into out of bounds errors when printing out to the screen otherwise.
vector<string> worldMap = {
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
	"*                                                                   |                       |      |__|            ^ ^ ^ ^             ^ ^                                                                  *",
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

//Need to keep track of POI's (points of interest) in an ordered fashion for when we randomly add them to the map later.
map<int, int> POI;
//Boolean is used to keep track whether a puzzle has been done or not. If it has, value will change to true in Update_Game. Necessary for Tower_Sequence to occur.
bool puzzleOneDone = false, puzzleTwoDone = false, puzzleThreeDone = false, puzzleFourDone = false, puzzleFiveDone = false;
//Initialize Player and Kerney as type Character (since they're the only two guranteed fightable characters in the game).
Character Player, Kerney;
//Finds size of screen and stores it as ROWS, COLS (y, x).
const auto [ROWS, COLS] = get_terminal_size();
//Find center coordinates of screen (used later on in Main_Menu, and Puzzle_Three if player dies).
const int x = COLS / 2;
const int y = ROWS / 2;

//Declarations of functions used (below main).
void Main_Menu();
void Introduction();
void Draw_Map(int rowSize, int colSize, int playerPositionCol, int playerPositionRow);
void Update_Game();
void Initialize_Map_Points_Of_Interest();
void Inside_Castle_Trade();
void View_Inventory();
void Game_Combat(Character &Opponent);
void Mini_Games(int &currentPlayerRow, int previousPlayerRow, int &currentPlayerCol, int previousPlayerCol);
void Puzzle_One();
void Puzzle_Two();
void Puzzle_Three();
void Puzzle_Four();
void Puzzle_Five();
void Tower_Sequence();
void Utility_Map_Settings();
void Utility_Text_Settings();
void Utility_Press_E_To_Continue();
void Utility_Prevent_Clip(int &currentPlayerRow, int previousPlayerRow, int &currentPlayerCol, int previousPlayerCol);



//Main acts as a driver program.
int main() {

	//Seeding for later use (in Puzzle_3() & Puzzle_4()).
	srand(time(NULL));

	//By default, lower player attack power so fighting enemies is a challenge in the beginning.
	Player.attackPwr = 25;
	Player.defense = 5;

	//Calls Main_Menu function to print out the main menu so it's the first screen user sees.
	Main_Menu();

	//Give player explanation of the controls.
	cout << BOLDWHITE
	     << "Use the arrow keys or WASD to move up, left, down, and right respectively.\n"
	     << "From the map, press Q to quit the game.\n"
	     << "From the map, press I to view your stats and inventory.\n"
	     << "Use Ctrl + C (Windows/Linux) or Cmd + C (Mac) to kill the program at any time.\n"
	     << RESET;
	Utility_Press_E_To_Continue();
	Utility_Text_Settings();

	//Calls Introduction function to give exposition before putting player onto the map.
	Introduction();

	//Set cursor mode to false for it to not appear on screen and call Update_Game to draw map.
	//NOTE: Update_Game integrates the whole program together, so it acts as main in a sense.
	set_cursor_mode(false);
	Update_Game();

	//Clean up after yourself.
	Utility_Text_Settings();
}



//Credit for this function goes to ChachaTeraSira (Github), @chachaterasira (Instagram).
//Prints initial menu screen.
void Main_Menu() {
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
			Utility_Text_Settings();
			return;
		}
		//Else if player wants to quit, reset settings (clean up after yourself) and exit.
		else if (keyPress == 'q' or keyPress == 'Q') {
			Utility_Text_Settings();
			exit(0);
		}
	}
}

void Introduction() {
	string userName;

	clearscreen();
	movecursor(0, 0);

	//Let player choose their name.
	cout << BOLDWHITE << "Choose a name for yourself: " << RESET;
	cin >> userName;
	Player.name = userName;
	//Assign Kerney his name (keeps things all in one place).
	Kerney.name = "Kerney";

	clearscreen();
	movecursor(0, 0);

	cout << "Craftsman: Thank you for coming on a short notice, our kingdom has been falling apart because of Bill Kerney.\n"
	     << "           Kerney has wanting revenge for 10 years now, and seems like he is getting ready for his attacks.\n"
	     << "           If we want stop Kerney you will need some weapons and armor.\n"
	     << "           As you may have already guessed, I'm a craftsman. I'll provide you with a sword, shield, and some armor.\n"
	     << "           In addition, don't worry about sinking in the river. It's quite shallow, and someone with your stature should be able to walk across it just fine.\n\n"
	     << "You: Okay, thank you. Though, about Kerney, what is his backstory?\n\n"
	     << "Craftsman: He was not always on the dark side. At one time, he was the kings right hand man. He knows everything about the kingdom and how it operates.\n\n"
	     << "You: Do you know what he has been planning for his attacks?\n\n"
	     << "Craftsman: All I know is that he has traps placed around the kingdom in the form of riddles and puzzles...and he is after the prince--the king's son--Stallman.\n"
	     << "           You can find me in the castle by coming through the front entrance, where you can buy gear from me. I'm Weapons Master Mencarelli, by the way.\n"
	     << "           Now, go and explore the kingdom! Gather resources and clues that might help you stop Kerney!\n";

	Utility_Press_E_To_Continue();
}


//Draws the map initially, and when player moves.
void Draw_Map(int rowSize, int colSize, int playerPositionCol, int playerPositionRow) {
	//Keeps map in top left.
	movecursor(0, 0);

	//Prints map out. Repeats printing one row and all columns.
	for (size_t row = 0; row <= rowSize; row++) {
		for (size_t col = 0; col <= colSize; col++) {
			//Prints player location.
			if (row == playerPositionRow and col == playerPositionCol) cout << "P";
			//Prints out POI's (points of interest) for player to explore.
			//With this, you're basically saying if the map "POI" has the row we're on, and if at that key (row) the associated value (col) is the same, print out I.
			else if (POI.contains(row) and POI.at(row) == col) cout << BOLDWHITE << "I" << RESET;
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

	//Initialize all points of interest.
	Initialize_Map_Points_Of_Interest();

	//Draw initial map.
	Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);

	//Continuously checks for user input.
	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();

		//If user wants to quit, breaks out and returns.
		if (keyPress == 'q' or keyPress == 'Q') break;
		else if (keyPress == 'i' or keyPress == 'I') {
			View_Inventory();
			Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
		} else { //Else if user wants to move, change their current coordinates. For columns we change user position by 2 to make distances between x and y feel similar.
			if (keyPress == UP_ARROW or keyPress == 'w') currentPlayerRow--;
			if (keyPress == DOWN_ARROW or keyPress == 's')	currentPlayerRow++;
			if (keyPress == LEFT_ARROW or keyPress == 'a') currentPlayerCol -= 2;
			if (keyPress == RIGHT_ARROW or keyPress == 'd') currentPlayerCol += 2;

			//Prevents player from going outside the map.
			currentPlayerCol = clamp(currentPlayerCol, 1, colSize - 1);
			currentPlayerRow = clamp(currentPlayerRow, 1, rowSize - 1);

			//NOTE FOR BELOW: Else if's are used because only one can happen at a time (i.e. player can only be at one location at a time). There's no reason to check the other statements as a result, reducing runtime.
			//Prevents player from clipping into main castle block OR leftmost tower OR rightmost tower. (Code is written with respect to the previous pseudocode OR's.)
			if (((currentPlayerCol >= 8 and currentPlayerCol <= 32) and (currentPlayerRow >= 6 and currentPlayerRow <= 12)) or
			        ((currentPlayerCol >= 13 and currentPlayerCol <= 16) and (currentPlayerRow >= 2 and currentPlayerRow <= 5)) or
			        ((currentPlayerCol >= 24 and currentPlayerCol <= 27) and (currentPlayerRow >= 2 and currentPlayerRow <= 5))) {

				//If player wants to trade with Mencarelli, run the function to do so.
				if ((currentPlayerCol >= 18 and currentPlayerCol <= 21) and (currentPlayerRow >= 9 and currentPlayerRow <= 12)) Inside_Castle_Trade();

				//Once player is done trading, set player position back to where they were, and redraw map.
				Utility_Prevent_Clip(currentPlayerRow, previousPlayerRow, currentPlayerCol, previousPlayerCol);
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
			//Prevents player from clipping into bridge.
			else if ((currentPlayerCol >= 61 and currentPlayerCol <= 91) and
			         ((currentPlayerRow >= 12 and currentPlayerRow <= 13) or (currentPlayerRow >= 16 and currentPlayerRow <= 17))) {
				Utility_Prevent_Clip(currentPlayerRow, previousPlayerRow, currentPlayerCol, previousPlayerCol);
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
			//Puzzle 1 call (for hut in bottom left).
			else if ((currentPlayerCol >= 6 and currentPlayerCol <= 9) and (currentPlayerRow >= 36 and currentPlayerRow <= 39)) {
				//If player hasn't done the puzzle, send them into it.
				if (!puzzleOneDone) Puzzle_One();

				//Always keep player from clipping into hut and redraw.
				Utility_Prevent_Clip(currentPlayerRow, previousPlayerRow, currentPlayerCol, previousPlayerCol);
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
			//Puzzle 2 call (for hut top side river, on left).
			else if ((currentPlayerCol >= 57 and currentPlayerCol <= 60) and (currentPlayerRow >= 5 and currentPlayerRow <= 8)) {
				//If player hasn't done the puzzle, send them into it.
				if (!puzzleTwoDone)	Puzzle_Two();

				//Always keep player from clipping into hut and redraw.
				Utility_Prevent_Clip(currentPlayerRow, previousPlayerRow, currentPlayerCol, previousPlayerCol);
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
			//Puzzle 3 call (for hut bottom side river, on right).
			else if ((currentPlayerCol >= 99 and currentPlayerCol <= 102) and (currentPlayerRow >= 23 and currentPlayerRow <= 26)) {
				//If player hasn't done the puzzle, send them into it.
				if (!puzzleThreeDone) {
					Puzzle_Three();
					//If player dies or Kerney is spared, set them back to the castle. Otherwise, prevent clipping.
					if (Kerney.isAlive) {
						currentPlayerRow = 13;
						currentPlayerCol = 19;
					} else Utility_Prevent_Clip(currentPlayerRow, previousPlayerRow, currentPlayerCol, previousPlayerCol);
				}
				//Otherwise, prevent clipping.
				else Utility_Prevent_Clip(currentPlayerRow, previousPlayerRow, currentPlayerCol, previousPlayerCol);

				//Regardless, redraw the map.
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
			//Puzzle 4 call (for hut top side river, on right).
			else if ((currentPlayerCol >= 136 and currentPlayerCol <= 139) and (currentPlayerRow >= 4 and currentPlayerRow <= 7)) {
				//If player hasn't done the puzzle, send them into it.
				if (!puzzleFourDone) Puzzle_Four();

				//Always keep player from clipping into hut and redraw.
				Utility_Prevent_Clip(currentPlayerRow, previousPlayerRow, currentPlayerCol, previousPlayerCol);
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
			//Puzzle 5 call (for hut closest to tower).
			else if ((currentPlayerCol >= 172 and currentPlayerCol <= 176) and (currentPlayerRow >= 20 and currentPlayerRow <= 23)) {
				//If player hasn't done the puzzle, send them into it.
				if (!puzzleFiveDone) Puzzle_Five();

				//Always keep player from clipping into hut and redraw.
				Utility_Prevent_Clip(currentPlayerRow, previousPlayerRow, currentPlayerCol, previousPlayerCol);
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
			//Checks whether player is at tower.
			else if ((currentPlayerCol >= 187 and currentPlayerCol <= 198) and (currentPlayerRow >= 27 and currentPlayerRow <= 41)) {
				//Checks if player can enter tower or not. Area where they can enter in the line of the tower that the path leads to (184th column, and 38th-41st row).
				if ((puzzleOneDone and puzzleTwoDone and puzzleThreeDone and puzzleFourDone and puzzleFiveDone) and
				        (currentPlayerCol == 187) and (currentPlayerRow >= 38 and currentPlayerRow <= 41)) {
					Tower_Sequence();
					return;
				}
				//Otherwise, make sure the player doesn't clip into the tower and redraw map.
				else {
					Utility_Prevent_Clip(currentPlayerRow, previousPlayerRow, currentPlayerCol, previousPlayerCol);
					Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
				}
			}
			//Checks whether player is at a point of interest or not.
			else if (POI.contains(currentPlayerRow) and currentPlayerCol == POI.at(currentPlayerRow)) {
				Mini_Games(currentPlayerRow, previousPlayerRow, currentPlayerCol, previousPlayerCol);
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}

			//If player position has moved, update player position and redraw map.
			if (previousPlayerCol != currentPlayerCol or previousPlayerRow != currentPlayerRow) {
				previousPlayerRow = currentPlayerRow;
				previousPlayerCol = currentPlayerCol;
				Draw_Map(rowSize, colSize, currentPlayerCol, currentPlayerRow);
			}
		}
	}
}

//Handles when player goes to POI's (points of interest) on map.
//Creates and handles for up to 5 different types of POI's.
void Initialize_Map_Points_Of_Interest() {
	//Create i number of sets of coordinates to have POI's (points of interest) appear on map.
	for (int i = 0; i < 10; i++) {
		//NOTE: 40 comes from the total playable y-axis area of the map. The 1 just makes sure the POI doesn't end up on the topmost border of the map. Bottom is handled automatically by modulo 40.
		int yCoord = (rand() % 40) + 1;
		//NOTE: 200 comes from the total playable x-axis area of the map. The 1 just makes sure the POI doesn't end up on the leftmost border of the map. Right side is handled automatically by modulo 200.
		int xCoord = (rand() % 200) + 1;
		//If POI is on an even numbered spot, add 1 to make it odd numbered. Necessary since player walks on odd numbered spots for x-axis.
		if (xCoord % 2 == 0) xCoord++;

		//We need to check that the POI coordinates aren't somewhere that the player cannot reach.
		if (
		    //Targetting for castle.
		    (
		        //Main block of castle.
		        ((xCoord >= 7 and xCoord <= 31) and (yCoord >= 6 and yCoord <= 12)) or
		        //Left outcropping tower.
		        ((xCoord >= 12 and xCoord <= 15) and (yCoord >= 2 and yCoord <= 5)) or
		        //Right outcropping tower.
		        ((xCoord >= 23 and xCoord <= 27) and (yCoord >= 2 and yCoord <= 5))
		    )
		    or
		    //Targeting for bridge.
		    (
		        //Handles x coords, since those don't change between the top and bottom parts.
		        (xCoord >= 60 and xCoord <= 91) and
		        //Handles y coords for the top and bottom parts respectively.
		        ((yCoord >= 12 and yCoord <= 13) or (yCoord >= 16 and yCoord <= 17))
		    )
		    or
		    //Targetting for puzzle 1.
		    ((xCoord >= 5 and xCoord <= 9) and (yCoord >= 36 and yCoord <= 39))
		    or
		    //Targetting for puzzle 2.
		    ((xCoord >= 56 and xCoord <= 60) and (yCoord >= 5 and yCoord <= 8))
		    or
		    //Targetting for puzzle 3.
		    ((xCoord >= 98 and xCoord <= 102) and (yCoord >= 23 and yCoord <= 26))
		    or
		    //Targetting for puzzle 4.
		    ((xCoord >= 135 and xCoord <= 139) and (yCoord >= 4 and yCoord <= 7))
		    or
		    //Targetting for puzzle 5.
		    ((xCoord >= 171 and xCoord <= 176) and (yCoord >= 20 and yCoord <= 23))
		    or
		    //Targetting for tower.
		    ((xCoord >= 186 and xCoord <= 198) and (yCoord >= 27 and yCoord <= 41))
		    or
		    //Prevents POI's from spawning in the river. (Very rough targetting for the river using only the x-axis.)
		    (xCoord >= 59 and xCoord <= 100)
		    or
		    //If we already have a place in the map with the same key or key-value, redo it as well.
		    //Note: Without this, it'll cause some spots to not spawn since maps cannot have duplicate values.
		    (POI.contains(yCoord) or POI.contains(xCoord))
		) {
			//The long and short of that horrible, HORRIBLE code is basically this: If the POI spawns in any unreachable place by the player, decriment i so that the POI is redone.
			i--;
		}
		//Otherwise, if the POI is in an attainable spot by the player, add it's coordinates to our list of POI's.
		else POI.insert(pair<int, int>(yCoord, xCoord));
	}
}


void Inside_Castle_Trade() {
	Utility_Text_Settings();

	cout << BOLDWHITE << "Walking up to the castle gates, you yell up to the guard tower far above, " << RESET << "\"Permission to enter, sir? I need to speak with Weapons Master Mencarelli!\"\n"
	     << BOLDWHITE << "The guardsmen, recognizing you, allows you through.\n"
	     << "Remembering the way to take from before, you stride down the breathtakingly large stone hallway--eventaully coming to Weapons Master Mencarelli workstation.\n\n" << RESET
	     << "You: Mencarelli! I'm here to stock up. What'd you have?\n\n"
	     << "Mencarelli: Take a look...\n";

	Utility_Press_E_To_Continue();

	clearscreen();
	movecursor(0, 0);

	//Print out store options for player to purchase.
	cout << "Mencarelli: So, what'll it be?\n\n"
	     << BOLDWHITE << "1) Health Potion " << BOLDYELLOW << "(5 gold)\n"
	     << BOLDWHITE << "2) Shield " << BOLDYELLOW << "(10 gold)\n"
	     << BOLDWHITE << "3) Armor " << BOLDYELLOW << "(10 gold)\n"
	     << BOLDWHITE << "4) Weapon " << BOLDYELLOW << "(10 gold)\n"
	     << BOLDWHITE << "5) A wee little gremlin friend :) " << BOLDYELLOW << "(all your gold once you have at least 50 gold)\n"
	     << BOLDWHITE << "6) Stop trading\n\n"
	     << "Your balance: " << Player.balance << "\n\n" << RESET;

	//Continuously reprompt user until they wish to quit trading.
	while (true) {
		//Reset userInput for reuse.
		int userInput = 0;

		//FIXME: I have no idea why, but raw mode somehow isn't switched properly when calling Utility_Text_Settings earlier, so I have to manually add this in here.
		//       This isn't worth my time to figure out, so I'll leave it as is since negligibly slows down runtime.
		set_raw_mode(false);

		//While they don't give a valid input of 1 through 6, reprompt.
		while (!(userInput >= 1 and userInput <= 6)) {
			cin >> userInput;
			//If they entered a non-short, handle for that.
			if (!cin) {
				cin.clear();
				//Ignores user input if not a positive number.
				//numeric_limits<streamsize>::max() returns the max value for the type.
				//Backslash n is where the cin.ignore stops reading if reached before the numeric limit.
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> userInput;
			}
		}

		//This must be up here so that the good choice thing doesn't print, and it also saves runtime.
		if (userInput == 6) {
			cout << "\nMencarelli: That all? Alright. Good luck and be safe out there!\n";
			break;
		}

		//If player wants a health potion, give them a health potion.
		if (userInput == 1 and Player.balance >= 5) {
			Player.healthPotions++;
			Player.balance -= 5;
			cout << "\nMencarelli: Good choice " << Player.name << ", good choice...\n";
		}
		//Else if player wants a sheild, increase the amount of HP they fortify for by 5.
		else if (userInput == 2 and Player.balance >= 10) {
			Player.fortifyAmount += 5;
			Player.balance -= 10;
			cout << "\nMencarelli: Good choice " << Player.name << ", good choice...\n";
		}
		//Else if the player wants armor, increase their default defense stat by 5.
		else if (userInput == 3 and Player.balance >= 10) {
			Player.defense += 5;
			Player.balance -= 10;
			cout << "\nMencarelli: Good choice " << Player.name << ", good choice...\n";
		}
		//Else if the player wants a weapon upgrade, increase their attack power stat by 5.
		else if (userInput == 4 and Player.balance >= 10) {
			Player.attackPwr += 5;
			Player.balance -= 10;
			cout << "\nMencarelli: Good choice " << Player.name << ", good choice...\n";
		}
		//Else if the player is insane enough to spend this much gold on a gremlin, make them OP cause why not.
		else if (userInput == 5 and Player.balance >= 50) {
			cout << "\nMencarelli: Good choice " << Player.name << ", good choice...\n";
			Player.fortifyAmount += 9999;
			Player.defense += 9999;
			Player.attackPwr += 9999;
			//The large negative number prevents the player from obtaining more health potions because the gremlin "drinks" them all once the player gets them.
			//They're already so OP though that it shouldn't matter.
			Player.healthPotions = -9999;
			cout << "\nYou: Whoa! The little gremlin just drank all my health potions! What the hell Mencarelli?\n\n"
			     << "Mencarelli: Yes, well, you need to give it sustinence considering all the perks you gain from the little one. It'll continue to do that, just to mention.\n\n"
			     << "You: Why are you selling a gremlin in the first place?\n\n"
			     << "Mencarelli: Why did you buy the gremlin in the first place?\n";
			Player.balance = 0;
		} else { //Else if player doesn't have the balance, tell them so.
			cout << BOLDWHITE << "\nInsufficient funds!\n";
		}

		cout << BOLDWHITE << "Your balance: " << Player.balance << "\n" << RESET;
	}

	Utility_Press_E_To_Continue();

	Utility_Map_Settings();
}

void View_Inventory() {
	clearscreen();
	movecursor(0, 0);

	cout << "STATS\n"
	     << "Name: " << Player.name << "\n"
	     << "Health: " << Player.health << "\n"
	     << "Attack Power: " << Player.attackPwr << "\n"
	     << "Defense: " << Player.defense << "\n"
	     << "Fortification Amount: " << Player.fortifyAmount << "\n\n"
	     << "INVENTORY\n"
	     << "Health Potions: " << Player.healthPotions << "\n"
	     << "Gold: " << Player.balance << "\n\n"
	     << "Press I to return.";

	set_cursor_mode(false);
	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();
		if (keyPress == 'i' or keyPress == 'I') break;
	}

	Utility_Map_Settings();
}

//Handles combat, regardless of enemy.
void Game_Combat(Character &Opponent) {
	string userInput;

	//While neither side has lost...
	while (Player.health > 0 and Opponent.health > 0) {

		//PHASE 1: PLAYER'S TURN!
		cout << BOLDWHITE << "What would you like to do?\n" << RESET
		     << BOLDRED << "   A) Attack\n" << BOLDBLUE << "   B) Fortify\n" << BOLDGREEN << "   C) Drink a health potion (restores " << Player.POTION_HEAL_AMOUNT << " HP)\n" << RESET;
		//If fighting Kerney, give a unique option.
		if (Opponent.name == "Kerney") cout << BOLDYELLOW << "   Z) Send an extinction level asteroid into the Earth 👀\n" << RESET;
		cin >> userInput;

		//Reject user inputs that aren't valid and reprompt.
		while ((userInput != "a" and userInput != "A" and userInput != "b" and userInput != "B" and userInput != "c" and userInput != "C") and ((userInput != "z" or userInput != "Z") and Opponent.name != "Kerney")) {
			//Clears cin's error flag when userInput is not an acceptable input.
			cin.clear();
			//Ignores user input if not a positive number.
			//numeric_limits<streamsize>::max() returns the max value for the type.
			//Backslash n is where the cin.ignore stops reading if reached before the numeric limit.
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> userInput;
		}

		clearscreen();
		movecursor(0, 0);
		//User's turn to attack or block.
		if (userInput == "a" or userInput == "A") { //If user wants to attack...
			cout << BOLDRED << "Attacking " << Opponent.name << ", you deal " << Player.attackPwr << " damage!\n"
			     << "However, due to their armor, you only hit for " << Player.attackPwr - Opponent.defense << " damage.\n" << RESET;
			Opponent.health -= (Player.attackPwr - Opponent.defense);

			//Don't want to display a negative health number, so cap it to 0.
			if (Opponent.health < 0) Opponent.health = Opponent.MIN_HEALTH;
		} else if (userInput == "b" or userInput == "B") { //Else if user wants to fortify/block...
			cout << BOLDBLUE << "Fortifying, you gain " << Player.fortifyAmount << " points of health.\n" << RESET;
			Player.health += Player.fortifyAmount;

			//Don't want user health to go above the max, so cap it at 100.
			if (Player.health > Player.MAX_HEALTH) Player.health = Player.MAX_HEALTH;
		} else if (userInput == "c" or userInput == "C") {
			//If player has health potions, heal them.
			if (Player.healthPotions > 0) {
				cout << BOLDGREEN << "Drinking a health potion, you restore " << Player.POTION_HEAL_AMOUNT << " points of health!\n" << RESET;
				Player.health += Player.POTION_HEAL_AMOUNT;
				//For each potion they use, reduce their stockpile by 1.
				Player.healthPotions--;

				//Don't want user health to go above the max, so cap it at 100.
				if (Player.health > Player.MAX_HEALTH) Player.health = Player.MAX_HEALTH;
			}
			//Otherwise, tell the player they have none and their turn is over.
			else cout << "No health potion available! Your turn was wasted.\n";
		} else if (Opponent.name == "Kerney" and (userInput == "z" or userInput == "Z")) { //Else if fighting Kerney, and user wants to see the world burn...
			cout << BOLDWHITE << "Woooow, really? Taking the whole world with you just because you don't want to fight Kerney? Shame man, shame.\n" << RESET;

			Utility_Press_E_To_Continue();

			Utility_Text_Settings();

			exit(0);
		}

		//Update user on current health values.
		cout << GREEN << "\n" << Player.name << "'s HP: " << Player.health << "/" << Player.MAX_HEALTH << "\n";
		cout << RED << Opponent.name << "'s HP: " << Opponent.health << "/" << Opponent.MAX_HEALTH << "\n" << RESET;

		//If opponent dies, return.
		if (Opponent.health == Opponent.MIN_HEALTH) return;


		//PHASE 2: OPPONENT'S TURN!
		int opponentChoice = (rand() % 2);
		//If opponent attacks...
		if (opponentChoice == 0) {
			cout << BOLDRED << "\n" << Opponent.name << " attacks you, dealing " << Opponent.attackPwr << " damage!\n"
			     << "However, due to your armor, they only hit for " << Opponent.attackPwr - Opponent.defense << " damage.\n" << RESET;
			Player.health -= (Opponent.attackPwr - Player.defense);

			//Don't want to display a negative health number, so cap it to 0.
			if (Player.health < Player.MIN_HEALTH) Player.health = Player.MIN_HEALTH;
		} else if (opponentChoice == 1) { //Else if Kerney fortifys/blocks...
			cout << BOLDBLUE << "\n" << Opponent.name << " fortifys, gaining " << Opponent.fortifyAmount << " points of health.\n" << RESET;
			Opponent.health += Opponent.fortifyAmount;

			//Don't want opponent health to go above the max, so cap it at their max health.
			if (Opponent.health > Player.MAX_HEALTH) Opponent.health = Opponent.MAX_HEALTH;
		} else if (Opponent.name == "Kerney" and (rand() % 3 == 2)) { //Else if we're fighting Kerney and he wants to drink a health potion...
			//If opponent has health potions available, heal.
			if (Opponent.healthPotions > 0) {
				cout << BOLDGREEN << "\n" << Opponent.name << "Drinking a health potion " << Opponent.name << " restores " << Opponent.POTION_HEAL_AMOUNT << " points of health!\n" << RESET;

				Opponent.health += Opponent.POTION_HEAL_AMOUNT;
				//For each potion they use, reduce their stockpile by 1.
				Opponent.healthPotions--;

				//Don't want user health to go above the max, so cap it at 100.
				if (Opponent.health > Opponent.MAX_HEALTH) Opponent.health = Opponent.MAX_HEALTH;
			}
			//Otherwise, their turn was wasted trying to heal.
			else cout << Opponent.name << " goes for a health potion, but finds out they're out, wasting a turn.\n";
		}

		//Update user on current health values.
		cout << GREEN << "\n" << Player.name << "'s HP: " << Player.health << "/" << Player.MAX_HEALTH << "\n";
		cout << RED << Opponent.name << "'s HP: " << Opponent.health << "/" << Opponent.MAX_HEALTH << "\n" << RESET;

		//If player dies, return.
		if (Player.health == Player.MIN_HEALTH) return;
	}
}

void Mini_Games(int &currentPlayerRow, int previousPlayerRow, int &currentPlayerCol, int previousPlayerCol) {
	clearscreen();
	movecursor(0, 0);

	Utility_Text_Settings();

	//Get a random number between 1 and 100.
	int diceRoll = (rand() % 100) + 1;

	//Fight an enemy. 40% chance
	if (diceRoll <= 40) {
		//Random number between 1 and 3.
		int enemyType = rand() % 3 + 1;
		//Random number between 1 and 100.
		int lootReward = rand() % 100 + 1;
		string userInput;
		Character Enemy;

		//Give the game some variance so the player is not *always* fighting the same enemy. Stats remain the same between them.
		if (enemyType == 1) Enemy.name = "Marauder";
		else if (enemyType == 2) Enemy.name = "Bandit";
		else if (enemyType == 3) Enemy.name = "Highwayman";

		cout << "Journeying about, you're ambushed by a " << Enemy.name << "! Do you choose to fight? (y/n)\n";

		cin >> userInput;
		//Reprompt user if they don't give valid input.
		while (userInput != "y" and userInput != "Y" and userInput != "n" and userInput != "N") {
			cin.clear();
			//Ignores user input if not a positive number.
			//numeric_limits<streamsize>::max() returns the max value for the type.
			//Backslash n is where the cin.ignore stops reading if reached before the numeric limit.
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> userInput;
		}

		//If user wants to fight, send them into combat against the enemy.
		if (userInput == "y" or userInput == "Y") {
			cout << endl;
			Game_Combat(Enemy);
		}
		//Else if user wants to flee, return to map.
		else if (userInput == "n" or userInput == "N") {
			currentPlayerCol = previousPlayerCol;
			currentPlayerRow = previousPlayerRow;

			Utility_Press_E_To_Continue();
			Utility_Map_Settings();
			return;
		}

		//If player dies, respawn them at the castle.
		if (Player.health == Player.MIN_HEALTH) {
			set_cursor_mode(false);

			//Print "You Died" to screen, and have it fade out.
			for (int i = 256; i >= 0; i--) {
				clearscreen();
				movecursor(y + 3, x - 3);
				//Change color each run of the loop to make it look like it's fading out.
				setcolor(i, 0, 0);
				cout << "You Died\n";
				//Pauses the program for 10'000 usec.
				usleep(10'000);
			}

			movecursor(0, 0);

			//Set player position back to castle.
			currentPlayerCol = 19;
			currentPlayerRow = 13;

			//Reset player health.
			Player.health = Player.MAX_HEALTH;

			cout << BOLDWHITE << "Waking up in a cold sweat, you relize it was just a dream. Must have been your mind recalling battles fought the day prior...\n" << RESET;

			Utility_Press_E_To_Continue();
			Utility_Map_Settings();
			return;
		} else { //Else if player defeats the enemy, give them a reward from 4 options.
			cout << "Defeating the " << Enemy.name << ", you're rewarded with the spoils of combat!\n";

			//Get some gold (balance +15). 50% chance.
			if (lootReward <= 50) {
				cout << "Gold +15!\n";
				Player.balance += 15;
			}
			//Get health potions (healthPotions +1). 30% chance.
			else if (lootReward > 50 and lootReward <= 90) {
				cout << "Health Potions +1!\n";
				Player.healthPotions++;
			}
			//Get some armor (defense +5). Lower 5% chance due to armor likely being damaged in the fighting.
			else if (lootReward > 90 and lootReward <= 95) {
				cout << "Defense +5!\n";
				Player.defense += 5;
			}
			//Get a weapon (attackPwr +5). Lower 5% chance due to weapon likely being damaged in the fighting.
			else if (lootReward > 95 and lootReward <= 100) {
				cout << "Attack Power +5!\n";
				Player.attackPwr += 5;
			}

			//Reset player health so they can go into combat again without hp carrying over.
			Player.health = Player.MAX_HEALTH;
		}
	}
	//Get a potion (healthPotions +1). 10% chance.
	else if (diceRoll > 40 and diceRoll <= 50) {
		cout << BOLDWHITE << "Walking up to a skeleton leaning against a tree, you find a satchel. "
		     << "\"Well, they won't be needing this anymore\" you think as you look through it to find a spare health potion.\n"
		     << "Health Potions +1!\n" << RESET;
		Player.healthPotions++;
	}
	//Get some gold (balance +5). 30% chance.
	else if (diceRoll > 50 and diceRoll <= 80) {
		cout << BOLDWHITE << "Striding by an old tree, you notice a sack up in the branches. "
		     << "Out of curiosity, you climb the tree to grab it. Landing back on the ground, you open it up to reveal a pouch of gold!\n"
		     << "Gold +5!\n" << RESET;
		Player.balance += 5;
	}
	//Get some armor (defense +5). 10% chance.
	else if (diceRoll > 80 and diceRoll <= 90) {
		cout << BOLDWHITE << "Traveling around, you find a chest partially buried in the ground. Working to dig it out, and peering inside, you find some old--yet sturdy--armor. "
		     << "\"If nobody is around to claim it, may as well take it for myself.\"\n"
		     << "Defense +5!\n" << RESET;
		Player.defense += 5;
	}
	//Get a weapon (attackPwr +5). 10% chance.
	else if (diceRoll > 90 and diceRoll <= 100) {
		cout << BOLDWHITE << "A man runs up to you, out of the wilderness, asking, \"I don't have time to go into detail, but please! Take this sword and keep it safe!\"\n"
		     << "Taking the sword in your hands, you notice it's better than your current one. Might as well get some use out of it while your protecting it.\n"
		     << "Attack Power +5!\n" << RESET;
		Player.attackPwr += 5;
	}

	//Removes the point of interest from POI (and therefore, won't be reprinted to the screen when user returns to the map).
	POI.erase(currentPlayerRow);

	Utility_Press_E_To_Continue();

	Utility_Map_Settings();
}


//Basic arithmetic puzzle.
void Puzzle_One() {
	Utility_Text_Settings();

	unsigned short userInput = 0, puzzleAnswer = 18;

	cout << BOLDWHITE << "As you walk towards a wall of rock, you notice an entrance. Deciding to enter, you head into the bowels of the Earth.\n"
	     << "Inside, you find an ancient wall drawing, with images depicting a item appearing from the stone.\n"
	     << "This item seems to only be able to be accessed after solving a math problem.\n"
	     << "As you look around, something catches your eye. A math equation bleeds out from a dark and gloomy corner: \n\n"
	     << "    ""\"Solve the problem to pass the test: (5 * 2) (8 / 4) + 3 + 7 - 12\"""\n\n"
	     << "What do you believe the answer to be?\n" << RESET;
	cin >> userInput;

	//Reject user inputs that aren't valid and reprompt.
	while (userInput != puzzleAnswer) {
		//Clears cin's error flag when userInput is not an acceptable input.
		cin.clear();
		//Ignores user input if not a positive number.
		//numeric_limits<streamsize>::max() returns the max value for the type.
		//Backslash n is where the cin.ignore stops reading if reached before the numeric limit.
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << BOLDWHITE << "\nYou enter your answer and...nothing happens. It seems you were wrong.\n" << "Thinking again, what do you believe the answer is?\n" << RESET;
		cin >> userInput;
	}

	cout << BOLDWHITE << "\nAs you hear rock scraping against rock, it turns out your answer proved fruitful!\n" << "Walking over and peering into the box turns up an old key. I wonder what that's used for...\n" << RESET;

	//Keeps track of when puzzle has been completed.
	puzzleOneDone = true;

	Utility_Press_E_To_Continue();

	Utility_Map_Settings();
}

//Traditional riddle.
void Puzzle_Two() {
	Utility_Text_Settings();

	string userInput, puzzleAnswer = "newspaper";

	cout << BOLDWHITE << "Entering an old hut, you find a skeleton, surrounded by scraps of what appears to be paper.\n"
	     << "One of them appears legible, reading:\n\n"
	     << "    What is white, black, and red all over?\n\n"
	     << "Confused by the seemingly random question, you learn there's a basement that's locked.\n"
	     << "Unable to open it, you walk back to the piece of paper.\n" << """\"What's white, black, and red all over\""" you ponder.\n" << "Could it be a..." << RESET;
	cin >> userInput;

	//Convert userInput to lowercase for ease of checking.
	for (auto& ch : userInput) {
		ch = tolower(ch);
	}

	//Reject user inputs that aren't valid and reprompt.
	while (userInput != puzzleAnswer) {
		cin.clear();
		//Ignores user input if not a positive number.
		//numeric_limits<streamsize>::max() returns the max value for the type.
		//Backslash n is where the cin.ignore stops reading if reached before the numeric limit.
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << BOLDWHITE << "\nHmmm, no it couldn't be that. What about a..." << RESET;
		cin >> userInput;

		//Convert userInput to lowercase for ease of checking.
		for (auto& ch : userInput) {
			ch = tolower(ch);
		}
	}

	cout << BOLDWHITE << "\nA rumbling begins, and you notice the door behind you opens.\n" << "Walking down the appearing stairs, you find an old key wrapped in a cloth. I wonder what that's used for...\n" << RESET;

	//Keeps track of when puzzle has been completed.
	puzzleTwoDone = true;

	Utility_Press_E_To_Continue();

	Utility_Map_Settings();
}

//Door puzzle and Kerney fight.
void Puzzle_Three() {
	Utility_Text_Settings();

	string userInput, puzzleAnswer = "b";

	cout << BOLDWHITE << "Walking underneath the bridge, you find an alcove. Coming closer, you notice there's an old door.\n"
	     << "Becoming curious, you enter, down the long and winding stariwell.\n"
	     << "Entering a room, a slab of metal with engravings on it catches your eye. It's positioned that it's arrow engraving is pointing up.\n"
	     << "Picking it up, you ponder what a pretty penny it might be worth.\n"
	     << "Walking farther in, you notice this seems to be an old catacomb, with offering to the deceased still left behind.\n"
	     << "Exploring some more, you come up against a large door, seemingly impassible. The slab of metal you have looks like it might fit into the door.\n"
	     << "Do you choose to insert it top, bottom, left, or right? (t/b/l/r)\n" << RESET;

	cin >> userInput;

	while (userInput != puzzleAnswer) {
		//Clears cin's error flag when userInput is not an acceptable input.
		cin.clear();
		//Ignores user input if not a positive number.
		//numeric_limits<streamsize>::max() returns the max value for the type.
		//Backslash n is where the cin.ignore stops reading if reached before the numeric limit.
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << BOLDWHITE << "\nThat didn't work, try again. Do you choose to insert it top, bottom, left, or right first? (t/b/l/r)\n" << RESET;
		cin >> userInput;
	}

	cout << BOLDWHITE << "\nStanding stunnded, it actually works and the door begins to recede into the floor."
	     << "\nWalking in, you notice the place looks ransacked. Intrigued, you continue on until you find..."
	     << "\nWait! Is that Kerney? Is he the one who's been ransacking the place? Aghast, you go to confront him.\n" << RESET;

	//Go into combat with Kerney as the opponent...
	Game_Combat(Kerney);

	if (Kerney.health <= 0) { //If Kerney is defeated...
		string spareOrKill;

		cout << BOLDWHITE << "\nBesting Kerney in battle, you face him as he lies on the floor.\n"
		     << "You notice a key flat on the floor atop the pile of trinkets and ends Kerney was scavaging. Noticing it's similar to the other ones you found before, you take it.\n\n"
		     << "Facing back to Kerney, he asks you...\n\n" << RESET
		     << "Kerney: Well boy? You going to kill me?\n\n"
		     << BOLDWHITE << "   Will you spare or kill Kerney? (s/k)\n" << RESET;
		cin >> spareOrKill;

		//Reject user inputs that aren't valid and reprompt.
		while (spareOrKill != "s" and spareOrKill != "S" and spareOrKill != "k" and spareOrKill != "K") {
			//Clears cin's error flag when userInput is not an acceptable input.
			cin.clear();
			//Ignores user input if not a positive number.
			//numeric_limits<streamsize>::max() returns the max value for the type.
			//Backslash n is where the cin.ignore stops reading if reached before the numeric limit.
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> spareOrKill;
		}

		//If player wishes to kill Kerney...
		if (spareOrKill == "k" or spareOrKill == "K") {
			//Keep track of Kerney's aliveness.
			Kerney.isAlive = false;

			cout << "\nYou: I'll spare the world your torture.\n\n"
			     << "Kerney: So be it...\n";

			//Keeps track of when puzzle has been completed.
			puzzleThreeDone = true;

			Utility_Press_E_To_Continue();

			Utility_Map_Settings();

			return;
		} else { //Lore for if Kerney is alive. His living status isn't changed since by default the global variable tracking his life/death state is set to true.
			clearscreen();
			movecursor(0, 0);

			cout << BOLDWHITE << "Leaving the catacombs behind, you go back to the castle to talk to Mencarelli.\n\n\n" << RESET

			     << "You: Hey, I've been taking care of these traps and almost had Kerney. I spared him, so let's just hope he doesn't get any bright ideas.\n\n"
			     << "Mencarelli: Don't worry about that right now. Stallman came up to me and told me to tell you that he wants to meet you in the castle. I'm thining it's about Kerney.\n\n"
			     << BOLDWHITE << "\nSome time later...\n\n\n" << RESET
			     << "You: Prince Stallman you wanted to see me.\n\n"
			     << "Stallman: Yes, good to finally see you, I wanted to thank you on taking care of the traps throughout the kingdom.\n\n"
			     << "You: I had a chance to kill him, but didn't.\n\n"
			     << "Kerney: (Clears throat) Am I interupting an important conversation?\n\n"
			     << "Stallman: Kerney! What are you doing here? How did you get inside the castle?\n\n"
			     << "Kerney: Oh, I guess you have forgotten that I was once part of this royalty and know my way around.\n\n"
			     << "You: I won't let you get to Stallman!\n\n"
			     << "Kerney: Hahahaha, you are just a weak little warrior.\n\n"

			     << BOLDWHITE << "\nA battle ensues, leading with you being bested by Kerney, causing Stallman to be kidnapped.\n\n\n" << RESET

			     << "You: Mencarelli! Kerney took Stallman! I don't know where; oh lord he probably already killed him!\n\n"
			     << "Mencarelli: Don't jump to conclutions boy. When Kerney was exiled to the edges of the kingdom, he built a tower. He must be there, now go!\n\n";

			//Keeps track of when puzzle has been completed.
			puzzleThreeDone = true;

			Utility_Press_E_To_Continue();

			Utility_Map_Settings();

			return;
		}
	} else if (Player.health <= 0) { //Else if you die...
		Utility_Map_Settings();

		//Print "You Died" to screen, and have it fade out.
		for (int i = 256; i >= 0; i--) {
			clearscreen();
			movecursor(y + 3, x - 3);
			//Change color each run of the loop to make it look like it's fading out.
			setcolor(i, 0, 0);
			cout << "You Died\n";
			//Pauses the program for 10'000 usec.
			usleep(10'000);
		}
		movecursor(0, 0);

		cout << BOLDWHITE << "Waking up, you notice you're back at the castle.\n"
		     << "Must have been a dream, dying in a catacomb to Kerney.\n"
		     << "\"I still need to take care of that puzzle on the right side of the bridge...\", you think as you walk outside the castle.\n" << RESET;

		//Reset Player and Kerney health so user can try again.
		Player.health = 100;
		Kerney.health = 100;

		Utility_Press_E_To_Continue();
		return; //...returns you to map and can retry.
	}
}

//The "answer is completely random" puzzle.
void Puzzle_Four() {
	Utility_Text_Settings();

	string userInput;

	cout << BOLDWHITE << "Entering a run down home, you notice a space on the wall engraved with a puzzle.\n"
	     << "The puzzle reads: ""What does this spell? modnarsirewsnaeht""\n\n"
	     << "   A) The answer is random\n   B) The answer is random\n   C) The answer is random\n   D) The answer is random\n"
	     << "\nWhat do you think the answer is?\n" << RESET;
	cin >> userInput;

	//Picks a random number between 1 and 4 and checks whether the user chose the correct answer. Else reprompts.
	while (true) {
		int puzzleAnswer = (rand() % 4) + 1;

		if (puzzleAnswer == 1 and (userInput == "A" or userInput == "a")) break;
		else if (puzzleAnswer == 2 and (userInput == "B" or userInput == "b")) break;
		else if (puzzleAnswer == 3 and (userInput == "C" or userInput == "c")) break;
		else if (puzzleAnswer == 4 and (userInput == "D" or userInput == "d")) break;

		cout << BOLDWHITE << "\nPressing the button does nothing. You ponder if your answer is a bit too logical...\n" << RESET;

		//Clears cin's error flag when userInput is not an acceptable input.
		cin.clear();
		//Ignores user input if not a positive number.
		//numeric_limits<streamsize>::max() returns the max value for the type.
		//Backslash n is where the cin.ignore stops reading if reached before the numeric limit.
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> userInput;
	}

	cout << BOLDWHITE << "\nGetting the puzzle right, an old rickety bookshelf moves out of the way.\n"
	     << "Walking towards the bookshelf, you realize there's obviously a secret room inside.\n"
	     << "Looking around, you find nothing of interest besides an old key. I wonder what that's used for...\n" << RESET;

	//Keeps track of when puzzle has been completed.
	puzzleFourDone = true;

	Utility_Press_E_To_Continue();

	Utility_Map_Settings();
}

//HACKER-MAN!!!
void Puzzle_Five() {
	Utility_Text_Settings();

	string userInput, puzzleAnswer = "password";

	cout << BOLDWHITE << "A strange building resides next to the tower. Inside of it, you find a room full of...well, you're not quite sure.\n"
	     << "There are many long wirey things around, and the walls are covered in an ugly beige coloring, with outcroppings all around\n"
	     << "Looking around, you find what seems to be the centerpiece of the room, with a lot of things you can press. They move, so you decide to press them all to see what happens.\n"
	     << "Hitting one button in particular causes lights as bright as the sun to turn on. Panicking, you hide best you can in case someone comes.\n"
	     << "After a bit's hesitation, you step out and go to a thing that's displaying some words. Looking at it, it reads:\n\n"
	     << """Please enter your password:""\n\n" << "What do you think this ""\"password\""" might be?\n" << RESET;

	cin >> userInput;

	//Reject user inputs that aren't valid and reprompt.
	while (userInput != puzzleAnswer) {
		//Clears cin's error flag when userInput is not an acceptable input.
		cin.clear();
		//Ignores user input if not a positive number.
		//numeric_limits<streamsize>::max() returns the max value for the type.
		//Backslash n is where the cin.ignore stops reading if reached before the numeric limit.
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << BOLDWHITE << "\nWords come up that read:\n\n" << RED << "    ACCESS DENIED\n\n"
		     << BOLDWHITE << "As you figure you got it wrong, you try again. What do you think this ""password"" could be?\n" << RESET;
		cin >> userInput;
	}

	cout << BOLDWHITE << "\nAfter entering ""\"password\""" as the password, it reads:\n\n" << GREEN << "      ACCESS GRANTED\n   Welcome Hack-er-man!\n\n" << RESET
	     << BOLDWHITE << "At the same time that line of text appears, a drawer opens up, revealing an old key. I wonder what that's used for...\n" << RESET;

	//Keeps track of when puzzle has been completed.
	puzzleFiveDone = true;

	Utility_Press_E_To_Continue();

	Utility_Map_Settings();
}

void Tower_Sequence() {
	Utility_Text_Settings();

	string userInput;

	//If Kerney is alive...
	if (Kerney.isAlive) {
		cout << "You: Stallman, are you there?\n\n"
		     << "Stallman: Yes, I'm here. Don't worry about me.\n\n\n"
		     << BOLDWHITE << "Inserting each of the five keys you found earlier into the door, it unlocks.\n"
		     << "As you open the door to the tower and make your way inside, you eventually reach the top.\n\n\n" << RESET
		     << "You: There you are. What do you mean not to worry about you? I came all this way to save you and this what you say?\n\n"
		     << "Stallman: Yes, because I love Kerney and I'm going to be with him for the rest of my life.\n\n"
		     << "You: What is this nonsense? What spell have you put on Stallman, Kerney?\n\n"
		     << "Kerney: Oh boy you never learned. I have no spell on Stallman.\n\n"
		     << "You: Oh my god you both have lost your minds!\n\n"
		     << "Stallman: No we haven't. We're just in love. Isn't Kerney just the most handsomest-est?\n\n"

		     << BOLDWHITE << "\nDo you concur? (y/n)\n\n" << RESET;
		cin >> userInput;

		//Reject user inputs that aren't valid and reprompt.
		while (userInput != "yes" and userInput != "Yes" and userInput != "y" and userInput != "Y") {
			//Clears cin's error flag when userInput is not an acceptable input.
			cin.clear();
			//Ignores user input if not a positive number.
			//numeric_limits<streamsize>::max() returns the max value for the type.
			//Backslash n is where the cin.ignore stops reading if reached before the numeric limit.
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Stallman: Did I stutter?\n";
			cin >> userInput;
		}

		cout << "\nYou: Yes, he is the most handsomest-est.\n\n"
		     << "You: What in the? Why did I just say that? I'm getting the heck out of here!\n\n"
		     << BOLDWHITE << "Startled and unaware of why you just said that, you decide to flee the tower.\n\n" << RESET
		     << "Stallman: And make sure you lock the door behind you!\n";

		Utility_Press_E_To_Continue();
	} else { //Else if Kerney isn't alive...
		cout << "You: Stallman, are you there?\n\n"
		     << "Stallman: Yes I am here. I'm still locked up, though.\n\n"
		     << "You: Don't worry, I have the keys to get you out of here.\n\n"
		     << BOLDWHITE << "\nSlotting the keys into the keyholes in the door, it swings wide open. Racing up the tower, and beginning to run out of breath, you eventually reach Stallman's room.\n\n\n" << RESET
		     << "You: Okay now explain when in the world did Kerney have the time to kidnap you?\n\n"
		     << "Stallman: It was while you were out exploring. I suppose he snuck into the castle, and because he was a part of the nobility before being exiled, he knew his way around.\n"
		     << "		   But nevermind that! Kerney is gone now, and I'm safe. Thank you; now I must figure out how I can ever repay you.\n\n"

		     << BOLDWHITE << "Leaving the tower, with Stallman in tow, you arrive back at the castle near dusk...\n\n\n" << RESET
		     << "Mencarelli: My god Prince Stallman, are you alright?\n\n"
		     << "Stallman: Yes yes, I'm quite alright now.\n\n"
		     << BOLDWHITE << "\nCalmed by seeing Stallman scratchless, he brings you inside to be recognized as being a hero.\n"
		     << "A banquet full of every kind of food and drink commenced shortly thereafter. This surely wasn't a night you were likely to forget.\n"
		     << "Later that night...\n\n\n" << RESET

		     << "You: I must say Stallman, you are *quite* the expert...\n";

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
	cout << BOLDWHITE << endl << "Press E to continue" << RESET << endl;

	set_raw_mode(true);
	while (true) {
		int keyPress = quick_read();
		if (keyPress == 'e' or keyPress == 'E') break;
	}
}

//Used to save lines above where preventing clipping into buildings comes up a lot.
void Utility_Prevent_Clip(int &currentPlayerRow, int previousPlayerRow, int &currentPlayerCol, int previousPlayerCol) {
	currentPlayerRow = previousPlayerRow;
	currentPlayerCol = previousPlayerCol;
}
