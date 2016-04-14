//* * * * * * * * * * * * * * * * * * * * * * * //
//  Author:		Paul Schwappach					//
//	Professor:	George Sfakianakis				//
//	Class:		CSIS 297 - Intermediate C++		//
//	Assignment:	Semester Project				//
//	Date:		03/11/2016						//
//* * * * * * * * * * * * * * * * * * * * * * * //

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//
//	About User class											//
//		This class inherits from the Player class and allows	//
//	specific actions for a user to interface with 				//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//

// included header files
#include "Card.h"
#include "BlackJackDeck.h"
#include "Player.h"
#include "User.h"

//* * * * * * * * * * * * * * * * * * * * * * * *
// No-Argument Constructor						*
//* * * * * * * * * * * * * * * * * * * * * * * *
User::User()
{
	userName = "";
	userMoney = 100.00;
	resetHand();
	hand = Hand();
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// Argument Constructor							*
//* * * * * * * * * * * * * * * * * * * * * * * *
User::User(std::string name)
{
	setName(name);
	userMoney = 100.00;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// setName() sets userName						*
//* * * * * * * * * * * * * * * * * * * * * * * *
void User::setName(std::string name)
{
	userName = name;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// setBet() sets bet amount for user			*
//* * * * * * * * * * * * * * * * * * * * * * * *
void User::setBet(double amount)
{
	userBet = amount;
	if (hasDoubled)
		userMoney -= (userBet / 2);
	else
		userMoney -= userBet;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// setBet2() sets split bet amount for user		*
//* * * * * * * * * * * * * * * * * * * * * * * *
void User::setBet2(double amount)
{
	userBet2 = amount;
	if (hasDoubledSplit)
		userMoney -= (userBet2 / 2);
	else
		userMoney -= userBet2;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getMoney() adds win amount to userMoney		*
//* * * * * * * * * * * * * * * * * * * * * * * *
void User::addMoney(double winnings)
{
	userMoney += winnings;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// setInsurance() set's user insurance bet		*
//* * * * * * * * * * * * * * * * * * * * * * * *
void User::setInsurance(double amount)
{
	insurance = amount;
	userMoney -= insurance;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// setInsurance() set's user insurance bet		*
//* * * * * * * * * * * * * * * * * * * * * * * *
void User::resetHand()
{
	hand = Hand();
	userSplitHand = Hand();
	hasDoubled = false;
	hasDoubledSplit = false;
	setBet(0);
	setBet2(0);
	setInsurance(0);
	setUserWantsToQuit(false);

}

//* * * * * * * * * * * * * * * * * * * * * * * *
// setUserWantsToQuit() user wants to stop		*
// running theprogram							*
//* * * * * * * * * * * * * * * * * * * * * * * *
void User::setUserWantsToQuit(bool selection)
{
	userWantsToQuit = selection;
}


//* * * * * * * * * * * * * * * * * * * * * * * *
// getName() returns user's name				*
//* * * * * * * * * * * * * * * * * * * * * * * *
std::string User::getName() const
{
	return userName;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getBet() returns user's bet amount			*
//* * * * * * * * * * * * * * * * * * * * * * * *
double User::getBet() const
{
	return userBet;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getBet2() returns user's split bet amount	*
//* * * * * * * * * * * * * * * * * * * * * * * *
double User::getBet2() const
{
	return userBet2;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getMoney() displays amount of userMoney		*
//* * * * * * * * * * * * * * * * * * * * * * * *
double User::getMoney() const
{
	return userMoney;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getInsurance() set's user insurance bet		*
//* * * * * * * * * * * * * * * * * * * * * * * *
double User::getInsurance() const
{
	return insurance;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getUserWantsToQuit() returns if the user  	*
// wants to stop running the program			*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool User::getUserWantsToQuit() const
{
	return userWantsToQuit;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getHasDoubled() has user doubled	(main)		*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool User::getHasDoubled() const
{
	return hasDoubled;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getHasDoubledSplit() has user doubled (split)*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool User::getHasDoubledSplit() const
{
	return hasDoubledSplit;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// canDoubleDown() checks the hand to see if	*
//	it can double down (same with split hand)	*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool User::canDoubleDown(int handNum) const
{
	bool canDoubleDown = false;
	if (handNum == 1)
	{
		if (hand.getSize() == 2 && userMoney >= userBet)
		{
			canDoubleDown = true;
		}
		else
			canDoubleDown = false;
	}
	if (handNum == 2)
	{
		if (userSplitHand.getSize() == 2 && userMoney >= userBet2)
			canDoubleDown = true;
		else
			canDoubleDown = false;
	}

	return canDoubleDown;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// doubleDown() adds a card to userHand	and		*
//	doubles bet	(same with split hand)			*
//* * * * * * * * * * * * * * * * * * * * * * * *
void User::doubleDown(BlackJackDeck &deck, bool hasSplit)
{
	if (!hasSplit)
	{
		hand.addCard(deck);
		hasDoubled = true;
		setBet(userBet * 2);
	}
	else
	{
		userSplitHand.addCard(deck);
		hasDoubledSplit = true;
		setBet2(userBet2 * 2);
	}
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// getSplit() return if user split their hand	*
//* * * * * * * * * * * * * * * * * * * * * * * *
bool User::hasSplit() const
{
	bool hasSplit;

	if (userSplitHand.getSize() > 0)
		hasSplit = true;
	else
		hasSplit = false;

	return hasSplit;

}

//* * * * * * * * * * * * * * * * * * * * * * * *
// split() splits the user hand into two hands	*
//* * * * * * * * * * * * * * * * * * * * * * * *
void User::split(BlackJackDeck &deck)
{
	hand - userSplitHand;
	hand + deck;
	userSplitHand + deck;
	setBet2(userBet);
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// showHand() returns the user hand as a string	*
//* * * * * * * * * * * * * * * * * * * * * * * *
std::string User::showHand() const
{
	std::string outString = "";
	outString += userName;
	outString += ", your main hand contains: \n";
	outString += hand.handState();
	return outString;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// showSplitHand() returns the user split hand	*
// as a string									*
//* * * * * * * * * * * * * * * * * * * * * * * *
std::string User::showSplitHand() const
{
	std::string outString = "";
	outString += userName;
	outString += ", your split hand contains: \n";
	outString += userSplitHand.handState();
	return outString;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// overload << to show user name and their 		*
// amount of money								*
//* * * * * * * * * * * * * * * * * * * * * * * *
std::ostream &operator << (std::ostream &strm, const User &user)
{
	strm << user.userName << ", your current bankroll is: " << user.userMoney << "\n";
	strm << "Your current main hand bet is : $" << user.getBet() << "\n";
	if (user.hasSplit())
		strm << "Your current split hand bet is : $" << user.getBet2() << "\n";
	if (user.insurance)
		strm << "Your insurance value is: $" << user.getInsurance() << "\n";
	return strm;
}

//* * * * * * * * * * * * * * * * * * * * * * * *
// overload >> operator to input userName		*
//* * * * * * * * * * * * * * * * * * * * * * * *
std::istream &operator >> (std::istream &strm, User &user)
{
	// prompt for name
	std::cout << "First, enter your name!" << std::endl;
	strm >> user.userName;

	return strm;
}