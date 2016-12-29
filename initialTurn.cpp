#include <iostream>
#include <algorithm>	
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include "externalVars.h"
using namespace std;

int draw(int oldTotal, int aceCounter);

int initialTurn (int oldTotal, int aceCounter)
{
	oldTotal = draw(oldTotal, aceCounter);
	oldTotal = draw(oldTotal, aceCounter);
	cout << "Press Enter to continue" << endl;
	cin.get();
	return oldTotal;
}