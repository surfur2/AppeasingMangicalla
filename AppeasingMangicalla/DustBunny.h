#pragma once
#include "Mover.h"

/* Basic type of enemy.
   Cannot move, only attack.*/
class DustBunny :
	public Mover
{
public:
	// Pass in the current position of a piece when creating it.
	DustBunny(int cRow, int cCol);
	// Default destructor since no "complex" data members
	~DustBunny();
	// Attempt a move
	bool AttemptMove(const int& yDir,const int& xDir);
	// Actually move
	void MovePiece(const int& yDir,const int& xDir);
	// Attempt a attack
	Mover* AttemptAttack(const int& yDir, const int& xDir);
	// Actually attack
	void Attack(Mover& hitCollision);
};

