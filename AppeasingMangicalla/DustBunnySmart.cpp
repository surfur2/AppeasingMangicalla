#include "DustBunnySmart.h"
#include "BoardManager.h"
#include "PathFinder.h"



DustBunnySmart::DustBunnySmart(int cRow, int cCol) : DustBunny::DustBunny(cRow, cCol)
{
	displayChar = Globals::GetSpiderDisplayChar();
	goldVal = Globals::GetDustBunnyGoldVal();
	health = Globals::GetDustBunnyHealth();
	minDamage = Globals::GetDustBunnyMinDamage();
	maxDamage = Globals::GetDustBunnyMaxDamage();
	type = GameObjects::dustbunny;
	hasSeenPlayer = false;
}


DustBunnySmart::~DustBunnySmart()
{
}

// This is where you will check for FOV movement. If in FOV, then green light to move
bool DustBunnySmart::AttemptMove(const int& playerPosY, const int& playerPosX)
{
	if (BoardManager::Instance()->CanEnemySeePlayer(this))
	{		
		PathFinder currentPath(currentRow, currentCol, playerPosX, playerPosY);

		currentMoveTile = currentPath.FindPath();

		int xDir = currentMoveTile.first;
		int yDir = currentMoveTile.second;

		int newRow = currentRow + yDir;
		int newCol = currentCol + xDir;

		return BoardManager::Instance()->CanMove(newRow, newCol);
	}
	return false;
}

// This is where A* will be used for finding the path to player.
void DustBunnySmart::MovePiece()
{	
	int xDir = currentMoveTile.first;
	int yDir = currentMoveTile.second;

	int newRow = currentRow + yDir;
	int newCol = currentCol + xDir;

	BoardManager::Instance()->MovePiece(currentRow, currentCol, newRow, newCol);
}
