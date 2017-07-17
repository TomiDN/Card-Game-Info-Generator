#ifndef _PLAYERS_HEADER_INCLUDED_
#define _PLAYERS_HEADER_INCLUDED_

#include <iostream>
#include <fstream>
#include <string.h>

struct Player
{
	char name[128];
	unsigned ID;
};

int generate_Player_ID(unsigned n);

void generate_Player(Player& player);

#endif

