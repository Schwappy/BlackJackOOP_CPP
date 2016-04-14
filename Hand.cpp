//* * * * * * * * * * * * * * * * * * * * * * * //
//  Author:		Paul Schwappach					//
//	Professor:	George Sfakianakis				//
//	Class:		CSIS 297 - Intermediate C++		//
//	Assignment:	Semester Project				//
//	Date:		02/23/2016						//
//* * * * * * * * * * * * * * * * * * * * * * * //

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *//
//	About Hand class:											   //
//		This class creates a blackjack hand from a BlackJackDeck   //
//	object and has a method to get the value of a black jack hand  //
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	* *//

// included header files
#include "Card.h"
#include "BlackJackDeck.h"
#include "Player.h"



//* * * * * * * * * * * * * * * * * * * * * * * *
// No-argument Constructor						*
//* * * * * * * * * * * * * * * * * * * * * * * *
Player::Hand::Hand()
{
	setCardValues();
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// DEBUG Constructor							*
//* * * * * * * * * * * * * * * * * * * * * * * *
Player::Hand::Hand(int num)
{
	Card card = Card();
	hand[0] = card;
	hand[1] = card;
	setCardValues();
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// addCard() adds a card from BlackJackDeck		*
//* * * * * * * * * * * * * * * * * * * * * * * *
void Player::Hand::addCard(BlackJackDeck &deck)
{
	hand.push_back(deck.dealCard());
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// addCard() adds a card from split				*
//* * * * * * * * * * * * * * * * * * * * * * * *
void Player::Hand::addCard(Card &card)
{
	hand.push_back(card);
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// setCardValues() adds a card from split		*
//* * * * * * * * * * * * * * * * * * * * * * * *
void Player::Hand::setCardValues()
{
	// set values for each rank
	cardValues['A'] = 1;
	cardValues['2'] = 2;
	cardValues['3'] = 3;
	cardValues['4'] = 4;
	cardValues['5'] = 5;
	cardValues['6'] = 6;
	cardValues['7'] = 7;
	cardValues['8'] = 8;
	cardValues['9'] = 9;
	cardValues['0'] = 10;
	cardValues['J'] = 10;
	cardValues['Q'] = 10;
	cardValues['K'] = 10;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getValue() returns the value of the hand		*
//		This method handles the logic of using	*
//		an Ace in the hand (1 or 11value)		*
//* * * * * * * * * * * * * * * * * * * * * * * *
int Player::Hand::getValue() const
{
	int handValue = 0;
	char rank = ' ';
	int handSize = hand.size();
	bool hasAce = false;

	// determine the value of the hand
	for (int count = 0; count < handSize; count++)
	{
		// get rank from Card class
		rank = hand[count].getRank();

		if (rank == 'A')
				hasAce = true;

		// use rank to determine card's value
		handValue += cardValues.find(rank)->second;
	} // end for loop

	// determine if an Ace will be 1 or 11
	if(hasAce) // outer
	{
		if (handValue + 10 <= 21) // inner
		{
			handValue += 10;
		} // end inner if
	} // end outer if

	return handValue;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getSize() returns the number of Card objects	*
// contained in the hand						*
//* * * * * * * * * * * * * * * * * * * * * * * *
int Player::Hand::getSize() const
{
	return hand.size();
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// sameRank() checks initial hand to see if the *
// two Cards are the rank						*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool Player::Hand::sameRank() const
{
	bool sameRank;
	int size = hand.size();
	char card1Rank = ' ';

	if (size > 2 || hand[0].getRank() != hand[1].getRank())
		sameRank = false;
	else
		sameRank = true;

	return sameRank;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// card2IsAce() checks initial hand to see if	*
// the second Cards is an ace					*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool Player::Hand::card2IsAce() const
{
	bool isAce = false;
	int size = hand.size();

	if (size == 2 && hand[1].getRank() == 'A')
		isAce = true;

	return isAce;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// removeCard() removes a card from the hand	*
//* * * * * * * * * * * * * * * * * * * * * * * *
Card Player::Hand::removeCard()
{
	Card card;
	card = hand.back();
	hand.pop_back();
	return card;
}

//* * * * * * * * * * * * * * * * * * * * * * * * * *
// hasBusted() checks to see if the hand is over 21	*
//* * * * * * * * * * * * * * * * * * * * * * * * * *
bool Player::Hand::hasBusted() const
{
	bool busted;

	if (getValue() > 21)
	{
		busted = true;
	}
	else
		busted = false;
	return busted;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// handState() returns the current hand's card	*
// states within the hand						*
//* * * * * * * * * * * * * * * * * * * * * * * *
std::string Player::Hand::handState() const
{
	std::string outString = "[";
	int handSize_less1 = hand.size() -1;
	int handSize = hand.size();

	// loop through hand to add a card object
	// state to the outString
	for (int count = 0; count < handSize; count++)
	{
		outString += hand[count].cardState();
		if (count != handSize_less1)
		{
			outString += ", ";
		}
	}
	outString += "]\n";

	return outString;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// dealerHandState() returns the dealers hand	*
// state with 1 card hidden						*
//* * * * * * * * * * * * * * * * * * * * * * * *
std::string Player::Hand::dealerHandState() const
{
	std::string outString = "[XX, ";
	outString += hand[1].cardState();
	outString += "]\n\n";

	return outString;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// operator - overload removes a card from the	*
// this Hand object and adds it to another hand	*
//* * * * * * * * * * * * * * * * * * * * * * * *
void Player::Hand::operator - (Hand &splitHand)
{
	splitHand.addCard(removeCard());
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// operator + overload removes a card from the	*
// BlackJackDeck object and adds it to the hand	*
//* * * * * * * * * * * * * * * * * * * * * * * *
 void Player::Hand::operator + (BlackJackDeck &deckRight)
{
	hand.push_back(deckRight.dealCard());
}