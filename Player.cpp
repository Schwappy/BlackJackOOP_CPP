//* * * * * * * * * * * * * * * * * * * * * * * //
//  Author:		Paul Schwappach					//
//	Professor:	George Sfakianakis				//
//	Class:		CSIS 297 - Intermediate C++		//
//	Assignment:	Semester Project				//
//	Date:		02/25/2016						//
//* * * * * * * * * * * * * * * * * * * * * * * //

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//
//	About Player class:											//
//		This class allows the user to perform actions on their	//
//	hand of cards according to the rules of Black Jack.			//
//  Hit, stand, double, split.									//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//

// included header files
#include "Card.h"
#include "BlackJackDeck.h"
#include "Player.h"

//* * * * * * * * * * * * * * * * * * * * * * * *
// No-argument Constructor						*
//* * * * * * * * * * * * * * * * * * * * * * * *
Player::Player()
{ }

//* * * * * * * * * * * * * * * * * * * * * * * *
// setBJ() sets hasBlackJack					*
//* * * * * * * * * * * * * * * * * * * * * * * *
void Player::setBJ()
{
	if (hand.getValue() == 21 && hand.getSize() == 2)
		hasBlackJack = true;
	else
		hasBlackJack = false;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getBJ() returns if Player has BJ				*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool Player::getBJ()
{
	return hasBlackJack;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// hit() adds a card to userHand				*
//* * * * * * * * * * * * * * * * * * * * * * * *
void Player::hit(BlackJackDeck &deck)
{
	hand.addCard(deck);
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// stand() finishes userHand					*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool Player::stand() const
{
	return true;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// showHand() display current hand state		*
//* * * * * * * * * * * * * * * * * * * * * * * *
std::string Player::showHand() const
{
	std::string outString = "";
	outString += "The hand contains: \n";
	outString += hand.handState();
	return outString;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// operator > overlaods to check hand values	*
// does *this player have a hand of more value	*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool Player::operator > (const Player &pRight)
{
	bool status;
	
	if (hand.getValue() > pRight.hand.getValue())
		status = true;
	else
		status = false;

	return status;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// operator >= overlaods to check hand values	*
// does *this player have a hand of more value	*
// or equal value								*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool Player::operator >= (const Player &pRight)
{
	bool status;
	
	if (hand.getValue() > pRight.hand.getValue())
		status = true;
	else if (hand.getValue() == pRight.hand.getValue())
		status = true;
	else
		status = false;

	return status;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// operator < overlaods to check hand values	*
// does *this player have a lower value			*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool Player::operator < (const Player &pRight)
{
	bool status;
	
	if (hand.getValue() < pRight.hand.getValue())
		status = true;
	else
		status = false;

	return status;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// operator <= overlaods to check hand values	*
// does *this player have a lower value	or		*
// equal value									*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool Player::operator <= (const Player &pRight)
{
	bool status;
	
	if (hand.getValue() > pRight.hand.getValue())
		status = true;
	else if (hand.getValue() == pRight.hand.getValue())
		status = true;
	else
		status = false;

	return status;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// operator == overlaods to check hand values	*
// does *this player have an equal hand value	*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool Player::operator == (const Player &pRight)
{
	bool status;
	
	if (hand.getValue() == pRight.hand.getValue())
		status = true;
	else
		status = false;

	return status;
}