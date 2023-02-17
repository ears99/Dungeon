
/*
 * DUNGEON: A TEXT-BASED ROUGELIKE FOR THE LINUX TERMINAL 
 *
 * WRITTEN BY JACOB SEADORF ON JANUARY 18, 2023  
 */

#include <ncurses.h>
#include "player.h"
#include "system.h"

void processInput();

Player p;
System s;

int main() {
	s.init();
	mvprintw(p.y, p.x, "@");

	//move cursor to player position 
	move(p.y, p.x);
	refresh();

	processInput();
	getch();
	endwin();
	return 0;
}

void processInput() {

	while(1) {
		int dungeonLevel = 0;

		switch(int ch = getch()) {
		//key handling for player movement (arrow keys)
		case KEY_UP: 
			p.x += 0;
			p.y -= 1;
			mvprintw(p.y, p.x,"@");
			mvprintw(p.y+1, p.x, " ");
			move(p.y, p.x);
			s.turn += 1;
			move(p.y,p.x);
			refresh();
		break;
		case KEY_RIGHT: 
			p.x += 1;
			p.y += 0;
			mvprintw(p.y, p.x,"@");
			move(p.y, p.x);
			mvprintw(p.y, p.x-1, " ");
			s.turn += 1;
			move(p.y,p.x);
			refresh();
		break;
		case KEY_DOWN: 
			p.x += 0;
			p.y += 1;
			mvprintw(p.y, p.x, "@");
			mvprintw(p.y-1, p.x, " ");
			move(p.y, p.x);
			s.turn += 1;
			move(p.y,p.x);
			refresh();
		break;
		case KEY_LEFT:
			p.x -= 1;
			p.y += 0;
			mvprintw(p.y, p.x, "@");
			mvprintw(p.y, p.x+1, " ");
			move(p.y, p.x);
			s.turn += 1;
			move(p.y,p.x);
			refresh();
		break;

		//Inventory, equip and use keys
		
		//'i' -- inventory 
		case 105:  
			//save screen before opening inventory
			scr_dump("game");
			//display inventory
			clrtobot();
			mvprintw(0, 0, "===============");
			mvprintw(1, 0, "===INVENTORY===");
			mvprintw(2, 0, "===============");
			
			//print "item" as a test
			for(int i = 3; i < 20; i++){
				mvprintw(i, 3, "Item");
				refresh();
			}

			mvprintw(38, 0, "e - equip, d - drop, i - info, Space - return");
				//inventory key processing
				switch(int ch = getch()) {
					case 32: //space -- return to the game
						clrtobot();
						scr_restore("game");
						move(p.y, p.x);
						refresh();
					break;
					
					case 100: //'d' -- drop an item
						move(38, 0);
						clrtoeol();
						mvprintw(38, 0, "Drop what item?");
						getch();
						clrtobot();
						scr_restore("game");
						move(p.y,p.x);
						refresh();
					break;
					
					case 101: //'e' -- equip an item
						move(38, 0);
						clrtoeol();
						mvprintw(38, 0, "Equip what item?");
						getch();
						clrtobot();
						scr_restore("game");
						move(p.y, p.x);
						refresh();
					break;
				}
					
			refresh();	
			getch();
		break;

		//'q' -- drink ("quaff") a potion
		case 113: 
			move(0,0);
			clrtoeol();
			mvprintw(0,0,"Drinking placeholder");
			move(p.y, p.x);
			refresh();
		break;

		//'>' -- go down a level	
		case 62: 
			move(0,0);
			clrtoeol();
			if(dungeonLevel > -1) {
				dungeonLevel++;
				mvprintw(0,0, "Dungeon Level: %d", dungeonLevel);
				move(p.y, p.x);
				refresh();
			}
		break;

		//'<' -- go up a level (if on the top level, leave the dungeon)
		case 60:
			move(0,0);
			clrtoeol();
			dungeonLevel--;
			//check if on the top (first) level of the dungeon
			if(dungeonLevel == -1) {
				mvprintw(0, 0, "You have exited the dungeon.");	
				move(p.y, p.x);
				getch();
			} else {
				mvprintw(0,0,"Dungeon Level: %i", dungeonLevel);
				move(p.y, p.x);
				refresh();
			}
		break;

		//'@' -- display character sheet
		case 64: 
			scr_dump("game");
			move(0,0);
			clrtobot();
			mvprintw(0,0, "======================");
			mvprintw(1,0, "===CHARACTER SHEET====");
			mvprintw(2,0,"======================");
			mvprintw(3,0,"HEALTH: %d", p.hp);
			mvprintw(4,0,"MANA: %d", p.mp);
			mvprintw(5,0,"LEVEL: %d", p.level);
			mvprintw(6,0,"Press any key to return...");
			getch();
			clrtobot();
			scr_restore("game");
			refresh();
		break;
		

		//'f' -- throw a throwable item
		case 102: 
			move(0,0);
			clrtoeol();
			mvprintw(0,0,"Throw an item");
			move(p.y, p.x);
			refresh();
		break;

		//';' -- look around the map
		case 59:
			move(0,0);
			clrtoeol();
			mvprintw(0, 0, "Look around the map");
			move(p.y, p.x);
			refresh();
		break;

		//any other unmapped key
		default: 
			move(0,0);
			clrtoeol();
			mvprintw(0,0, "What?");
			move(p.y, p.x);
			refresh();
		break;
			}
		}
	}
