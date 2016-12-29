#include <iostream>
#include <algorithm>	
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include "externalVars.h"
using namespace std;

int draw(int oldTotal, int aceCounter)
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
		++aceCounter;
	}

	deck[0] = 0;		//Marks card as "in play"

	return newtotal;
}