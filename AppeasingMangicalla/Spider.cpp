#include "Spider.h"
#include "BoardManager.h"
#include "PathFinder.h"
#include <string>



Spider::Spider(int cRow, int cCol) : Mover(cRow, cCol)
{
	displayChar = Globals::GetSpiderDisplayChar();
	goldVal = Globals::GetSpiderGoldVal();
	health = Globals::GetSpiderHealth();
	minDamage = Globals::GetSpiderMinDamage();
	maxDamage = Globals::GetSpiderMaxDamage();
	type = GameObjects::spider;
	hasSeenPlayer = false;
}


Spider::~Spider()
{
}

// This is where you will check for FOV movement. If in FOV, then green light to move
bool Spider::AttemptMove(const int& playerPosY, const int& playerPosX)
{
	if (BoardManager::Instance()->CanEnemySeePlayer(this))
	{		
		PathFinder currentPath(currentCol, currentRow, playerPosX, playerPosY);

		currentPath.FindPath();

		while (currentPath.ast.path.top >= 0)
		{
			currentPathList.push_back(currentPath.Pop(currentPath.ast.path));
		}

		int newRow = currentPathList.front().second;
		int newCol = currentPathList.front().first;

		return BoardManager::Instance()->CanMove(newRow, newCol);
	}
	return false;
}

// This is where A* will be used for finding the path to player.
void Spider::MovePiece(const int& yDir, const int& xDir)
{	
	int newRow = currentPathList.front().second;
	int newCol = currentPathList.front().first;

	BoardManager::Instance()->MovePiece(currentRow, currentCol, newRow, newCol);
}

// We pass in the current possition of the enemy
Mover* Spider::AttemptAttack(const int& yDir, const int& xDir)
{
	// Up
	Mover* player = BoardManager::Instance()->CanEnemyAttack(currentRow - 1, currentCol);
	if (player != nullptr)
		return player;

	// Right
	player = BoardManager::Instance()->CanEnemyAttack(currentRow, currentCol + 1);
	if (player != nullptr)
		return player;

	// Down
	player = BoardManager::Instance()->CanEnemyAttack(currentRow + 1, currentCol);
	if (player != nullptr)
		return player;

	// Left
	player = BoardManager::Instance()->CanEnemyAttack(currentRow, currentCol - 1);
	if (player != nullptr)
		return player;

	return player;
}

void Spider::Attack(Mover& hitCollision)
{
	int damage = (rand() % (maxDamage - minDamage)) + minDamage;
	hitCollision.TakeDamage(damage);
	BoardManager::Instance()->AddPlayerDamageTaken(damage);
	string output = "Enemy  ";
	output += displayChar;
	output += " attacked player for: ";
	output = output + std::to_string(damage);
	BoardManager::Instance()->AddPrintAction(output);
}
