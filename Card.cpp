//* * * * * * * * * * * * * * * * * * * * * * * //
// Author:	Paul Schwappach			//
// Professor:	George Sfakianakis		//
// Class:	CSIS 297 - Intermediate C++	//
// Assignment:	Semester Project		//
// Date:	02/08/2016			//
//* * * * * * * * * * * * * * * * * * * * * * * //

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//
//  About Card class:						//
//	The card class allows the creation of a single card	//
// that can be then used by it's subclasses.  A Deck class,	//
// for example, is a collection of cards that can be shuffled	//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//

// included header files
#include "Card.h"

//* * * * * * * * * * * * * * * * * * * * * * * *
// No-argument accepting Constructor		*
//* * * * * * * * * * * * * * * * * * * * * * * *

Card::Card()
{
	suit = 'S';
	rank = 'A';
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// Argument accepting Constructor		*
//* * * * * * * * * * * * * * * * * * * * * * * *
Card::Card(char s, char r)
{
	suit = s;
	rank = r;
}


//* * * * * * * * * * * * * * * * * * * * * * * *
// setSuit sets the suit of a card object	*
//* * * * * * * * * * * * * * * * * * * * * * * *

void Card::setSuit(char s)
{
	suit = s;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// setRank sets the rank of a card object	*
//* * * * * * * * * * * * * * * * * * * * * * * *

void Card::setRank(char r)
{
	rank = r;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getSuit returns the rank of a card object	*
//* * * * * * * * * * * * * * * * * * * * * * * *

char Card::getSuit() const
{
	return suit;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getRank returns the rank of a card object	*
//* * * * * * * * * * * * * * * * * * * * * * * *

char Card::getRank() const
{
	return rank;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// cardState returns the current card's suit	*
// and rank to the console in the form of "SA"	*
//* * * * * * * * * * * * * * * * * * * * * * * *

std::string Card::cardState() const
{
	char card[2];
	card[0] = getRank();
	card[1] = getSuit();

	std::string state(card, 2);

	return state;
}
