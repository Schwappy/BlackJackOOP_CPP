//* * * * * * * * * * * * * * * * * * * * * * * //
//  Author:		Paul Schwappach					//
//	Professor:	George Sfakianakis				//
//	Class:		CSIS 297 - Intermediate C++		//
//	Assignment:	Semester Project				//
//	Date:		03/04/2016						//
//* * * * * * * * * * * * * * * * * * * * * * * //

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//
//	About Dealer class											//
//		This class inherits from the Player class and is		//
//	controlled by the game state to perform it's actions on		//
//	it's hand of cards according to the rules of Black Jack		//
//	for a dealer												//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//

// included header files
#include "Card.h"
#include "BlackJackDeck.h"
#include "Player.h"
#include "Dealer.h"
#include "User.h"

//* * * * * * * * * * * * * * * * * * * * * * * *
// finishRound() completes the hand for the		*
// dealer as per the rules of blackjack			*
//* * * * * * * * * * * * * * * * * * * * * * * *
void Dealer::finishRound(BlackJackDeck &deck, int userValue)
{
	const int DEALER_STAND_VALUE = 17;
	const int BUSTED = 21;
	int dVal;
	bool stand = false;

	do {
		dVal = hand.getValue();
		if (dVal >= DEALER_STAND_VALUE || dVal > BUSTED || dVal > userValue)
			stand = true;

		if (!stand)
			hand.addCard(deck);

	} while(!stand);
}


//* * * * * * * * * * * * * * * * * * * * * * * *
// concealHand() displays the dealer's hand but	*
// hides the first card.						*
//* * * * * * * * * * * * * * * * * * * * * * * *
std::string Dealer::concealHand() const
{
	std::string outString = "";
	outString += "The dealer is showing \n";
	outString += hand.dealerHandState();
	return outString;
}

//* * * * * * * * * * * * * * * * * * * * * * * * * *
// showHand() display current dealers' hand state	*
//* * * * * * * * * * * * * * * * * * * * * * * * * *
std::string Dealer::showHand()
{
	std::string outString = "";
	outString += "The Dealer's hand contains: \n";
	outString += hand.handState();
	return outString;
}

//* * * * * * * * * * * * * * * * * * * * * * * * * *
// offerInsurance() check hand to see if insurance	*
// should be offered to user						*
//* * * * * * * * * * * * * * * * * * * * * * * * * *
bool Dealer::offerInsurance() const
{
	bool insurance = false;

	if (hand.card2IsAce())
		insurance = true;

	return insurance;
}