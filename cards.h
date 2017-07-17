#ifndef _CARDS_HEADER_INCLUDED_
#define _CARDS_HEADER_INCLUDED_

#include <iostream>
#include <fstream>
#include <string.h>

enum Colour
{
	Unknown, Red , Black , Blue, White, Green,
};

struct Card
{
	char name[64];
	unsigned ID;
	Colour color;
};

Colour colourValidation(char s[6]);

int generate_Card_ID(unsigned n);

void generate_Card(Card& card);

#endif
