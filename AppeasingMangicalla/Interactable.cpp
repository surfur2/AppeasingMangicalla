#include "Interactable.h"



Interactable::Interactable(int cRow, int cCol) : GameObject(cRow, cCol)
{
	canMoveThrough = false;
}


Interactable::~Interactable()
{
}
