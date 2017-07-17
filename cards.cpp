#include "cards.h"
#include <iostream>
#include <fstream>
#include <string.h>

Colour colorValidation(char s[6])
{
	if ((strcmp(s, "Red") == 0) || (strcmp(s, "red") == 0))
		return Red;
	else if ((strcmp(s, "Black") == 0) || (strcmp(s, "black") == 0))
		return Black;
	else if ((strcmp(s, "Blue") == 0) || (strcmp(s, "blue") == 0))
		return Blue;
	else if ((strcmp(s, "White") == 0) || (strcmp(s, "white") == 0))
		return White;
	else if ((strcmp(s, "Green") == 0) || (strcmp(s, "green") == 0))
		return Green;
	else
		return Unknown;
}

int generate_Card_ID(unsigned n)
{
	std::ifstream file_c;
	file_c.open("cards.dat", std::ios::binary);
	file_c.seekg(0, std::ios::end);
	int file_size = file_c.tellg();
	file_c.close();
	if (file_size < 72)
	{
		n = 1;
	}
	else
	{
		n = (file_size / 72) + 1;
	}
	return n;
}

void generate_Card(Card& card)
{
	std::ofstream file_c;
	char color[6];
	file_c.open("cards.dat", std::ios::binary | std::ios::app);
	std::cout << "Colour, please: ";
	std::cin.getline(color, 6);
	card.color = colorValidation(color);
	if (card.color == Unknown)
	{
		std::cout << "Error!" << std::endl;
		file_c.close();
		return;
	}
	file_c.write((char*)(&card.color), sizeof(card.color));
	std::cout << "Name, please: ";
	std::cin.getline(card.name, sizeof(card.name));
	file_c.write(card.name, sizeof(card.name));
	/*for (int i = 0; i < 64; i++)
	{
		card.name[i] = '\0';
	}*/
	card.ID = generate_Card_ID(card.ID);
	file_c.write((char*)(&card.ID), sizeof(card.ID));
	file_c.close();
	std::cin.clear();
	std::cin.sync();
}