#include <iostream>
#include <unistd.h>
#include "/public/colors.h"
using namespace std;

//30 x 20 map. FIXME: Fill in later.
vector<string> worldMap = {
	"******************************",
	"*                    t       *",
	"*  t                t  tt    *",
	"*               t t          *",
	"*                            *",
	"*                            *",
	"*                 t          *",
	"*       t                    *",
	"*         t       t          *",
	"*          t      t          *",
	"*            t t t           *",
	"*               t            *",
	"*             t              *",
	"*          t t               *",
	"*        t         tt        *",
	"*     t t           t        *",
	"*   t                t       *",
	"*  t                 t       *",
	"*                     t      *",
	"*                            *",
	"*                            *",
	"******************************",
};


void Draw_Map(int rowSize, int colSize) {
	clearscreen();
	movecursor(0, 0);
	for (size_t row = 0; row <= rowSize; row++) {
		for (size_t col = 0; col <= colSize; col++) {
			if (row == //FIXME and col == //FIXME) cout << "P";
			else cout << worldMap.at(row).at(col);
		}
		cout << endl;
	}
}

void Get_Player_Location() {
	//TODO:
}


int main() {
	const int rowSize = worldMap.size() - 1, colSize = worldMap.at(rowSize).size() - 1;

	Draw_Map(rowSize, colSize);



	//I'm thinking we should try to have main be a driver program, with
	//functions that carry out the majority of the program.
	//This will make it far easier to test our own codes independantly.
	//Not everything will need a function (such as dialogue), but at least for
	//the map, dungeon/puzzles, etc. it'll be a good idea.

}


/*
void Interactable_Map() {
	//Defines the playable area (as big as screen size) and prints map out.
	vector<vector<int>> [ROWS, COLS] = get_terminal_size();
// 	const auto [ROWS, COLS] = get_terminal_size();
	cout << ROWS << " " << COLS << endl;

	//Sets x and y to middle of the screen.
	int x = COLS / 2;
	int y = ROWS / 2;

	//Nonblocking I/O
	set_raw_mode(true);

	//In order to navigate the map, infinite loop must be used until quit signal (Q or q) is sent.
	while (true) {
		set_cursor_mode(false);
		//Stores the key pressed on the keyboard.
		int keyPress = quick_read();

		//If quit signal is sent, quit.
		if (keyPress == 'Q' or keyPress == 'q') break;
		//Else move the *Something here* where on the screen they want.
		if (keyPress == UP_ARROW) y--;
		if (keyPress == DOWN_ARROW) y++;
		if (keyPress == LEFT_ARROW) x--;
		if (keyPress == RIGHT_ARROW) x++;

		//Prevents user from moving offscreen.
		y = clamp(y, 0, ROWS);
		x = clamp(x, 0, COLS);
		clearscreen();
		movecursor(y, x);
		cout << CYAN << "test" << endl;

		//Prevents lagging the server by only taking input every 10,000 microseconds (or every 0.01 seconds).
		usleep(10000);
	}

	set_raw_mode(false); //Sets raw mode to false so constant input isn't recorded.
	resetcolor(); //Clears colors of map.
	set_cursor_mode(true); //Brings cursor back.
	clearscreen(); //Reset screen size so map goes away.
}*/
