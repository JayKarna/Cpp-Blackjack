#include <iostream>
#include <algorithm>	
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include "externalVars.h"
using namespace std;

void aceCheck(int aceCounter, int total)
{
	if (aceCounter > 0)
	{
		--aiAceCounter;
		total = total - 10;
		cout << "Your total is over 21, so one of your aces will be worth 1\n";
		cout << "Your current total is " << total << ".\n\n";
	}
}