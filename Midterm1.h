#pragma once

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <string>
#include <limits>
#include <random>

int rollDice();
bool isValidNumber(const std::string& str);

class Player {
public:
	int diceCount = 5;
	int diceValues[5] = { 0,0,0,0,0 };
	int order = 1;
	std::string name = "";
	void rollDices()
	{
		for (int i = 0; i < diceCount; i++)
		{
			diceValues[i] = rollDice();
		}
		int n = sizeof(diceValues) / sizeof(diceValues[0]);
		std::sort(diceValues,diceValues+n);
	}
	void showRoll()
	{
		for (int i = 0; i < diceCount; i++)
		{
			std::cout << diceValues[i] << " ";
		}
		std::cout << std::endl;
	}
	int countFace(int face)
	{
		int count = 0;
		for (int i = 0; i < diceCount; i++)
		{
			if (diceValues[i] == face)
			{
				count++;
			}
		}
		return count;
	}
};