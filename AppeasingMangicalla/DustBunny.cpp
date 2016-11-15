#include "Globals.h"
#include "BoardManager.h"
#include "DustBunny.h"
#include <string>


DustBunny::DustBunny(int cRow, int cCol) : Mover(cRow, cCol)
{
	displayChar = Globals::GetDustBunnyDisplayChar();
	goldVal = Globals::GetDustBunnyGoldVal();
	health = Globals::GetDustBunnyHealth();
	minDamage = Globals::GetDustBunnyMinDamage();
	maxDamage = Globals::GetDustBunnyMaxDamage();
	type = GameObjects::dustbunny;
	hasSeenPlayer = false;
}

DustBunny::~DustBunny() {}

// This is where you will check for FOV movement. If in FOV, then green light to move
bool DustBunny::AttemptMove(const int& yDir,const int& xDir)
{
	return true;
}

// This is where A* will be used for finding the path to player.
void DustBunny::MovePiece(const int& yDir,const int& xDir) 
{ 
}

// We pass in the current possition of the enemy
Mover* DustBunny::AttemptAttack(const int& yDir,const int& xDir)
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

void DustBunny::Attack(Mover& hitCollision)
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






