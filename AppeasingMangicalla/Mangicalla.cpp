#include "Globals.h"
#include "Mangicalla.h"
#include "BoardManager.h"
#include <string>


Mangicalla::Mangicalla(int cRow, int cCol)
{
	displayChar = Globals::GetMangicallaDisplayChar();
	goldOnHand = Globals::GetMangicallaGoldVal();
	currentRow = cRow;
	currentCol = cCol;
	canMoveThrough = false;
	type = GameObjects::mangicalla;
}


Mangicalla::~Mangicalla()
{
}

int Mangicalla::Interact()
{
	int goldReturned = 0;

	if (BoardManager::Instance()->AreEnemiesDead())
	{
		BoardManager::Instance()->AddPrintAction("Mangicalla: 'You have done as I have asked... good!'");
		BoardManager::Instance()->AddPrintAction("Mangicalla: 'You found treasure while cleaning the house? It is of little consequence!'");
		BoardManager::Instance()->AddPrintAction("Mangicalla: 'As a generous host, I not only give you the gift of your life, but also this rather large bonus!'");

		goldReturned = CalculateGoldForPlayer();
		string bonusGoldStr = "Mangicalla givs you ";
		bonusGoldStr.append(std::to_string(goldReturned));
		bonusGoldStr += " additional gold";

		BoardManager::Instance()->AddPrintAction(bonusGoldStr);
		BoardManager::Instance()->AddPrintAction("Mangicalla: 'Now.... BEGONE!");

		BoardManager::Instance()->GameIsOver();
	}
	else
	{
		BoardManager::Instance()->AddPrintAction("Mangicalla: 'You dare come back to me before the job is complete?!'");
		BoardManager::Instance()->AddPrintAction("Mangicalla: 'Make sure all the check every nook and crany if you ever \nexpect to make it out of here alive!'");
	}

	return goldReturned;
}

int Mangicalla::CalculateGoldForPlayer()
{
	return goldOnHand - BoardManager::Instance()->GetPlayerSteps() - BoardManager::Instance()->GetPlayerDamageTaken();
}
