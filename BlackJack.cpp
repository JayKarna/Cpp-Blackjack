/*
Blackjack Game in C++

Currently simulates Blackjack against an AI.

USECASE TO CONSIDER: Dealt two aces

Current task: make pretty
- Create a "turn" function
- Figure out why the ace counter stopped working
- Delete old, leftover stuff
- Remove ocerloading

Upcoming features/updates:
- Keep user from knowing computer's total, only knows 1 card
- Making more user-friendly
- Creating new arrays - "In Play" and "Discard"
- Adding "Play again" feature using deck in current state
- Create card classes
- 5 card arrays for hands?
- 5 card charlie
- remove "using namespace std;"

*/


#include <iostream>
#include <algorithm>	
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
using namespace std;

//Global Variables
const int cardsInSuit = 13;			//13 cards per suit (Ace to King)
const int noOfSuits = 4;			//4 suits (Hearts, Diamonds, Spades, and Clubs)
int deck[noOfSuits*cardsInSuit];	//52 card deck
int aiAceCounter = 0;				//Ace counters used in determining whether an ace counts as 1 or 11
int playerAceCounter = 0;
int playerTotal = 0;
int aiTotal = 0;

//Initializing all functions (content below main())
/*int initialPlayerDraw();		//First two cards
int initialAIDraw();
int playerHit(int oldTotal);	//Drawing additional cards
int aiHit(int oldTotal); */
int draw(int oldTotal);
void populate();
int initialTurn(int oldTotal);
void results(int result1, int result2);
// allow computer/player to hit or stay
// check whether the player/AI busted
// check the ace counter

int main()
{
	//Populates 52-element array for the deck.  Specific suits or face values do not matter. Face cards count as 10, aces count as 11 until hand is over 21
	populate();

	//Intro page
	cout << "\n***************************************************************************************************************************************************\n\n";
	cout << "Welcome to Blackjack!\n\nIn this game, you will be playing against a computer.  All cards are worth their face values, Face Cards are worth 10, and Aces are worth 11 or 1\n";
	cout << "The goal is to be the closest to 21, without going over.  If you go over, you \"bust\" and lose immediately!\n\n";
	cout << "***************************************************************************************************************************************************" << endl;
	cout << "Press Enter to begin" << endl;
	cin.get();
	
	//Draw Player 1's initial hand
	cout << "Player 1:\n";
	playerTotal = initialTurn(playerTotal);

	//Draw AI's initial hand
	cout << "Computer Player:\n";
	aiTotal = initialTurn(aiTotal);

	//Initializing variables used in second phase of game
	char choice;
	int z = 1, q = 1;
	int result1, result2;

	//Asking Player 1 whether they want to hit or stay
	while (z)
	{
		cout << "Player 1: Hit or stay? (input \"h\" or \"s\")\n";
		cin >> choice;
		
		if (choice == 'h')	//If Player 1 chooses to hit
		{
			playerTotal = draw(playerTotal);	//Draws 1 new card and adds its value to Player 1's total
			if (playerTotal > 21)
			{
				if (playerAceCounter > 0)	//If Player 1 has any aces and they bust, change the ace's value from 11 to 1
				{
					--playerAceCounter;
					playerTotal = playerTotal - 10;
					cout << "Your total is over 21, so one of your aces will be worth 1\n";
					cout << "Your current total is " << playerTotal << ".\n\n";
					if (playerTotal > 21)	//If even after replacing the ace's value Player 1 still busts . . .
					{
						z = 0;			//Breaks out of loop
						result1 = 0;	//Marks Player 1 as having busted (for future reference)
						cout << "Player 1 busted!\n\n";
					}
				}
				else	//If Player 1 busted without having any aces
				{
					z = 0;
					result1 = 0;
					cout << "Player 1 busted!\n\n";
				}
			}
			else	//If Player 1 drew and is still safe, they can keep going
			{
				z = 1;
			}
		}

		else if (choice == 's')	//If Player 1 chooses to stay . . .
		{
			z = 0;			//Breaks out of loop
			result1 = 1;	//Marks Player 1 as having not busted (for future reference)
		}

		else	//If Player 1 enters anything besides "h" or "s", they must enter their option
		{
			cout << "Please try again.\n";
			z = 1;
		}
	}
	cout << "Press Enter to begin Computer's turn" << endl;
	cin.get();	//For some reason, 2 cin.get()'s are required here for it to function properly
	cin.get();
	
	//Computer player's turn works the same as Player 1's, with one primary difference (noted in in-line comments)
	while (q)
	{
		cout << "Computer Player: Hit or stay?\n";

		if (aiTotal < 17)	//If Computer's hand's total is below 17, they will draw a new card
		{
			cout << "Computer Player hits.\n\n";
			aiTotal = draw(aiTotal);
			if (aiTotal > 21)
			{
				if (aiAceCounter > 0)
				{
					--aiAceCounter;
					aiTotal = aiTotal - 10;
					cout << "Your total is over 21, so one of your aces will be worth 1\n";
					cout << "Your current total is " << aiTotal << ".\n\n";
					if (aiTotal > 21)
					{
						q = 0;
						result2 = 0;
						cout << "Computer Player busted!\n\n";
					}
				}
				else
				{
					q = 0;
					result2 = 0;
					cout << "Computer Player busted!\n\n";
				}
			}
			else	//If Computer's hand is 17 or higher, they will stay
			{
				q = 1;
			}
		}

		else
		{
			cout << "Computer Player stays.\n\n";
			q = 0;
			result2 = 1;
		}
	}
	cout << "Press Enter to see results" << endl;
	cin.get();
	
	//Displaying end-of-game results, using whether or not they busted and their hand totals
	results(result1, result2);
	
	return 0;
}

