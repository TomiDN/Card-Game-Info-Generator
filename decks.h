#ifndef _DECKS_HEADER_INCLUDED_
#define _DECKS_HEADER_INCLUDED_

#include "players.h"
#include "cards.h"
#include <iostream>
#include <fstream>
#include <string.h>

struct Deck
{
	Player player;
	Card cards[60];
	Colour deckColour;
};

int count_recorded_players(unsigned n);

int count_recorded_cards(unsigned n);

Colour deck_colour(Colour& deckColour);

void generate_Deck(Deck& arr);

#endif
