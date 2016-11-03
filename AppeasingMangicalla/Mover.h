#pragma once
#include "GameObject.h"

class BoardManager;

// Abstract class that defines all polymorphic functions and attributes for
// a object that can "move". Action based objects.
class Mover :
	public GameObject
{
public:
	Mover();
	~Mover();
	bool TakeDamage(int dmg) { 
		health -= dmg;
		if (health <= 0)
			return true;
		
		return false;
	};

	// All objects that are able to move in game should override these methods
	// Check if the piece should move. Return vlaue is if the piece should move
	virtual bool AttemptMove(const int& yDir, const int& xDir) = 0;
	//Execute the move
	virtual void MovePiece(const int& yDir, const int& xDir) = 0;
	virtual Mover* AttemptAttack(const int& yDir, const int& xDir) = 0;
	virtual void Attack(Mover& hitCollision) = 0;

	int goldVal;
	bool hasMoved;
protected:
	int minDamage;
	int maxDamage;
	int health;
};

