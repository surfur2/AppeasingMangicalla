#include "Floor.h"

Floor::Floor(int cRow,int cCol)
{
	displayChar = _FLOOR_CHAR;
	canMoveThrough = _CAN_MOVE_THROUGH;
	currentRow = cRow;
	currentCol = cCol;
	type = GameObjects::floor;
}


Floor::~Floor()
{
}

