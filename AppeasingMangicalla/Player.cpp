#include "Globals.h"
#include "Player.h"
#include "BoardManager.h"
#include "Wall.h"
#include <math.h>
#include <time.h>
#include <string>

// Base constructor for Player
// Most of this information can be pulled out from a .txt fisle instead
Player::Player(int cRow, int cCol) : Mover (cRow, cCol)
{
	displayChar = Globals::GetPlayerDisplayChar();
	goldVal = Globals::GetPlayerGoldVal();
	health = Globals::GetPlayerHealth();
	minDamage = Globals::GetPlayerMinDamage();
	maxDamage = Globals::GetPlayerMaxDamage();
	radiusFov = Globals::GetPlayerFov();
	type = GameObjects::player;
	damageTaken = 0;
	stepsTaken = 0;
	srand(time(NULL));
	hasSeenPlayer = true;
}

Player::Player(const Player& player)
{
	displayChar = Globals::GetPlayerDisplayChar();
	goldVal = player.goldVal;
	health = player.health;
	minDamage = player.minDamage;
	maxDamage = player.maxDamage;
	currentRow = player.currentRow;
	currentCol = player.currentCol;
	canMoveThrough = false;
	type = GameObjects::player;
	damageTaken = player.damageTaken;
	stepsTaken = player.stepsTaken;
	srand(time(NULL));
}

Player::~Player()
{
}

/* Modified from: http://www.roguebasin.com/index.php?title=LOS_by_Odd */
void Player::CalculateFov()
{
	int x, y;

	for (double f = 0; f < 3.14 * 2; f += 0.05) {
		x = int(radiusFov*cos(f)) + currentCol;
		y = int(radiusFov*sin(f)) + currentRow;
		DrawlineMod(currentCol, currentRow, x, y);
	}
}

void Player::DrawlineMod(int x, int y, int x2, int y2) {
	int dx = abs(x - x2);
	int dy = abs(y - y2);
	double s = double(.10 / (dx>dy ? dx : dy));
	double t = 0.0;
	while (t < 1.00) {
		dx = int((1.00 - t)*x + t*x2);
		dy = int((1.00 - t)*y + t*y2);
		if (BoardManager::Instance()->GetTile(dy, dx)->displayChar != _WALL_CHAR) {
			BoardManager::Instance()->UpdatePlayerVision(dy, dx);
		}
		else {
			BoardManager::Instance()->UpdatePlayerVision(dy, dx);
			return;
		}
		t += s;
	}
}
/* End section modified from: http://www.roguebasin.com/index.php?title=LOS_by_Odd */

// Check if movement is possible in given direction
bool Player::AttemptMove(const int& yDir,const int& xDir)
{

	int newRow = currentRow + yDir;
	int newCol = currentCol + xDir;

	return BoardManager::Instance()->CanMove(newRow, newCol);
}

// Move player in specified direction
void Player::MovePiece(const int& yDir,const int& xDir)
{
	int newRow = currentRow + yDir;
	int newCol = currentCol + xDir;

	BoardManager::Instance()->MovePiece(currentRow, currentCol, newRow, newCol);
}

// Attempt an attack for the player
Mover* Player::AttemptAttack(const int& yDir,const int& xDir)
{
	bool successfulAttack = false;
	int newRow = currentRow + yDir;
	int newCol = currentCol + xDir;
	return BoardManager::Instance()->CanPlayerAttack(newRow, newCol);
	
}

//Atack the specified piece
void Player::Attack(Mover& hitCollision)
{
	int damage = (rand() % (maxDamage - minDamage)) + minDamage;
	bool isDead = hitCollision.TakeDamage(damage);
	string output = "Player attacked enemy for: ";
	output = output + std::to_string(damage);
	BoardManager::Instance()->AddPrintAction(output);
	if (isDead)
	{
		output = "Player killed enemy: ";
		output = output + hitCollision.displayChar;;
		BoardManager::Instance()->AddPrintAction(output);
		BoardManager::Instance()->DestroyPiece(&(hitCollision));
	}
}

Interactable* Player::AttemptInteraction(const int& yDir,const int& xDir)
{
	int newRow = currentRow + yDir;
	int newCol = currentCol + xDir;
	return BoardManager::Instance()->CanPlayerInteract(newRow, newCol);
}

void Player::PerformInteraction(Interactable& interactable)
{
	AddGoldToTotal(interactable.Interact());
}

bool Player::IsPlayerDead() 
{
	if (health <= 0)
	{
		return true;
	}
	return false;
}


