//* * * * * * * * * * * * * * * * * * * * * * * //
//  Author:		Paul Schwappach					//
//	Professor:	George Sfakianakis				//
//	Class:		CSIS 297 - Intermediate C++		//
//	Assignment:	Semester Project				//
//	Date:		03/11/2016						//
//* * * * * * * * * * * * * * * * * * * * * * * //

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//
// Test all of the classes that make up Black Jack!				//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *	//

#include "Card.h"
#include "BlackJackDeck.h"
#include "Player.h"
#include "User.h"
#include "Dealer.h"

#include <string>
#include <iostream>
#include <ctime>
#include <iomanip>

// static member declarations
std::map <char, int> Player::Hand::cardValues;

// function prototypes
void initializeHands(BlackJackDeck &deck, User &user, Dealer &dealer);
void handleHand(BlackJackDeck &deck, User &user, Dealer &dealer);
void calcWinner(User &user, Dealer &dealer);
bool handleInsurance(User &user);
bool inputValidation(int num);
bool inputValidation(double num, User &user);

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- Main -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
int main()
{
	// seed the random shuffle
	srand(unsigned(time(NULL)));

	// Declare variables
	int numDecks = 1;			// number of total BJ decks to be played with
	double userBetAmount;		// amount of money user will bet
	std::string userName;		// user name
	bool userBusted = false;	// did user bust?
	bool dealerBusted = false;	// did dealer bust?
	bool again = false;			// play another hand?
	bool goodInput = false;		// validated userSelection
	bool gameover = false;		// when user runs out of money
	char userSelection = ' ';	// play again selection

	// Declare objects
	Dealer dealer;
	User user;

	// prompt user for their name
	std::cout << "Hello, this is a text based Black Jack game.\n";
	std::cin >> user;

	// prompt user for number of decks
	do
	{
		std::cout << "How many decks of cards would you like to play with?\n"
			<< "Enter a number: (Max 8)\n";
		std::cin >> numDecks;
	} while (!inputValidation(numDecks));

	// create the BlackJackDeck object with the number of decks user wants
	BlackJackDeck multiDeck(numDecks);

	// game loop -- one full hand per loop
	do {

		// set a bet for the hand
		do {
			std::cout << "How much would you like to bet this hand?\n" << "You have $"
				<< std::setprecision(2) << std::fixed << user.getMoney() << " available.\n"
				<< "Minimum bet: $0.01, maximum: no limit.\n";
			std::cin >> userBetAmount;
		} while(!inputValidation(userBetAmount, user));

		// set user bet according to input
		user.setBet(userBetAmount);

		// initialize the hand of user and dealer
		initializeHands(multiDeck, user, dealer);

		// call the userAction function to handle user's play
		handleHand(multiDeck, user, dealer);

		// check if user selected to terminate the program
		if (user.getUserWantsToQuit())
			break;

		// finish the dealers hand
		dealer.finishRound(multiDeck, user.hand.getValue());

		// determine the winner of the hand
		calcWinner(user, dealer);

		// add a gameover if userMoney = $0.00;
		if (user.getMoney() == 0.00)
			gameover = true;

		// check to play another hand 
		if (!gameover)
		{
			// prompt for another hand
			std::cout << "Would you like to play again? (Y = yes, any other key to quit)\n";
			std::cin >> userSelection;
			if (toupper(userSelection) != 'Y')
				again = false;
			else
			{
				again = true;
				user.resetHand();
				dealer = Dealer();
			}
		}
		else
			std::cout << "You ran out of money! Gameover. Play again soon!";

	} while (again && !gameover); // end game loop

	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- /Main -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- */

	////fix this later....
	system("Pause");
	return 0;
}

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- Initialize Hands() -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
/*
initializeHands()
Params:	BlackJackDeck &deck, User &user, Dealer &dealer

Does:	adds 2 cards to each hand for dealer and user
		
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void initializeHands(BlackJackDeck &deck, User &user, Dealer &dealer)
{
	// create a hand for the dealer & user
	for(int count = 0; count < 2; count++)
	{
		dealer.hand + deck;		// overloaded operator function
		user.hand + deck;		// overloaded operator function
	}
} // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- /Initialize Hands() -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- handleHand() -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
/*
handleHand()
Params:	BlackJackDeck &deck, User &user, Dealer &dealer

Does:	1) checks for BlackJacks(BJ) for user and dealer
		2) if no BJs asks user to complete their hand
			given options which are handled in a switch

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void handleHand(BlackJackDeck &deck, User &user, Dealer &dealer)
{
	// local variables
	bool inPlay = true;			// if user's hand is in play still
	bool hasSplit = false;		// did the user split?
	bool hand1Done = false;		// if split, did first split hand end?
	char userAction;			// user's action to hand
	int userHandValue = user.hand.getValue();					// for efficiency
	int userSplitValue = user.userSplitHand.getValue();			// ""		""
	int dealerValue = dealer.hand.getValue();					// ""       ""
	bool userHasInsurance = false;								// does user have insurance
	bool goodInput = false;										// input validation

	// show hands to user (and user's hand value)
	std::cout << dealer.concealHand() << std::endl;
	std::cout << user.showHand() << "Value: " << userHandValue << std::endl;

	// set user and dealer BJ bools
	user.setBJ();
	dealer.setBJ();

	// handle insurance
	if (dealer.offerInsurance())
		userHasInsurance = handleInsurance(user);		

	// handle BlackJack's
	if (user.getBJ() && !hasSplit)
		inPlay = false;

	// if dealer has BJ end hand
	if (dealer.getBJ())
	{
		if (userHasInsurance)
			user.addMoney(user.getInsurance() * 2);
		inPlay = false;
	}
	// dealer does not have BJ and offered insurance
	else if (dealer.offerInsurance())
	{
		std::cout << "The dealer does not have a BlackJack!\n";
		if (userHasInsurance)
			std::cout << "However, your insurance money was lost.\n\n";
	}

	// if no BJ's handle hand normally

	// prompt user for action until they cannot act again
	while (inPlay)
	{
		if (hasSplit && hand1Done) // For split hand (check first)
		{
			std::cout << user.showSplitHand() << "Value: "
				<< userSplitValue << std::endl << std::endl;

			std::cout << "\nWhat would you like to do with the split hand?\n"
				<< "H = Hit, S = Stand, D = DoubleDown\n"
				<< "R = to see all hands again.\n"
				<< "F = see available money.\n" 
				<< "Q = quit program" << std::endl;
		}
		else // For main hand
		{
			std::cout << "\nWhat would you like to do with the main hand?\n"
				<< "H = Hit, S = Stand, D = DoubleDown, X = Split\n"
				<< "R = to see all hands again.\n"
				<< "F = see available money.\n" 
				<< "Q = quit program" << std::endl;
		}
		std::cin >> userAction;

		// switch statement to act based on input
		switch (toupper(userAction))
		{
		// ------------------------------------------ Hit ------------------------------------------
		case 'H':
			if (hasSplit && hand1Done)  // For split hand (check first)
			{
				user.userSplitHand + deck;
				userSplitValue = user.userSplitHand.getValue();
				std::cout << "You have been dealt a " << deck.cLastCardDealt() << "\n\n";
				std::cout << user.showSplitHand() << "Value: " << userSplitValue << std::endl;
				if (userSplitValue == 21)
				{
					inPlay = false;
					std::cout << "\nSplit hand is finished\n\n";
				}
				else
				{
					inPlay = !user.userSplitHand.hasBusted();
					if (!inPlay)
						std::cout << "\nSplit hand is finished\n\n";
				}
			}
			else // For main hand
			{
				user.hand + deck;
				userHandValue = user.hand.getValue();
				std::cout << "\nYou have been dealt a " << deck.cLastCardDealt() << std::endl;
				std::cout << user.showHand() << "Value: " << userHandValue << std::endl;
				hand1Done = user.hand.hasBusted();
				if (userHandValue == 21)
					hand1Done = true;
				if (hand1Done)
					std::cout << "\nMain hand is finished\n\n";

			}
			break;

		// -------------------------------------------- Stand --------------------------------------------
		case 'S':
			if (hasSplit && hand1Done) // For split hand (check first)
			{
				inPlay = !user.stand();
				std::cout << "\nSplit hand is finished\n\n";
			}

			else // For main hand
			{
				hand1Done = user.stand();

				if (hand1Done && !hasSplit)
				{
					inPlay = false;
					std::cout << "\nMain hand is finished\n\n";
				}

				if (hasSplit)
					std::cout << "\nMain hand is finished\n\n";
			}
			break;

		// --------------------------------------- Double Down ---------------------------------------
		case 'D':
			if (hasSplit && hand1Done) // For split hand (check first)
			{
				if (user.canDoubleDown(2))
				{
					user.doubleDown(deck, hasSplit);
					std::cout << "\nSplit hand is finished\n\n";
					inPlay = false;
				}
				else
					std::cout << "\nError: you can't double down after a hit on this hand.\n";
			}

			else // For main hand
			{
				if (user.canDoubleDown(1))
				{
					user.doubleDown(deck, hasSplit);
					hand1Done = true;
					if (hasSplit)
						std::cout << "\nMain hand is finished\n\n";

					if (!hasSplit)
						inPlay = false;
				}
				else
					std::cout << "\nError: you can't double down after a hit on this hand.\n";
			}
			break;

		// ------------------------------------------ Split ------------------------------------------
		case 'X':
			if (hasSplit)
				std::cout << "ERROR: You can only split once per hand.\n";
			else if (!user.hand.sameRank())
				std::cout << "ERROR: You can only split with two cards of the same rank.\n";
			else if (user.getMoney() < user.getBet())
				std::cout << "ERROR: You cannot split youre funds are too low. "
				<< "($" << std::setprecision(2) << std::fixed << user.getMoney() << " available)\n\n";
			else
			{
				user.split(deck);
				hasSplit = true;
				userSplitValue = user.userSplitHand.getValue();		// set split hand value
				userHandValue = user.hand.getValue();				// update main hand value
				std::cout << "\n" << user.showHand() << "Value: " << userHandValue << std::endl;
				std::cout << user.showSplitHand() << "Value: "
					<< userSplitValue << std::endl;
			}
			break;

		// ---------------------------------------- Show hands ----------------------------------------
		case 'R':
			std::cout << dealer.concealHand() << std::endl;
			std::cout << user.showHand() << "Value: " << userHandValue << std::endl;
			if (hasSplit)
				std::cout << user.userSplitHand.handState() << "Value: "
				<< userSplitValue << std::endl;
			break;

		//  -----------------------------------Show Available Money -----------------------------------
		case 'F':
			std::cout << user;
			//std::cout << "($" << std::setprecision(2) << std::fixed << user.getMoney() << " available)\n\n";
			break;
		case 'Q':
			std::cout << "Thanks for playing BlackJack, come back soon!\n\n\n\n";
			user.setUserWantsToQuit(inPlay);
			inPlay = false;
			break;

		default:
			std::cout << "You're selection is not valid.\n";
			break;
		} // end switch

		// quit loop if hand 1 is finished and no split hand
		if (hand1Done && !hasSplit)
			inPlay = false;
	} // endwhile

} // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- /handleHand() -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-


// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- calcWinner() -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
/*
handleHand()
Params:	User &user, Dealer &dealer

Does:	1) checks for BlackJacks(BJ) for user and dealer
		2) if no BJs compares the dealer hand against
			the user hand(s) to determine the winner
			and adjusts user money accordingly			

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void calcWinner(User &user, Dealer &dealer)
{
	// local variables
	const double USER_BET = user.getBet();
	const double BLACKJACK_WIN_AMOUNT = USER_BET + (USER_BET * 1.5);
	const double HAND_WIN_AMOUNT =	USER_BET * 2;
	const double PUSH_AMOUNT =	USER_BET;
	const double DOUBLE_DOWN_WIN_AMOUNT = USER_BET * 2;
	double hand1WinAmount = 0;
	double hand2WinAmount = 0;
	int uHandVal1 = user.hand.getValue();
	int uHandVal2 = user.userSplitHand.getValue();
	int dHandVal = dealer.hand.getValue();
	bool uBust1 = user.hand.hasBusted();
	bool uBust2 = user.userSplitHand.hasBusted();
	bool dBust = dealer.hand.hasBusted();
	bool userHasSplit = user.hasSplit();
	bool blackJack = false;

	// check for user BJ
	if (user.getBJ() && !dealer.getBJ())
	{
		// user += BLACKJACK_WIN_AMOUNT;
		std::cout << "You were dealt and BlakJack and won!\n"
			<< "You're main hand win amount is: $" << BLACKJACK_WIN_AMOUNT << ".\n";
		user.addMoney(BLACKJACK_WIN_AMOUNT);
	}
	// check for dealer BJ
	else if (dealer.getBJ())
	{
		std::cout << dealer.showHand() << "Value: " << dHandVal << std::endl;
		std::cout << "The dealer was dealt and BlakJack and won. Your bet was lost.\n\n";
	}
	// if no BJ - check each hand against dealer and adjsut money if user wins
	else {
		switch(dBust)
		{
			// if dealer busted
		case true:
			// --------------------------------------- handle main hand ---------------------------------------
			// display main hand
			std::cout << std::endl << std::endl;
			std::cout << user.showHand() << "Value: " << uHandVal1 << "\n\n";

			// main hand bust
			if (uBust1)
				std::cout << user.getName() << ", your main hand has busted.\n";
			// main hand not busted
			else
			{
				std::cout << dealer.showHand() << "Value: " << dHandVal << std::endl;
				std::cout << "The dealer has busted, you're main hand won!\n\n";
				if (user.getHasDoubled())
				{
					user.addMoney(DOUBLE_DOWN_WIN_AMOUNT);
					hand1WinAmount = DOUBLE_DOWN_WIN_AMOUNT;
				}
				else
				{
					user.addMoney(HAND_WIN_AMOUNT);
					hand1WinAmount = HAND_WIN_AMOUNT;
				}
				// display win amount for hand 1
				std::cout << "You're main hand win amount is: $" << hand1WinAmount << ".\n\n";
			}

			// --------------------------------------- handle split hand ---------------------------------------
			if (userHasSplit)
			{
				std::cout << user.showSplitHand() << "Value: " << uHandVal2 << std::endl;
				// split hand bust
				if (userHasSplit && uBust2)
					std::cout << user.getName() << ", your split hand has busted.\n";
				else
				{
					std::cout << dealer.showHand() << "Value: " << dHandVal << std::endl;
					std::cout << "The dealer has busted, you're split hand won !\n";
					// add winnings to hand based on whether user split and or doubled down
					if (userHasSplit)
					{
						if (user.getHasDoubledSplit())
						{
							user.addMoney(DOUBLE_DOWN_WIN_AMOUNT);
							hand2WinAmount = DOUBLE_DOWN_WIN_AMOUNT;
						}
						else
						{
							user.addMoney(HAND_WIN_AMOUNT);
							hand2WinAmount = HAND_WIN_AMOUNT;
						}
						// display win amount for hand 2
						std::cout << "You're split hand win amount is: $" << hand2WinAmount << ".\n\n";
					}
				}
			}
			break;

			// if dealer has not busted
		case false:
			// this is where I can use comparison overload
			// --------------------------------------- handle main hand ---------------------------------------
			// chek main hand against dealer
			if (!uBust1)
			{
				std::cout << std::endl << std::endl;
				std::cout << dealer.showHand() << "Value: " << dHandVal << std::endl;
				if (user > dealer)
				{
					std::cout << user.showHand() << "Value: " << uHandVal1 << "\n\n";
					std::cout << user.getName() << ", your main hand's value is higher than the dealer, "
						<< " you won the hand!\n\n";

					if (user.getHasDoubled())
					{
						user.addMoney(DOUBLE_DOWN_WIN_AMOUNT);
						hand1WinAmount = DOUBLE_DOWN_WIN_AMOUNT;
					}
					else
					{
						user.addMoney(HAND_WIN_AMOUNT);
						hand1WinAmount = HAND_WIN_AMOUNT;
					}
					// display win amount for hand 1
					std::cout << "You're main hand win amount is: $" << hand1WinAmount << ".\n";
				}
				else if (user < dealer)
				{
					std::cout << user.showHand() << "Value: " << uHandVal1 << "\n\n";
					std::cout << user.getName() << ", your main hand's value is lower than the dealer, "
						<< " you have lost the hand.\n\n";
				}
				else
				{
					std::cout << "Your main hand has the same value as the dealer's hand and is therefore a push.\n\n";
					if (user.getHasDoubled())
						user.addMoney(PUSH_AMOUNT);
					user.addMoney(PUSH_AMOUNT);
				}

			}
			else
				std::cout << user.getName() << ", your main hand has busted.\n";

			// --------------------------------------- handle split hand ---------------------------------------
			// check split hand against dealer
			if (userHasSplit && !uBust2)
			{
				std::cout << std::endl << std::endl;
				std::cout << dealer.showHand() << "Value: " << dHandVal << std::endl;
				if (uHandVal2 > dHandVal)
				{
					std::cout << user.showSplitHand() << "Value: "<< uHandVal2 << "\n\n";
					std::cout << user.getName() << ", your split hand's value is higher than the dealer, "
						<< " you won the hand!\n\n";
					if (user.getHasDoubledSplit())
					{
						user.addMoney(DOUBLE_DOWN_WIN_AMOUNT);
						hand2WinAmount = DOUBLE_DOWN_WIN_AMOUNT;
					}
					else
					{
						user.addMoney(HAND_WIN_AMOUNT);
						hand2WinAmount = HAND_WIN_AMOUNT;
					}
					// display win amount for hand 2
					std::cout << "You're split hand win amount is: $" << hand2WinAmount << ".\n";
				}
				else if (uHandVal2 < dHandVal)
				{
					std::cout << user.showSplitHand() << "Value: "<< uHandVal2 << "\n\n";
					std::cout << user.getName() << ", your split hand's value is lower than the dealer, "
						<< " you have lost the hand.\n\n";
				}
				else
				{
					std::cout << "Your split hand has the same value as the dealer's hand and is therefore a push.\n\n";
					if (user.getHasDoubled())
						user.addMoney(PUSH_AMOUNT);
					user.addMoney(PUSH_AMOUNT);
				}
			}
			else if (userHasSplit && uBust2)
				std::cout << user.getName() << ", your split hand has busted.\n";
			break;

		} // end switch
	} // end if - (if user Bj) Else if (dealerBJ) else: handle hand

} // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- /calcWinner() -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- handleInsurance(User) -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
/*
handleInsurance()
Params:	takes a &user object
Does:	asks user for insurance and removes an amount based on
		the users bet amount for that hand

return:	bool userHasInsurance(local) if the user wants(can have)
		insurance or not

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool handleInsurance(User &user)
{
	char userSelection;
	bool userHasInsurance;
	do {
		std::cout << "Do you want insurance? (Y/N)\n";
		std::cin >> userSelection;

		if (toupper(userSelection) == 'Y')
		{
			if (user.getMoney() < (user.getBet() / 2))
			{
				std::cout << "You do not have available funds to hold insurance.\n\n";
				userHasInsurance = false;
			}
			else
			{
				user.setInsurance(user.getBet() / 2);
				std::cout << user.getName() << ", your insurance is set at: $" << user.getInsurance() << std::endl;
				userHasInsurance = true;
			}
		}
		else if (toupper(userSelection) == 'N')
			userHasInsurance = false;
		else
		{
			std::cout << "\n\nERROR: your input was invalid\n\n";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
	} while (toupper(userSelection) != 'Y' && toupper(userSelection) != 'N');
	return userHasInsurance;
} // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- /handleInsurance(User) -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- inputValidation(int) -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
/*
inputValidation()
Params:	int num

Does:	checks to see if the passed in value is an int and is
		within the range of 1 - 8 (max decks allowed)

return:	boolean if the input is valid or not

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool inputValidation(int num)
{
	const int INPUT_MIN = 1;
	const int INPUT_MAX = 8;
	bool goodInput = false;
	// bool validNumber = false;

	// check to see if input is valid (is int and positive int)
	if ((std::cin.fail() || (std::cin.peek() != '\r' && std::cin.peek() != '\n'))
		|| num < INPUT_MIN || num > INPUT_MAX)
	{
		std::cout << "\n\nERROR: your input was invalid\n\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	else
		goodInput = true;

	return goodInput;
} // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- /inputValidation(int) -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- /inputValidation(double, User) -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
/*
inputValidation()
Params:	int num

Does:	checks to see if the passed in value is a double and is
		at least 0.01

return:	boolean if the input is valid or not

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool inputValidation(double num, User &user)
{
	const double INPUT_MIN = 0.01;
	bool goodInput = false;
	// bool validNumber = false;

	// check to see if input is valid (is int and positive int)
	if ((std::cin.fail() || (std::cin.peek() != '\r' && std::cin.peek() != '\n'))
		|| num < INPUT_MIN || num > user.getMoney())
	{
		std::cout << "\n\nERROR: your input was invalid\n\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	else
		goodInput = true;

	return goodInput;
} // -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- /inputValidation(double, User) -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-