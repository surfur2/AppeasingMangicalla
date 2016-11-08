#include "GameObject.h"

GameObject::GameObject(int cRow, int cCol)
{
	playerCanSee = false;
	currentRow = cRow;
	currentCol = cCol;
}

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
}
