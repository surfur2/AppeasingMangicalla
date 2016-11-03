#include "Wall.h"

Wall::Wall(int cRow, int cCol) : GameObject ()
{
	displayChar = _WALL_CHAR;
	canMoveThrough = _CANNOT_MOVE_THROUGH;
	currentRow = cRow;
	currentCol = cCol;
	type = GameObjects::wall;
}


Wall::~Wall()
{
}
