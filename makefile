
CC=g++
CFLAGS=-g -lncurses
CFLAGSR= -O2 -lncurses
DEPS= main.cpp player.cpp system.cpp

#debug version
all: $(DEPS)
	$(CC) $^ $(CFLAGS) -o dungeon

#release version
release: $(DEPS) 
	$(CC) $^ $(CFLAGSR) -o dungeon

.PHONY: clean

clean: dungeon
	rm $^
