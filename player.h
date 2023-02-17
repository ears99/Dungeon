#ifndef PLAYER_H
#define PLAYER_H
#include <ncurses.h>

typedef struct Item {
	const char* name;
	unsigned int modifier; 
	int itemNumber;
}item;


class Player {
public: 
	Player();
	~Player();
	//player postion
	int x; 
	int y;
	int hp; //health
	int mp; //mana for spells
	int level; //player level
	int xp; //experience points
	item inventory[36];	
private: 

};
#endif
