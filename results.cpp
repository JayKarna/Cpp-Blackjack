#include <iostream>
#include <algorithm>	
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include "externalVars.h"
using namespace std;

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