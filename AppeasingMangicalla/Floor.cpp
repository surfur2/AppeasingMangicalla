#include "Floor.h"

Floor::Floor(int cRow,int cCol) : GameObject(cRow, cCol)
{
	displayChar = _FLOOR_CHAR;
	canMoveThrough = _CAN_MOVE_THROUGH;
	type = GameObjects::floor;
}


Floor::~Floor()
{
}

