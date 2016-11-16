#pragma once
#include "DustBunny.h"
#include "PathFinder.h"
#include <vector>
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

	vector<std::pair<int, int>> currentPathList;
};

