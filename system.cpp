#include "system.h"

System::System() {
	init();
}

System::~System() {}

void System::init() {
	initscr();
	cbreak();
	noecho();
	start_color();
	keypad(stdscr, true);
}
