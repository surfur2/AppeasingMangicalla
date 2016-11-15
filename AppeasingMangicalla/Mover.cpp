#include "Mover.h"
#include "BoardManager.h"

Mover::Mover(int cRow, int cCol) : GameObject(cRow, cCol)
{
	hasMoved = false;
	canMoveThrough = false;
}

Mover::Mover()
{

}


Mover::~Mover()
{
}
