#include "players.h"
#include <iostream>
#include <fstream>
#include <string.h>

int generate_Player_ID(unsigned n)
{
	std::ifstream file_p;
	file_p.open("players.dat", std::ios::binary);
	file_p.seekg(0, std::ios::end);
	int file_size = file_p.tellg();
	file_p.close();
	if (file_size < 132)
	{
		n = 1;
	}
	else
	{
		n = (file_size / 132) + 1;
	}
	return n;
}

void generate_Player(Player& player)
{
	std::ofstream file_p;
	file_p.open("players.dat", std::ios::binary | std::ios::app);
	std::cout << "Name, please: ";
	std::cin.getline(player.name, sizeof(player.name));
	file_p.write(player.name, sizeof(player.name));
	/*for (int i = 0; i < 128; i++)
	{
		player.name[i] = '\0';
	}*/
	player.ID = generate_Player_ID(player.ID);
	file_p.write((char*)(&player.ID), sizeof(player.ID));
	file_p.close();
	std::cin.clear();
	std::cin.sync();
}