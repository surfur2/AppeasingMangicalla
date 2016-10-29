#pragma once
#include "GameObject.h"

#define _WALL_CHAR '#'

/* Visable class for the walls that define parimeter fo the mansion*/
class Wall :
	public GameObject
{
public:
	Wall(int cRow,int cCol);
	~Wall();
};

