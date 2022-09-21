#include <iostream>
#include <unistd.h>
#include "/public/colors.h"
using namespace std;



void Interactable_Map() {
	//Defines the "playable" area (as big as screen size) and prints map out.
	const auto [ROWS, COLS] = get_terminal_size(); //FIXME: Change to vector later.
	cout << ROWS << " " << COLS << endl;

	//FIXME: Not sure what this is for or if it's necessary.
	int x = COLS / 2;
	int y = ROWS / 2;

	set_raw_mode(true); //Nonblocking I/O

	//In order to navigate the map, infinite loop must be used until quit signal (Q or q) is sent.
	while (true) {
		set_cursor_mode(false);
		//Stores the key pressed on the keyboard.
		int keyPress = quick_read();

		//If quit signal is sent, quit.
		if (keyPress == 'Q' or keyPress == 'q') break;
		//Else move the /*Something here*/ where on the screen they want.
		if (keyPress == UP_ARROW) y--;
		if (keyPress == DOWN_ARROW) y++;
		if (keyPress == LEFT_ARROW) x--;
		if (keyPress == RIGHT_ARROW) x++;

		//Prevents user from moving offscreen.
		y = clamp(y, 0, ROWS);
		x = clamp(x, 0, COLS);
		clearscreen();
		movecursor(y, x);
		cout << "test" << endl;

		//Prevents lagging the server by only taking input every 10,000 microseconds (or every 0.01 seconds).
		usleep(10000);
	}

	set_raw_mode(false); //Sets raw mode to false so constant input isn't recorded.
	resetcolor(); //Clears colors of map.
	set_cursor_mode(true); //FIXME: Not sure if this is needed.
	clearscreen(); //Reset screen size so map goes away.
}

int main() {

	//Test to see if map works.
	int test_for_map = 0;
	cout << "1 for map, 0 for no map: ";
	cin >> test_for_map;
	if (test_for_map == 1) Interactable_Map();

	//I'm thinking we should try to have main be a driver program, with
	//functions that carry out the majority of the program.
	//This will make it far easier to test our own codes independantly.
	//Not everything will need a function (such as dialogue), but at least for
	//the map, dungeon/puzzles, etc. it'll be a good idea.

}
