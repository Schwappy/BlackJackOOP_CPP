//* * * * * * * * * * * * * * * * * * * * * * * //
// Author:	Paul Schwappach			//
// Professor:	George Sfakianakis		//
// Class:	CSIS 297 - Intermediate C++	//
// Assignment:	Semester Project		//
// Date:	02/08/2016			//
//* * * * * * * * * * * * * * * * * * * * * * * //

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//
//  About Card class (header file)				//
//	The card class allows the creation of a single card	//
// that can be then used by it's subclasses.  A Deck class,	//
// for example, is a collection of cards that can be shuffled	//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//

#ifndef CARD_H
#define CARD_H

// included libraries
#include <string>

class Card
{
private:
	char suit;	// card suit
	char rank;	// card rank

public:
	Card();
	Card(char, char);	// Constructor
	//~Card();		// Destructor
	void setSuit(char);	// Mutator
	void setRank(char);	// Mutator
	char getSuit() const;	// Accessor
	char getRank() const;	// Accessor
	std::string cardState() const;	// Accessor
}; // ---------- end Card class ----------
#endif
