#ifndef _REPORT_HEADER_INCLUDED_
#define _REPORT_HEADER_INCLUDED_

#include "cards.h"
#include "decks.h"
#include "players.h"
#include <iostream>
#include <fstream>
#include <string.h>

int recorded_decks(unsigned n);

void locateAndPrint_playerName(unsigned n);

void locateAndPrint_firstCard(unsigned n);

int most_Common_Card(int arr);

void locateAndPrint_mostCommonCard(unsigned n);

void printMostCommonCard();

static const char* const printColourName(Colour& color);

void locate_colour(Colour& color);

void generate_Report();

#endif