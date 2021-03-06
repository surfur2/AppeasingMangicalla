#include "Globals.h"
#include "Floor.h"
#include "Wall.h"
#include "EmptySpace.h"
#include "BoardManager.h"
#include "Mangicalla.h"
#include "DustBunny.h"
#include "Spider.h"
#include "WindowController.h"
#include <iostream>

#define GAME_TIME 150

using namespace std;

BoardManager* BoardManager::instance = nullptr;

BoardManager* BoardManager::Instance()
{
	if (instance == nullptr)
		instance = new BoardManager ();

	return instance;
}

BoardManager::BoardManager()
{
	writeGridLock = false;
	game_time = GAME_TIME;
	gameIsOver = false;
	Mover* enemy = nullptr;
	const vector<vector<int>> tempMap = Globals::GetMap();

	for (int i = 0; i < Globals::GetRows(); i++)
	{
		vector<GameObject*> row;
		for (int k = 0; k < Globals::GetCols(); k++)
		{
			switch (tempMap[i][k])
			{
				case GameObjects::empty:
					row.push_back(new EmptySpace(i, k));
					break;
				case GameObjects::floor: 
					row.push_back(new Floor(i, k));
					break;
				case GameObjects::wall: 
					row.push_back(new Wall(i, k)); 
					break;
				case GameObjects::player:
					player = new Player(i, k);
					row.push_back(player);
					break;
				case GameObjects::mangicalla:
					mangicalla = new Mangicalla(i, k);
					row.push_back(mangicalla);
					break;
				case GameObjects::dustbunny:
					enemy = new DustBunny(i, k);
					enemies.push_back(enemy);
					row.push_back(enemy);
					break;
				case GameObjects::spider:
					Spider* spider = new Spider(i, k);
					enemies.push_back(spider);
					spiders.push_back(spider);
					row.push_back(spider);
					break;
			}
		}
		board.push_back(row);
	}
}

BoardManager::~BoardManager()
{
	GameObject* temp;
	for (int i = 0; i < Globals::GetRows(); i++)
	{
		for (int k = 0; k < Globals::GetCols(); k++)
		{
			temp = board[i][k];
			delete temp;
		}
	}

	if (!printableActions.empty())
	{
		printableActions.clear();
	}

	instance = nullptr;
}

void BoardManager::WriteGrid(const bool& needsHelp, const bool& needsKey)
{
	if(!writeGridLock)
	{
		writeGridLock = true;
		system("CLS");
		player->CalculateFov();

		PrintSpiderPaths();

		for (int i = 0; i < Globals::GetRows(); i++)
		{
			for (int k = 0; k < Globals::GetCols(); k++)
			{
				if (board[i][k]->playerCanSee)
					cout << board[i][k]->displayChar;
				else
					cout << " ";
			}

			cout << endl;
		}

		cout << "Results of Action: " << endl;
		cout << endl;
		// Print the relavent player stats
		cout << *player;
		cout << "Mangicalla's Patience: " << game_time << endl;

		// Print previous actions
		while (!printableActions.empty())
		{
			cout << printableActions.back().c_str() << endl;
			printableActions.pop_back();
		}

		cout << endl;
		// Print help
		if (needsHelp)
		{
			cout << "Movement: w-up, a-left, s-down, d-right." << endl;
			cout << "Attack opponent: attempt to move into their square." << endl;
			cout << "Interact with object: attempt to move into its square." << endl;
			cout << "Exit Game: x" << endl;
		}
		// Print key
		else if (needsKey)
		{
			cout << "Player: " << Globals::GetPlayerDisplayChar() << endl;
			cout << "Mangicalla: " << Globals::GetMangicallaDisplayChar() << endl;
			cout << "'Dustbunnies': " << Globals::GetDustBunnyDisplayChar() << endl;
			cout << "'Spiders': " << Globals::GetSpiderDisplayChar() << endl;
			cout << "Spider Pathing Char: " << 'X' << endl;

		}

		// Print the help to help
		cout << endl;
		cout << "To see commands again: h" << endl;
		cout << "To see key of objects: k" << endl;

		auto gotoxy = [](int x, int y) {
			static HANDLE h = WindowController::windowInstance->hConOut;
			if (!h)
				h = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD c = { x, y };
			SetConsoleCursorPosition(h, c);
		};

		//Print Time
		gotoxy(WindowController::windowInstance->window_width - 1, WindowController::windowInstance->window_height);

		gotoxy(1, WindowController::windowInstance->window_height);

		cout << endl;
		cout << "Please enter a move for player: ";

		ResetSpiderPaths();
		writeGridLock = false;
	}
}

