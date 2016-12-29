/*
Blackjack Game in C++

Currently simulates Blackjack against an AI.

USECASE TO CONSIDER: Dealt two aces

Current task: make pretty
- Create a "turn" function
- Figure out why the ace counter stopped working
- Delete old, leftover stuff
- Remove overloading

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
#include <random>      		 // std::default_random_engine
#include <chrono>      		 // std::chrono::system_clock
#include "externalVars.h"	 // allows global variables to be used accross program
using namespace std;

//Global Variables
int deck[noOfSuits*cardsInSuit];	//52 card deck
int aiAceCounter = 0;				//Ace counters used in determining whether an ace counts as 1 or 11
int playerAceCounter = 0;
int playerTotal = 0;
int aiTotal = 0;

//Initializing all functions (content in separate .cpp files)
int draw(int oldTotal, int aceCounter);
void populate();
int initialTurn(int oldTotal, int aceCounter);
void results(int result1, int result2);
void aceCheck(int aceCounter, int total);
void printIntro();
// allow computer/player to hit or stay
// check the ace counter
// check whether the player/AI busted

int main()
{
	//Populates 52-element array for the deck.  Specific suits or face values do not matter. Face cards count as 10, aces count as 11 until hand is over 21
	populate();

	//Intro page
	printIntro();
	cin.get();
	
	//Draw Player 1's initial hand
	cout << "Player 1:\n";
	playerTotal = initialTurn(playerTotal, playerAceCounter);

	//Draw AI's initial hand
	cout << "Computer Player:\n";
	aiTotal = initialTurn(aiTotal, aiAceCounter);

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
			playerTotal = draw(playerTotal, playerAceCounter);	//Draws 1 new card and adds its value to Player 1's total
			if (playerTotal > 21)
			{
				aceCheck(playerAceCounter, playerTotal);
				if (playerTotal > 21)	//If even after replacing the ace's value Player 1 still busts . . .
				{
					z = 0;			//Breaks out of loop
					result1 = 0;	//Marks Player 1 as having busted (for future reference)
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
			aiTotal = draw(aiTotal, aiAceCounter);
			if (aiTotal > 21)
			{
				aceCheck(aiAceCounter, aiTotal);
				if (aiTotal > 21)
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