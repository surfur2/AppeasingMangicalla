#include "DustBunnySmart.h"
#include "BoardManager.h"
#include "PathFinder.h"



DustBunnySmart::DustBunnySmart(int cRow, int cCol) : DustBunny::DustBunny(cRow, cCol)
{
}


DustBunnySmart::~DustBunnySmart()
{
}

// This is where you will check for FOV movement. If in FOV, then green light to move
bool DustBunnySmart::AttemptMove()
{
	return true;
}

// This is where A* will be used for finding the path to player.
void DustBunnySmart::MovePiece(const int& playerPosY, const int& playerPosX)
{
	//Find Path!!!
	PathFinder pF(currentRow, currentCol, playerPosX, playerPosY);
	std::pair<int, int> moveTile = pF.FindPath();
	int xDir = moveTile.first;
	int yDir = moveTile.second;

	if (this->AttemptMove())
	{
		int newRow = currentRow + yDir;
		int newCol = currentCol + xDir;

		BoardManager::Instance()->MovePiece(currentRow, currentCol, newRow, newCol);
	}
}