void BoardManager::PrintSpiderPaths()
{
	for (int i = 0; i < spiders.size(); i++)
	{
		for (int k = 1; k + 1 < spiders[i]->currentPathList.size(); k++)
		{
			std::pair<int, int> nextTile = spiders[i]->currentPathList[k];
			std::pair<std::pair<int, int>, char> dictionaryEntry = make_pair(nextTile, board[nextTile.second][nextTile.first]->displayChar);
			tempChars.push_back(dictionaryEntry);
			board[nextTile.second][nextTile.first]->displayChar = 'X';
		}
		spiders[i]->currentPathList.clear();
	}
}

void BoardManager::ResetSpiderPaths()
{
	for (int i = 0; i < tempChars.size(); i++)
	{
		std::pair<std::pair<int, int>, char> dictionaryEntry = tempChars[i];
		board[dictionaryEntry.first.second][dictionaryEntry.first.first]->displayChar = dictionaryEntry.second;
	}
	tempChars.clear();
}

void BoardManager::WriteGameExit()
{
	system("CLS");
	cout << "Conclusion: " << endl;
	cout << endl;
	while (!printableActions.empty())
	{
		cout << printableActions.back().c_str() << endl;
		printableActions.pop_back();
	}

	cout << endl;

	if (!IsPlayerDead())
		cout << "Total player gold for play through was: " << player->goldVal << endl;
	system("PAUSE");
}

bool BoardManager::MovePiece(const int cRow, const int cCol, const int nRow, const int nCol)
{
	GameObject* temp1 = board[cRow][cCol];
	GameObject* temp2 = board[nRow][nCol];
	temp1->UpdatePos(nRow, nCol);
	temp2->UpdatePos(cRow, cCol);
	board[cRow][cCol] = board[nRow][nCol];
	board[nRow][nCol] = temp1;
	
	return true;
}

bool BoardManager::CanMove(const int& nRow, const int& nCol)
{
	return (board[nRow][nCol]->canMoveThrough);
}

Mover* BoardManager::CanPlayerAttack(const int& nRow, const int& nCol)
{
	if (board[nRow][nCol]->IsEnemy())
	{
		return dynamic_cast<Mover*>(board[nRow][nCol]);
	}

	return nullptr;
}

Interactable* BoardManager::CanPlayerInteract(const int& nRow, const int& nCol)
{
	if (board[nRow][nCol]->IsInteractable())
		return mangicalla;

	return nullptr;
}

Player* BoardManager::CanEnemyAttack(const int& nRow, const int& nCol)
{
	if (board[nRow][nCol]->IsPlayer())
	{
		return player;
	}

	return nullptr;
}

bool BoardManager::AttemptPlayerAction(const int& yDir, const int& xDir)
{
	bool playerCanAttack = false;
	bool playerCanMove = false;
	bool playerCanInteract = false;

	// Check for a valid player actions. If there is no valid player action, then the enemies will not do anything.
	Mover* hitCollision = player->AttemptAttack(yDir, xDir);
	Interactable* interactable = player->AttemptInteraction(yDir, xDir);
	if (hitCollision != nullptr)
		playerCanAttack = true;
	if (interactable != nullptr && !playerCanAttack)
		playerCanInteract = true;
	if (player->AttemptMove(yDir, xDir) && !playerCanAttack && !playerCanInteract)
		playerCanMove = true;

	// We need to make sure that there was some sort of valid input before allowing enemies to move
	if (playerCanAttack || playerCanMove || playerCanInteract)
	{
		// The flow of action is player attack->enemy attack->player move->enemies move
		if (playerCanAttack)
			player->Attack(*hitCollision);

		if (playerCanInteract)
			player->PerformInteraction(*interactable);

		// Enemies attack
		HaveEnemiesAttack();
		if (player->IsPlayerDead())
			return true;

		if (playerCanMove)
			player->MovePiece(yDir, xDir);

		// Enemies move
		HaveEnemiesMove();

		player->AddStepTaken();
		ResetVision();
		return true;
	}

	return false;
}

// Loop all enemies and attempt an attack
void BoardManager::HaveEnemiesAttack()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		Mover* player = enemies[i]->AttemptAttack(enemies[i]->currentRow, enemies[i]->currentCol);
		if (player != nullptr)
		{
			enemies[i]->Attack(*player);
			enemies[i]->hasMoved = true;
		}
	}
}

// If they have not already acted, then move enemies
void BoardManager::HaveEnemiesMove()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i]->hasMoved && enemies[i]->AttemptMove(player->currentRow, player->currentCol))
			enemies[i]->MovePiece(enemies[i]->currentRow, enemies[i]->currentCol);

		// We also reset the movement here
		enemies[i]->hasMoved = false;
	}

}


