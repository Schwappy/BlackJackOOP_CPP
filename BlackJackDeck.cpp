//* * * * * * * * * * * * * * * * * * * * * * * //
//  Author:	Paul Schwappach			//
// Professor:	George Sfakianakis		//
// Class:	CSIS 297 - Intermediate C++	//
// Assignment:	Semester Project		//
// Date:	02/20/2016			//
//* * * * * * * * * * * * * * * * * * * * * * * //

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//
// About Deck class:						//
// This class makes an amount of decks (52 Card objects)	//
// a user needs.  The deck shuffles, deals cards...		//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//

// included header files
#include "Card.h"
#include "BlackJackDeck.h"

//* * * * * * * * * * * * * * * * * * * * * * * *
// No-argument Constructor			*
//* * * * * * * * * * * * * * * * * * * * * * * *
BlackJackDeck::BlackJackDeck()
{
	shuffle();
	numDecks = 1;
	deckBuilder(numDecks);
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// Argument accepting Constructor		*
//* * * * * * * * * * * * * * * * * * * * * * * *
BlackJackDeck::BlackJackDeck(int numberDecks)
{
	numDecks = numberDecks;
	deckBuilder(numberDecks);
	shuffle();

}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
// deckBuilder() overload creates multiple decks of cards *
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void BlackJackDeck::deckBuilder(int decks)
{
	Card card;
	const int SUITS_MAX = 4;
	const int RANKS_MAX = 13;
	int suit = 0;
	int rank = 0;
	const char SUITS[SUITS_MAX] = {'S', 'D', 'C', 'H'};
	const char RANKS[RANKS_MAX] = {'2', '3', '4', '5', '6', '7',
		'8', '9', '0', 'J', 'Q', 'K', 'A'};


	for (int deckCount = 0; deckCount < decks; deckCount++)
	{
		for (int suit = 0; suit < SUITS_MAX; suit++)
		{
			for (int rank = 0; rank < RANKS_MAX; rank++)
			{
				card = Card(SUITS[suit], RANKS[rank]);
				deck.push_back(card);
			} // end for each rank
		} // end for each suit
	} // end for each deck
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// shuffle() shuffles deck for dealing a hand	*
//* * * * * * * * * * * * * * * * * * * * * * * *
void BlackJackDeck::shuffle()
{
	std::random_shuffle(deck.begin(), deck.end());
}


//* * * * * * * * * * * * * * * * * * * * * * * *
// dealCard() removes a card from the deck	*
//* * * * * * * * * * * * * * * * * * * * * * * *
Card BlackJackDeck::dealCard()
{
	if (deck.empty() == false)
	{
		lastCard = deck.back();
		deck.pop_back();
	}
	else
	{
		std::cout << "The deck is empty... reshuffling";
		resetDeck();
		lastCard = deck.back();
		deck.pop_back();
	}

	return lastCard;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// resetDeck discards all current cards in the	*
// deck and creates a fresh deck for a new round*
//* * * * * * * * * * * * * * * * * * * * * * * *
void BlackJackDeck::resetDeck()
{

	// clear the deck
	while(!deck.empty())
		deck.pop_back();

	// create new deck
	deckBuilder(numDecks);
	shuffle();
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// deckState returns the current deck's card	*
// states left inside the deck vector		*
//* * * * * * * * * * * * * * * * * * * * * * * *
std::string BlackJackDeck::deckState() const
{
	std::string outString = "[";
	int deckSize_less1 = deck.size() -1;
	int deckSize =  deck.size();
	const int ZERO = 0;
	// loop through vector to print it's contents
	// backwards to look like it deals from the top of the deck
	for (int count = deckSize_less1; count > ZERO; count--)
	{
		outString += deck[count].cardState();
		if (count != ZERO + 1)
			outString += ", ";
	}

	outString += "]\n\n\n";

	return "This deck currently contains: \n" + outString;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// cLastCardDealt returns the last card	that	*
// was dealt from the deck			*
//* * * * * * * * * * * * * * * * * * * * * * * *

std::string BlackJackDeck::cLastCardDealt() const
{
	return lastCard.cardState();
}