/*int initialPlayerDraw()
{
	int k = 1;
	int val1, val2, total;
	while (k)
	{
		//srand((unsigned)time(NULL));	//Seeds RNG based on time, so it is different every execution
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle (&deck[0], &deck[52], std::default_random_engine(seed));
		//random_shuffle(&deck[0][0], &deck[4][13]);	//Shuffles the deck before dealing
		if (deck[0] == 0 || deck[1] == 0)		//If either of these values are 0 (already in play), reshuffle
		{
			k = 1;
		}
		else
		{
			val1 = deck[0];		//Draw two cards and add them for your initial total
			val2 = deck[1];
			total = val1 + val2;
			k = 0;

			if (deck[0] == 11)
			{
				++playerAceCounter;
			}
			if (deck[1] == 11)
			{
				++playerAceCounter;
			}

			deck[0] = 0;		//Marks two cards dealt as "in play"
			deck[1] = 0;
		}
	}
	cout << "Your cards are " << val1 << " and " << val2 << ".\n";
	cout << "Your total is " << total << ".\n\n";

	return total;
}

int initialAIDraw()
{
	int k = 1;
	int val1, val2, total;
	while (k)
	{
		//srand((unsigned)time(NULL));	//Seeds RNG based on time, so it is different every execution
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle (&deck[0], &deck[52], std::default_random_engine(seed));
		//random_shuffle(&deck[0][0], &deck[4][13]);	//Shuffles the deck before dealing
		if (deck[0] == 0 || deck[1] == 0)		//If either of these values are 0 (already in play), reshuffle
		{
			k = 1;
		}
		else
		{
			val1 = deck[0];		//Draw two cards and add them for your initial total
			val2 = deck[1];
			total = val1 + val2;
			k = 0;

			if (deck[0] == 11)
			{
				++aiAceCounter;
			}
			if (deck[1] == 11)
			{
				++aiAceCounter;
			}

			deck[0] = 0;		//Marks two cards dealt as "in play"
			deck[1] = 0;
		}
	}
	cout << "Your cards are " << val1 << " and " << val2 << ".\n";
	cout << "Your total is " << total << ".\n\n";

	return total;
}

int playerHit(int oldTotal)
{
	while (deck[0] == 0)		//If top card is 0 (already in play), reshuffle
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle (&deck[0], &deck[52], std::default_random_engine(seed));
		//random_shuffle(&deck[0][0], &deck[4][13]);
	}

	int val = deck[0];
	int newtotal = oldTotal + val;

	cout << "You drew a " << val << ".\n";
	cout << "Your new total is " << newtotal << ".\n\n";

	if (deck[0] == 11)
	{
		++playerAceCounter;
	}

	deck[0] = 0;		//Marks card as "in play"

	return newtotal;
}

int aiHit(int oldTotal)
{
	while (deck[0] == 0)		//If top card is 0 (already in play), reshuffle
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle (&deck[0], &deck[52], std::default_random_engine(seed));
		//random_shuffle(&deck[0][0], &deck[4][13]);
	}

	int val = deck[0];
	int newtotal = oldTotal + val;

	cout << "You drew a " << val << ".\n";
	cout << "Your new total is " << newtotal << ".\n\n";

	if (deck[0] == 11)
	{
		++aiAceCounter;
	}

	deck[0] = 0;		//Marks card as "in play"

	return newtotal;
} */

void populate()
{
	//Populates 52-element array for the deck.  Specific suits or face values do not matter. Face cards count as 10, aces count as 11 until hand is over 21
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			deck[i*13+j] = j + 2;
		}
		
		for (int j = 9; j < 12; j++)
		{
			deck[i*13+j] = 10;
		}

		deck[12] = 11;
		deck[25] = 11;
		deck[38] = 11;
		deck[51] = 11;
	}
}

int initialTurn (int oldTotal)
{
	oldTotal = draw(oldTotal);
	oldTotal = draw(oldTotal);
	cout << "Press Enter to continue" << endl;
	cin.get();
	return oldTotal;
}

int draw(int oldTotal)
{
	while (deck[0] == 0)		//If top card is 0 (already in play), reshuffle
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle (&deck[0], &deck[52], std::default_random_engine(seed));
		//random_shuffle(&deck[0][0], &deck[4][13]);
	}

	int val = deck[0];
	int newtotal = oldTotal + val;

	cout << "You drew a " << val << ".\n";
	cout << "Your new total is " << newtotal << ".\n\n";

	if (deck[0] == 11)
	{
		++aiAceCounter;
	}

	deck[0] = 0;		//Marks card as "in play"

	return newtotal;
}

void results(int result1, int result2)
{
	if (result1 == 0 && result2 == 0)
	{
		cout << "You both busted!\nGame over.\n";
	}
	else if (result1 == 1 && result2 == 0)
	{
		cout << "Computer Player busted!\nPlayer 1 won with a total of " << playerTotal << ".\n";
	}
	else if (result1 == 0 && result2 == 1)
	{
		cout << "Player 1 busted!\nComputer Player won with a total of " << aiTotal << ".\n";
	}
	else
	{
		if (playerTotal > aiTotal)
		{
			cout << "Player 1 won with a total of " << playerTotal << ".\n";
			cout << "Computer Player's score: " << aiTotal << ".\n";
		}
		else if (playerTotal < aiTotal)
		{
			cout << "Computer Player won with a total of " << aiTotal << ".\n";
			cout << "Player 1's score: " << playerTotal << ".\n";
		}
		else
		{
			cout << "It's a tie! Both players have a score of " << playerTotal << "!\n";
		}
	}
}