//* * * * * * * * * * * * * * * * * * * * * * * //
//  Author:		Paul Schwappach					//
//	Professor:	George Sfakianakis				//
//	Class:		CSIS 297 - Intermediate C++		//
//	Assignment:	Semester Project				//
//	Date:		03/04/2016						//
//* * * * * * * * * * * * * * * * * * * * * * * //

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//
//	About Player class	(header File)							//
//		This is a superclass granting behaviors all players		//
//	of the game black jack have access to.						//
//	It also has a nested Hand class that allows the creation	//
//  of a hand to store the Player objects Card objects in		//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//

#ifndef PLAYER_H
#define PLAYER_H

// included libraries
#include <vector>
#include <map>
#include <string>
#include <iostream>

class Player
{ // start of Player class
private:
	// private variable
	bool hasBlackJack;

protected:
	// -------------------- start nested Hand class --------------------
	class Hand
	{
	private:
		static void setCardValues();			// static member for card values

	protected:
		std::vector<Card> hand;					// hand of Cards
		static std::map <char, int> cardValues;	// hold card values

	public:
		Hand();								// no-arg constructor
		Hand(int num);						// arg constructor	
		void addCard(BlackJackDeck &deck);	// mutator
		void addCard(Card &card);			// mutator
		int getValue() const;				// mutator	
		int getSize() const;				// mutator
		bool sameRank() const;				
		bool card2IsAce() const;			// accessor
		Card removeCard();
		bool hasBusted() const;				// accessor
		std::string handState() const;
		std::string dealerHandState() const;

		// math operator overloads
		void operator - (Hand &splitHand);
		void operator + (BlackJackDeck &deckRight);
	}; // -------------------- end nested Hand class --------------------

public:
	//hand variable of Player
	Hand hand;

	// methods of Player:
	Player();
	void setBJ();					// mutator
	bool getBJ();					// accessor
	void hit(BlackJackDeck &deck);
	bool stand() const;
	virtual std::string showHand() const;
	
	// relational operator overloads
	bool operator > (const Player &pRight);
	bool operator >= (const Player &pRight);
	bool operator < (const Player &pRight);
	bool operator <= (const Player &pRight);
	bool operator == (const Player &pRight);
}; // -------------------- end Player class --------------------

#endif