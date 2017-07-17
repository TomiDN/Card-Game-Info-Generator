#include "report.h"
#include <iostream>
#include <fstream>
#include <string.h>

int recorded_decks(unsigned n)
{
	std::ifstream file_d;
	file_d.open("decks.dat", std::ios::binary);
	file_d.seekg(0, std::ios::end);
	int file_size = file_d.tellg();
	file_d.close();
	n = (file_size / 248);
	return n;
}

void locateAndPrint_playerName(unsigned n)
{
	Player player;
	std::ifstream file_p;
	std::ofstream file_r;
	file_p.open("player.dat", std::ios::binary);
	unsigned m = 0;
	unsigned recPlayers = count_recorded_players(m);
	file_p.seekg(0, std::ios::beg);
	for (unsigned i = 0; i < recPlayers; i++)
	{
		file_p.seekg(128+132*i, std::ios::beg);
		file_p.read((char*)(&player.ID), sizeof(player.ID));
		if (player.ID == n)
		{
			file_p.seekg(-132, std::ios::cur);
			file_p.read(player.name, sizeof(player.name));
			file_p.close();
			file_r.open("report.txt", std::ios::app);
			file_r << "Owner: " << player.name;
			file_r.close();
			return;
		}
		file_p.seekg(0, std::ios::beg);
	}
}

void locateAndPrint_firstCard(unsigned n)
{
	Card card;
	std::ifstream file_c;
	std::ofstream file_r;
	file_c.open("cards.dat", std::ios::binary);
	unsigned m = 0;
	unsigned recCards = count_recorded_cards(m);
	file_c.seekg(0, std::ios::beg);
	for (unsigned i = 0; i < recCards; i++)
	{
		file_c.seekg(68+72*i, std::ios::cur);
		file_c.read((char*)(&card.ID), sizeof(card.ID));
		if (card.ID == n)
		{
			file_c.seekg(-68, std::ios::cur);
			file_c.read(card.name, sizeof(card.name));
			file_c.seekg(-68, std::ios::cur);
			file_c.read((char*)(&card.color), sizeof(card.color));
			file_c.close();
			file_r.open("report.txt", std::ios::app);
			file_r << " Card: " << card.name << " " << printColourName(card.color) << std::endl;
			file_r.close();
			return;
		}
		file_c.seekg(0, std::ios::beg);
	}
}

static const char* const printColourName(Colour& color)
{
	switch (color)
	{
	case Red: return "Red";
	case Black: return "Black";
	case Blue: return "Blue";
	case White: return "White";
	case Green: return "Green";
	}
}

void locate_colour(Colour& color)
{
	Deck deck;
	std::ifstream file_d;
	std::ofstream file_r;
	file_r.open("report.txt", std::ios::app);
	file_r << printColourName(color) << " ";
	file_r.close();
	file_d.open("decks.dat", std::ios::binary);
	unsigned n = 0;
	unsigned recDecks = recorded_decks(n);
	file_d.seekg(0, std::ios::beg);
	bool locatedColour;
	for (unsigned i = 0; i < recDecks; i++)
	{
		locatedColour = false;
		file_d.seekg(244 + 248*i, std::ios::beg);
		file_d.read((char*)(&deck.cards[i].color), sizeof(deck.cards[i].color));
		if (deck.cards[i].color == color)
		{
			locatedColour = true;
			file_d.seekg(-248, std::ios::cur);
			file_d.read((char*)(&deck.player.ID), sizeof(deck.player.ID));
			locateAndPrint_playerName(deck.player.ID);
			file_d.seekg(0, std::ios::cur);
			file_d.read((char*)(&deck.cards[i].ID), sizeof(deck.cards[i].ID));
			locateAndPrint_firstCard(deck.cards[i].ID);
		}
		file_d.seekg(0, std::ios::beg);
	}
	if (!locatedColour)
	{
		file_r.open("report.txt", std::ios::app);
		file_r << " " << std::endl;
		file_r.close();
	}
}

int most_Common_Card(int arr, int size)
{
	Deck deck;
	int commonCard = deck.cards[0].ID;
	int counter = 1;
	int firstCommonCounter;
	for (int i = 0; i < size; i++)
	{
		firstCommonCounter = 0;
		for (int j = 0; j < size; j++)
		{
			if (deck.cards[i].ID == deck.cards[j].ID)
			{
				firstCommonCounter++;
			}
		}
		if (firstCommonCounter > counter)
		{
			counter = firstCommonCounter;
			commonCard = deck.cards[i].ID;
		}
	}
	return commonCard;
}

void locateAndPrint_mostCommonCard(unsigned n)
{
	Card card;
	std::ifstream file_c;
	std::ofstream file_r;
	file_c.open("cards.dat", std::ios::binary);
	unsigned m = 0;
	unsigned recCards = count_recorded_cards(m);
	file_c.seekg(0, std::ios::beg);
	for (unsigned i = 0; i < recCards; i++)
	{
		file_c.seekg(68+72*i, std::ios::beg);
		file_c.read((char*)(&card.ID), sizeof(card.ID));
		if (card.ID == n)
		{
			file_c.seekg(-68, std::ios::cur);
			file_c.read(card.name, sizeof(card.name));
			file_c.close();
			file_r.open("report.txt", std::ios::app);
			file_r << "Most  common card: " << card.name << std::endl;
			file_r.close();
			return;
		}
		file_c.seekg(0, std::ios::beg);
	}
}

void printMostCommonCard()
{
	unsigned n = 0;
	unsigned recDecks = recorded_decks(n);
	int MAX_SIZE = recDecks*60;
	int* allCards = new int[MAX_SIZE];
	std::ifstream file_d;
	file_d.open("decks.dat", std::ios::binary);
	file_d.seekg(0, std::ios::beg);
	for (unsigned i = 0; i < recDecks; i++)
	{
		file_d.seekg(4+248*i, std::ios::beg);
		for (int j = 0; j < 60; j++)
		{
			file_d.seekg(0, std::ios::cur);
			file_d.read((char*)(&allCards[j*i+i]), sizeof(int));
		}
		file_d.seekg(0, std::ios::beg);
	}
	file_d.close();
	int mostCommonID = most_Common_Card(allCards[MAX_SIZE], MAX_SIZE);
	locateAndPrint_mostCommonCard(mostCommonID);
	delete[]allCards;
}

void generate_Report()
{
	std::ofstream file_r;
	file_r.open("report.txt", std::ios::trunc);
	file_r << "Report: " << std::endl;
	file_r.close();
	Colour current = Unknown;
	for (current = Red; current <= Green; current = (Colour)(current + 1))
	{			
			locate_colour(current);
	}
	printMostCommonCard();
	std::cout << "The report is waiting for you in the folder. :)" << std::endl;
}