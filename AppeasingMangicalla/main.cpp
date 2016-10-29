#include "Globals.h"
#include "BoardManager.h"
#include "WindowController.h"
#include "Player.h"
#include "ParametersController.h"
#include <conio.h>

using namespace std;

#define _INTRO // Can be commented out to skip intro

#define PRINT_INVALID_INPUT() \
	cout << endl; \
	cout << "Invalid input!" << endl; \
	cout << "Please enter a valid move: "; \

int main()
{
	//Read parameters for game
	ParametersController::InitializeParameterReader("parameters.txt");
	ParametersController::ReadParameters();

	// Initialize the window for play
	WindowController::InitializeWindow(75, 100);
	
	// Create the board manager for play. Gice main a reference since we will use it so much.
	BoardManager* brdMgr = BoardManager::Instance();

	// Write the introduction
#ifdef _INTRO
	ParametersController::InitializeParameterReader("Introduction.txt");
	ParametersController::ReadIntroduction();
#endif // _INTRO

	bool needsHelp = true;
	bool needsKey = false;
	bool playing = true;

	// Main game loop
	while (playing)
	{

		bool validInput = false;
		char temp;
		
		// Get input from player
		brdMgr->WriteGrid(needsHelp, needsKey);
		needsHelp = false;
		needsKey = false;
		int i = 0;
		while (!validInput)
		{
			if (i != 0)
			{
				PRINT_INVALID_INPUT();
			}
			temp = _getche();
			switch (temp)
			{
			case 'x':
				playing = false;
				validInput = true;
				break;
			case 'd':
				validInput = brdMgr->AttemptPlayerAction(0, 1);
				break;
			case 's':
				validInput = brdMgr->AttemptPlayerAction(1, 0);
				break;
			case 'a':
				validInput = brdMgr->AttemptPlayerAction(0, -1);
				break;
			case 'w':
				validInput = brdMgr->AttemptPlayerAction(-1, 0);
				break;
			case 'h':
				validInput = true;
				needsHelp = true;
				break;
			case 'k':
				validInput = true;
				needsKey = true;
				break;
			default:
				validInput = false;
				break;
			}
			i++;
		}
			
		// If we are not longer playing, end the game
		if (!playing)
			break;

		// Game ends because player is dead
		if (BoardManager::Instance()->IsPlayerDead())
		{
			brdMgr->AddPrintAction("Enemy killed player!!!");
			brdMgr->AddPrintAction("The forces of uncleanliness were too pungent.");
			brdMgr->AddPrintAction("You meet your final rest amoung the dust and cluter of an unknown mansion...");
			brdMgr->WriteGameExit();
			break;
		}

		// Game ends because the mission was complete
		if (BoardManager::Instance()->IsGameOver())
		{
			brdMgr->WriteGameExit();
			break;
		}
	}

	// Time to cleanup!
	ParametersController::DestroyParameterReader();
	WindowController::DestroyWindow();
	brdMgr->DestroyInstance();
	Globals::DestroyGlobals();
	return 0;
}
