#include "report.h"
#include "players.h"
#include "cards.h"
#include "decks.h"
#include <iostream>
#include <fstream>
#include <string.h>

int main()
{
	Player player;
	Card card;
	Deck deck;
	unsigned n = 0;
	std::ifstream file_p("players.dat", std::ios::binary | std::ios::app);
	std::ifstream file_c("cards.dat", std::ios::binary | std::ios::app);
	std::ifstream file_d("decks.dat", std::ios::binary | std::ios::app);
	
	if (!file_p || !file_c || !file_d)
	{
		std::cerr << "Problem with one of the files!" << std::endl;
	}
	else
	{
		while (true)
		{
			char command[7];
			std::cout << "Your command, please: ";
			std::cin.getline(command, sizeof(command));
			if (strcmp(command, "cc") == 0)
			{
				int cards = count_recorded_cards(n);
				if (cards == 32768)
				{
					std::cout << "Enough! The program can't handle so many magical creatures!" << std::endl;
					break;
				}
				else
				{
					generate_Card(card);
				}
			}
			else if (strcmp(command, "cp") == 0)
	 		{
				int players = count_recorded_players(n);
				if (players == 32768)
				{
					std::cout << "Stop! The program can't sustain so many enchanterers!" << std::endl;
					break;
				}
				else
				{
					generate_Player(player);
				}
			}
			else if (strcmp(command, "cd") == 0)
	 		{
				int size1 = count_recorded_cards(n);
				int size2 = count_recorded_players(n);
				if ((size1 == 0) || (size2 == 0))
				{
					std::cout << "Sorry, you dont have the assets to create a deck." << std::endl;
					break;
				}
				else
				{
					generate_Deck(deck);
				}
	 		}
			else if (strcmp(command, "report") == 0)
			{
				int size = recorded_decks(n);
				if (size == 0)
				{
					std::cout << "No decks in store to make a report!" << std::endl;
					break;
				}
				else
				{
					generate_Report();
					break;
				}
	 		}
			else
			{
				std::cout << "Invalid command!" << std::endl;
				break;
			}
			std::cin.clear();
			std::cin.sync();
		}
	}
	file_p.close();
	file_c.close();
	file_d.close();
	return 0;
}


