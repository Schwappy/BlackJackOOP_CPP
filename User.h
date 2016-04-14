//* * * * * * * * * * * * * * * * * * * * * * * //
//  Author:		Paul Schwappach					//
//	Professor:	George Sfakianakis				//
//	Class:		CSIS 297 - Intermediate C++		//
//	Assignment:	Semester Project				//
//	Date:		03/11/2016						//
//* * * * * * * * * * * * * * * * * * * * * * * //

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//
//	About User class (header File)								//
//		This class inherits from the Player class and allows	//
//	specific actions for a user to interface with 				//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//

#ifndef USER_H
#define USER_H

// included libraries
#include <string>
#include <iostream>
#include <vector>

class User : public Player
{
private:
	std::string userName;
	double userMoney;
	double userBet;
	double userBet2;
	double insurance;
	bool hasDoubled;
	bool hasDoubledSplit;
	bool userWantsToQuit;

public:
	Hand userSplitHand;						// instance variable
	User();									// no-arg constructor
	User(std::string name);					// arg constructor
	void setName(std::string name);			// mutator
	void setBet(double amount);				// mutator
	void setBet2(double amount);			// mutator
	void addMoney(double winnings);			// mutator
	void setInsurance(double amount);		// mutator
	void setUserWantsToQuit(bool selection);	// mutator
	std::string getName() const;			// accessor
	double getBet() const;					// accessor
	double getBet2() const;					// accessor
	double getMoney() const;				// accessor
	double getInsurance() const;			// accessor
	bool getUserWantsToQuit() const;		// accessor
	bool getHasDoubled() const;				// accessor
	bool getHasDoubledSplit() const;		// accessor
	bool canDoubleDown(int handNum) const;					
	void doubleDown(BlackJackDeck &deck, bool hasSplit);	
	void resetHand();						
	bool hasSplit() const;					// accessor
	void split(BlackJackDeck &deck);		
	virtual std::string showHand() const;	// accessor
	std::string showSplitHand() const;		// accessor
	// operator overlaods
	friend std::ostream &operator << (std::ostream &strm, const User &user);	// insertion overload
	friend std::istream &operator >> (std::istream &strm, User &user);			// extraction overload
};

#endif