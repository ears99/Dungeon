#ifndef SYSTEM_H
#define SYSTEM_H

#include <ncurses.h>


class System {
public: 
	System();
	~System();
	void init();
	int turn;
	int curX, curY;
private: 

};

#endif