// Destroy an enemy from the game
void BoardManager::DestroyPiece(Mover* enemy)
{
	auto temp = find(enemies.begin(), enemies.end(), enemy);
	auto tempSpider = find(spiders.begin(), spiders.end(), enemy);

	if (tempSpider != spiders.end())
	{
		swap(*tempSpider, spiders.back());
		spiders.pop_back();
	}
	// Remove from current enemy list
	if (temp != enemies.end())
	{
		swap(*temp, enemies.back());
		enemies.pop_back();
	}

	// Replace with a floor tile
	board[enemy->currentRow][enemy->currentCol] = new Floor(enemy->currentRow, enemy->currentCol);

	// Delete the memory
	delete enemy;
}

BoardManager::BoardManager(const BoardManager& brdMgr)
{
	
	// Copy the board and all objects on board
	for (int i = 0; i < brdMgr.board.size(); i++)
	{
		vector<GameObject*> row;

		for (int k = 0; k < brdMgr.board[i].size(); k++)
		{
			switch (brdMgr.board[i][k]->type)
			{
			case GameObjects::empty:
				row.push_back(new EmptySpace(*static_cast<EmptySpace*>(brdMgr.board[i][k])));
				break;
			case GameObjects::floor:
				row.push_back(new Floor(*static_cast<Floor*>(brdMgr.board[i][k])));
				break;
			case GameObjects::wall:
				row.push_back(new Wall(*static_cast<Wall*>(brdMgr.board[i][k])));
				break;
			case GameObjects::player:
				// Deep copy the player
				player = new Player(*brdMgr.player);
				row.push_back(player);
				break;
			case GameObjects::mangicalla:
				// Deep copy since Mangicalla has no 'complex' data types
				mangicalla = new Mangicalla(*brdMgr.mangicalla);
				row.push_back(mangicalla);
				break;
			case GameObjects::dustbunny:
				// Deep copy since DustBunny has no 'complex' data types
				Mover* enemy = new DustBunny(*static_cast<DustBunny*>(brdMgr.board[i][k]));
				enemies.push_back(enemy);
				row.push_back(enemy);
				break;
			}
		}

		board.push_back(row);
	}


	if (!brdMgr.printableActions.empty())
	{
		for (int i = 0; i < brdMgr.printableActions.size(); i++)
			AddPrintAction(brdMgr.printableActions[i]);
	}
}

void BoardManager::operator=(const BoardManager& rhs)
{
	// Clear the enemies out before initializing the board
	enemies.clear();

	// Copy the board and all objects on board
	for (int i = 0; i < board.size(); i++)
	{
		for (int k = 0; k < board[i].size(); k++)
		{
			switch (board[i][k]->type)
			{
			case GameObjects::empty:
				*board[i][k] = *static_cast<EmptySpace*>(rhs.board[i][k]);
				break;
			case GameObjects::floor:
				*board[i][k] = *static_cast<Floor*>(rhs.board[i][k]);
				break;
			case GameObjects::wall:
				*board[i][k] = *static_cast<Wall*>(rhs.board[i][k]);
				break;
			case GameObjects::player:
				*player = *rhs.player;
				*board[i][k] = *player;
				break;
			case GameObjects::mangicalla:
				*mangicalla = *rhs.mangicalla;
				*board[i][k] = *mangicalla;
				break;
			case GameObjects::dustbunny:
				Mover* enemy = nullptr;
				*enemy = *static_cast<DustBunny*>(rhs.board[i][k]);
				*board[i][k] = *enemy;
				enemies.push_back(enemy);
				break;
			}
		}
	}

	// Add the print actions at the end
	printableActions.clear();
	if (!rhs.printableActions.empty())
	{
		for (int i = 0; i < rhs.printableActions.size(); i++)
			AddPrintAction(rhs.printableActions[i]);
	}

}

bool BoardManager::CanEnemySeePlayer(Mover* enemy)
{
	return enemy->hasSeenPlayer;
}

void BoardManager::UpdatePlayerVision(int cRow, int cCol)
{
	board[cRow][cCol]->playerCanSee = true;

	if (board[cRow][cCol]->IsEnemy())
	{
		Mover* temp = dynamic_cast<Mover*>(board[cRow][cCol]);
		temp->hasSeenPlayer = true;
	}
}

void BoardManager::ResetVision()
{
	for (int i = 0; i < board.size(); i++)
	{
		for (int k = 0; k < board[i].size(); k++)
		{
			board[i][k]->playerCanSee = false;
		}
	}
}

GameObject* BoardManager::GetTile(const int& nRow, const int& nCol) {
	if (nRow < Globals::GetRows() && nRow < Globals::GetCols())
		return board[nRow][nCol];
	else
		return nullptr;
}

