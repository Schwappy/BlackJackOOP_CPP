//* * * * * * * * * * * * * * * * * * * * * * * //
//  Author:		Paul Schwappach					//
//	Professor:	George Sfakianakis				//
//	Class:		CSIS 297 - Intermediate C++		//
//	Assignment:	Semester Project				//
//	Date:		02/20/2016						//
//* * * * * * * * * * * * * * * * * * * * * * * //

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//
//	About Deck class (Header File)								//
//		This class makes an amount of decks (52 Card objects)	//
//	a user needs.  The deck shuffles, deals cards...			//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//
#ifndef BLACKJACKDECK_H
#define BLACKJACKDECK_H

// included libraries
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

class BlackJackDeck
{
private:
	std::vector<Card> deck;
	int numDecks;
	Card lastCard;


public:
	BlackJackDeck();
	BlackJackDeck(int);
	void deckBuilder(int decks);
	void shuffle();
	Card dealCard();
	void resetDeck();
	std::string deckState() const;
	std::string cLastCardDealt() const;

}; // ---------- end Deck class ----------
#endif
