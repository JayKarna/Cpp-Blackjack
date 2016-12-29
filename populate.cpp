#include <iostream>
#include <algorithm>	
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include "externalVars.h"
using namespace std;

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