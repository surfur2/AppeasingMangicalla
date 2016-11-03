#include "EmptySpace.h"

EmptySpace::EmptySpace(int cRow, int cCol) : GameObject(cRow, cCol)
{
	displayChar = _EMPTY_SPACE;
	canMoveThrough = _CAN_MOVE_THROUGH;
	type = GameObjects::empty;
}


EmptySpace::~EmptySpace()
{
}
