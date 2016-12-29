#include <iostream>
#include <algorithm>	
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include "externalVars.h"
using namespace std;
	
void printIntro()
{
	cout << "\n***************************************************************************************************************************************************\n\n";
	cout << "Welcome to Blackjack!\n\nIn this game, you will be playing against a computer.  All cards are worth their face values, Face Cards are worth 10, and Aces are worth 11 or 1\n";
	cout << "The goal is to be the closest to 21, without going over.  If you go over, you \"bust\" and lose immediately!\n\n";
	cout << "***************************************************************************************************************************************************" << endl;
	cout << "Press Enter to begin" << endl;
}