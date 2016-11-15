#include "Wall.h"

Wall::Wall(int cRow, int cCol) : GameObject (cRow, cCol)
{
	displayChar = _WALL_CHAR;
	canMoveThrough = _CANNOT_MOVE_THROUGH;
	type = GameObjects::wall;
}


Wall::~Wall()
{
}
