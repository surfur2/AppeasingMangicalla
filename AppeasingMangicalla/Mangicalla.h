#pragma once
#include "Interactable.h"

/* Wizard that the player can interact with to end the game.*/
class Mangicalla 
	: public Interactable
{
public:
	Mangicalla(int cRow, int cCol);
	~Mangicalla();
	// What happens when a player interacts with him
	int Interact();
private:
	// Internal calculation for score at end of the game/
	int CalculateGoldForPlayer();
	// Gold Mangicalla starts with 
	int goldOnHand;
};

