#pragma once
#include "GameObject.h"

#define _FLOOR_CHAR '.'

/* Tile that defines the 'inside' portion of the mansion.*/
class Floor :
	public GameObject
{
public:
	Floor(int cRow, int cCol);
	~Floor();
};

