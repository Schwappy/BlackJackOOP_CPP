//* * * * * * * * * * * * * * * * * * * * * * * //
//  Author:		Paul Schwappach					//
//	Professor:	George Sfakianakis				//
//	Class:		CSIS 297 - Intermediate C++		//
//	Assignment:	Semester Project				//
//	Date:		03/04/2016						//
//* * * * * * * * * * * * * * * * * * * * * * * //

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//
//	About Dealer class (header File)							//
//		This class inherits from the Player class and is		//
//	controlled by the game state to perform it's actions on		//
//	it's hand of cards according to the rules of Black Jack		//
//	for a dealer												//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//

#ifndef DEALER_H
#define DEALER_H

// included libraries
#include <string>
#include <iostream>
#include <vector>

class Dealer : public Player
{
public:
	void finishRound(BlackJackDeck &deck, int value);
	std::string concealHand() const;
	bool offerInsurance() const;
	virtual std::string showHand();
};
#endif