#include "Sapper.h"
#include <iostream>
#include <locale>
#include <random>
void Sapper::minesOutput() {
	std::cout << "In field " << minesCount << " mines\n";
	for (int mineI = 0; mineI < mines.size(); mineI++)
	{
		std::cout << "Mine " << mineI + 1 << " in x: " << mines[mineI].x << ", y: " << mines[mineI].y << "\n";
	}
}
void Sapper::minesRandom(bool first, int x, int y) {
	srand(time(NULL));
	std::random_device rd;
	std::mt19937 mersenne(rd());
	int coofMine = int(mersenne())%10;
	bool reroll = true, locReroll;
	mine tempMine(fabs(rand() % fieldWidth + 1), fabs(rand() % fieldHeight + 1));
	while (tempMine.x == x && tempMine.y == y) 
	{
		tempMine = mine(fabs(rand() % fieldWidth + 1), fabs(rand() % fieldHeight + 1));
	}
	std::vector <mine> tempMines;
	tempMines.push_back(tempMine);
	for (int i = 0; i < minesCount; i++)
	{
		while(reroll) 
		{
			locReroll = false;
			for (int x = 0; x <= i; x++)
			{
				if (tempMine.x == tempMines[x].x && tempMine.y == tempMines[x].y && tempMine.x == x && tempMine.y == y) locReroll = true;
			}
			if(locReroll) tempMine = mine(int(rand()) % fieldWidth + 1, int(rand()) % fieldHeight + 1);
			reroll = locReroll;
		}
		tempMines.push_back(tempMine);
		tempMine = mine(rand() % fieldWidth + 1, rand() % fieldHeight + 1);
		reroll = true;
	}
	for (int i = 0; i < minesCount; i++) {
		mines[i] = tempMines[i];
	}
}

int Sapper::minesAround(int x, int y, bool first, bool click)
{
	if (first) minesRandom(first, x, y);
	bool add = true;
	mine coordinates(x, y);
	int minesAround = 0;
	for (int i = 0; i < minesCount; i++)
	{
		if ((mines[i].x - 1 == coordinates.x || mines[i].x == coordinates.x || mines[i].x + 1 == coordinates.x) && (mines[i].y - 1 == coordinates.y || mines[i].y == coordinates.y || mines[i].y + 1 == coordinates.y)) {
			minesAround += 1;
		}
		if (mines[i].x == coordinates.x && mines[i].y == coordinates.y) return 10;
	}
	coordinates.around = minesAround;
	for (int i = 0; i < discoveredCells.size(); i++)
	{
		if (discoveredCells[i].x == x && discoveredCells[i].y == y) add = false;
	}
	if (add && click) discoveredCells.push_back(coordinates);
	return minesAround;
}
void Sapper::dCells() 
{
	std::cout << "In field " << discoveredCells.size() << " dCells\n";
	for (int mineI = 0; mineI < discoveredCells.size(); mineI++)
	{
		std::cout << "Cell " << mineI + 1 << " in x: " << discoveredCells[mineI].x << ", y: " << discoveredCells[mineI].y << "\n";
	}
}