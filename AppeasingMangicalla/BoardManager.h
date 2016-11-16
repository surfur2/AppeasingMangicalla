#pragma once
#include "GameObject.h"
#include "Mover.h"
#include "Player.h"
#include "Mangicalla.h"
#include <vector>

using namespace std;

class Mover;
class Player;
class Mangicalla;

/* Contains the definitions for the game board as well as manages the current state of the game.*/
class BoardManager {
private:
	~BoardManager();
	BoardManager();
	BoardManager(const BoardManager& brdMgr); // SEE README.txt
	void operator=(const BoardManager& rhs); // See README.txt

	// Attributes
	bool gameIsOver;
	Player* player;
	Mangicalla* mangicalla;
	vector<Mover*> enemies;
	vector<Spider*> spiders;
	vector<vector<GameObject*>> board;
	vector<string> printableActions; // Stack of statements to print on next grid write
	vector<std::pair<std::pair<int, int>, char>> tempChars;
	static BoardManager* instance; // Intance of singleton

	// Enemy movements and attacks
	void HaveEnemiesAttack();
	void HaveEnemiesMove();
	void ResetVision();
	void PrintSpiderPaths();
	void ResetSpiderPaths();
public:
	// Accessor/destructor for singleton
	static BoardManager* Instance();
	static void DestroyInstance();

	// Movement for all pieces on the board
	bool CanMove(const int& nRow, const int& nCol);
	bool MovePiece(const int cRow, const int cCol, const int nRow, const int nCol);

	// Check the board state for valid types of actions
	Mover* CanPlayerAttack(const int& nRow, const int& nCol);
	Interactable* CanPlayerInteract(const int& nRow, const int& nCol);
	Player* CanEnemyAttack(const int& nRow, const int& cCol);
	bool CanEnemySeePlayer(Mover* enemy);
	void UpdatePlayerVision(int cRow, int cCol);

	// Remove a piece from the board if it was destroyed
	void DestroyPiece(Mover* enemy);

	// Validate player action, and execute if it is. Otherwise return false.
	bool AttemptPlayerAction(const int& nRow, const int& nCol);
	
	// Rewrite the grid and the statements at the bottom
	void WriteGrid(const bool& needsHelp, const bool& needsKey);
	void WriteGameExit();
	// Add a statement that will be printed on the next gridWrite
	void AddPrintAction(string action) { printableActions.insert(printableActions.begin(), action); };

	// Inline definitions for various callthroughs.
	bool IsPlayerDead() { 
		if (player == nullptr)
			return true;
		return player->IsPlayerDead(); 
	};
	int GetPlayerSteps() { return player->GetStepsTaken(); };
	int GetPlayerDamageTaken() { return player->GetDamageTaken(); };
	void AddPlayerDamageTaken(int damage) { player->AddDamageTaken(damage); };
	void GameIsOver() { gameIsOver = true; };
	bool IsGameOver() { return gameIsOver; };
	bool AreEnemiesDead() { return enemies.empty(); };
	bool IsPlayerTile(int cRow, int cCol) { return (player->currentRow == cRow && player->currentCol == cCol); };
	GameObject* GetTile(const int& nRow, const int& nCol);
};