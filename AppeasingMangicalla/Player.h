#pragma once
#include "Mover.h"
#include "Interactable.h"
#include <iostream>

class BoardManager;

/* The player class.*/
class Player :
	public Mover
{
public:
	Player(int cRow, int cCol);
	Player(const Player& player);
	~Player();
	// Base methods required of a Mover
	bool AttemptMove(const int& yDir, const int& xDir);
	void MovePiece(const int& yDir, const int& xDir);
	Mover* AttemptAttack(const int& yDir, const int& xDir);
	void Attack(Mover& hitCollision);

	// Only the player can interact with objects
	Interactable* AttemptInteraction(const int& yDir, const int& xDir);
	void PerformInteraction(Interactable& interactable);

	// Setters that only accept addition
	void AddStepTaken() { stepsTaken++; };
	void AddGoldToTotal(const int& gold) { goldVal += gold; };
	void AddGoldToTotal(const unsigned int& gold) { goldVal += gold; };
	void AddDamageTaken(const int& damage) { damageTaken += damage; };

	// Basic getters
	int GetStepsTaken() { return stepsTaken; };
	int GetDamageTaken() { return damageTaken; };
	bool IsPlayerDead();

	// Define the parameters we want to output for the player.
	friend ostream &operator<<(ostream &output, const Player &player)
	{
		output << "Steps taken: " << player.stepsTaken << "\n";
		output << "Damage taken: " << player.damageTaken << "\n";
		return output;
	}
private:
	int stepsTaken;
	int damageTaken;
};

