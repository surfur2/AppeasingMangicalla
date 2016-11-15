#pragma once
#include "DustBunny.h"
class Spider :
	public Mover
{
public:
	Spider(int cRow, int cCol);
	~Spider();

	// Attempt a move
	bool AttemptMove(const int& playerPosY, const int& playerPosX);
	// Actually move
	void MovePiece(const int& yDir, const int& xDir);
	// Attempt a attack
	Mover* AttemptAttack(const int& yDir, const int& xDir);
	// Actually attack
	void Attack(Mover& hitCollision);

private:
	std::pair<int, int> currentMoveTile;
};

