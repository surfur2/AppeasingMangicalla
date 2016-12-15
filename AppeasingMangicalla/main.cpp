//Resource used for threading: http://www.cplusplus.com/reference/thread/thread/
#include "Globals.h"
#include "BoardManager.h"
#include "WindowController.h"
#include "Player.h"
#include "ParametersController.h"
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <thread>

#define WINDOW_WIDTH 75
#define WINDOW_HEIGHT 100
#define GAME_SPEED 2.5
using namespace std;

#define _INTRO // Can be commented out to skip intro

#define PRINT_INVALID_INPUT() \
	cout << endl; \
	cout << "Invalid input!" << endl; \
	cout << "Please enter a valid move: "; \

static bool playing = true;

int main()
{
	//Read parameters for game
	ParametersController::InitializeParameterReader("parameters.txt");
	ParametersController::ReadParameters();

	// Initialize the window for play
	WindowController::InitializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	// Create the board manager for play. Give main a reference since we will use it so much.
	unique_ptr<BoardManager> brdMgr(BoardManager::Instance());

	// Write the introduction
#ifdef _INTRO
	ParametersController::InitializeParameterReader("Introduction.txt");
	ParametersController::ReadIntroduction();
#endif // _INTRO 

	bool needsHelp = true;
	bool needsKey = false;

	//Timer using a thread
	time_t timer;
	thread TimeThread([&]() {
		time_t oldTime = time(&timer);
		while (playing)
		{
			time_t currentTime = time(&timer);
			if (difftime(currentTime, oldTime) >= GAME_SPEED)
			{
				brdMgr->game_time--;
				oldTime = currentTime;
			}
			else if (brdMgr->game_time <= 0)
			{
				playing = false;
				auto endGame = []() {
					system("CLS"); 
					cout << "Mangicalla's patience has its limits... You have tested them beyond the limits of wisdom.\nNext time consider your actions more closely before angering a powerful wizard." << endl; 
				};
				endGame();
				exit(0);
				return;
			}
		}
	});


	// Main game loop
	while (playing)
	{

		char temp;
		bool validInput = false;

		brdMgr->WriteGrid(needsHelp, needsKey);
		needsHelp = false;
		needsKey = false;
		int i = 0;
		// Get input from player
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
			playing = false;
			break;
		}
	}


	// Time to cleanup!
	//Joining TimeThread so that main waits for TimeThread to finish before exiting.
	TimeThread.join();
	ParametersController::DestroyParameterReader();
	WindowController::DestroyWindow();
	Globals::DestroyGlobals();

	return 0;
}
