#pragma once
#include <vector>
#include "mine.h"
class Sapper
{
public:
	int win = 0;
	int fieldWidth = 5, fieldHeight = 5, minesCount = 3;
	std::vector <mine> mines, discoveredCells;
	Sapper() 
	{
		for (int i = 0; i < minesCount; i++)
		{
			mines.push_back(mine(-1, -1));
		}
	}
	void minesOutput();
	void minesRandom(bool first, int x, int y);
	int minesAround(int x, int y, bool first, bool click);
	void dCells();
};

