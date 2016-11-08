#include "Mover.h"
#include "BoardManager.h"

Mover::Mover(int cRow, int cCol) : GameObject(cRow, cCol)
{
	hasMoved = false;
	canMoveThrough = false;
}

void Mover::CalculateFov()
{
	for (int i = (currentRow - radiusFov); i <= currentRow + radiusFov; i++)
	{
		if (i >= 0 && i < Globals::GetRows())
		{
			for (int k = (currentCol - radiusFov); k <= currentCol + radiusFov; k++)
			{
				if (k >= 0 && k < Globals::GetCols())
				{
					BoardManager::Instance()->UpdatePlayerVision(i, k);
				}
			}
		}
	}
}

Mover::Mover()
{

}


Mover::~Mover()
{
}
