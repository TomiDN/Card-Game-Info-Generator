#include "decks.h"
#include <iostream>
#include <fstream>
#include <string.h>

int count_recorded_cards(unsigned n)
{
	std::ifstream file_c;
	file_c.open("cards.dat", std::ios::binary);
	file_c.seekg(0, std::ios::end);
	int file_size = file_c.tellg();
	file_c.close();
	n = (file_size / 72);
	return n;
}

int count_recorded_players(unsigned n)
{
	std::ifstream file_p;
	file_p.open("players.dat", std::ios::binary);
	file_p.seekg(0, std::ios::end);
	int file_size = file_p.tellg();
	file_p.close();
	n = (file_size / 132);
	return n;
}

Colour deck_colour(Colour& deckColour)
{
	Deck deck;
	deckColour  = deck.cards[0].color;
	int counter = 1;
	int firstCommonCounter;
	for (int i = 0; i < 60; i++)
	{
		firstCommonCounter = 0;
		for (int j = 0; j < 60; j++)
		{
			if (deck.cards[i].color == deck.cards[j].color)
			{
				firstCommonCounter++;
			}
		}
		if (firstCommonCounter > counter)
		{
			counter = firstCommonCounter;
			deckColour = deck.cards[i].color;
		}
	}
	return deckColour;
}

void generate_Deck(Deck& deck)
{
	std::ofstream file_d;
	std::ifstream file_p;
	std::ifstream file_c;
	Player player;
	Card card;
	unsigned n = 0;
	unsigned recPlayers = count_recorded_players(n);
	file_p.open("players.dat", std::ios::binary);
	std::cout << "Owners name: ";
	std::cin.getline(player.name, sizeof(player.name));
	file_p.seekg(0, std::ios::beg);
	for (unsigned i = 0; i < recPlayers; i++)
	{
		file_p.seekg(0 + 132*i, std::ios::beg);
		file_p.read(deck.player.name, sizeof(deck.player.name));
		if (strcmp(player.name, deck.player.name) == 0)
		{
			std::cout << "Got it!" << std::endl;
			file_p.seekg(0, std::ios::cur);
			file_p.read((char*)(&deck.player.ID), sizeof(deck.player.ID));
			file_p.close();
			file_d.open("decks.dat", std::ios::binary | std::ios::app);
			file_d.write((char*)(&deck.player.ID), sizeof(deck.player.ID));
			file_d.close();
			break;
		}
		file_p.clear();
		file_p.seekg(0, std::ios::beg);
	}
	if (strcmp(player.name, deck.player.name) != 0)
	{
		std::cout << "Invalid Player! Your attempt at creating a deck has failed." << std::endl;
		file_p.close();
		return;
	}
	std::cin.clear();
	std::cin.sync();
	unsigned recCards = count_recorded_cards(n);
	file_c.open("cards.dat", std::ios::binary);
	file_c.seekg(0, std::ios::beg);
	for (int i = 0; i < 60; i++)
	{
		std::cout << "Your number " << i+1 << " card: ";
		std::cin.getline(card.name, 63);
		for (unsigned j = 0; j < recCards; j++)
		{
			file_c.seekg(4, std::ios::cur);
			file_c.read(deck.cards[i].name, sizeof(deck.cards[i].name));
			if (strcmp(card.name, deck.cards[i].name) == 0)
			{
				std::cout << "Got it!" << std::endl;
				file_c.seekg(0, std::ios::cur);
				file_c.read((char*)(&deck.cards[i].ID), sizeof(deck.cards[i].ID));
				file_c.seekg(-72, std::ios::cur);
				file_c.read((char*)(&deck.cards[i].color), sizeof(deck.cards[i].color));
				file_d.open("decks.dat", std::ios::binary | std::ios::app);
				file_d.write((char*)(&deck.cards[i].ID), sizeof(deck.cards[i].ID));
				file_d.close();
				break;
			}
			else
			{
				file_c.seekg(4, std::ios::cur);
			}
		}
		if (strcmp(card.name, deck.cards[i].name) != 0)
		{
			std::cout << "Invalid Card! Your attempt at creating a deck has failed." << std::endl;
			file_c.close();
			return;
		}
		file_c.seekg(0, std::ios::beg);
		std::cin.clear();
		std::cin.sync();
	}
	file_c.close();
	file_d.open("decks.dat", std::ios::binary | std::ios::app);
	deck.deckColour = deck_colour(deck.cards[60].color);
	file_d.write((char*)(&deck.deckColour), sizeof(deck.deckColour));
	file_d.close();
}
