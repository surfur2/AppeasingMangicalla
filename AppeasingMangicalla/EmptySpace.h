#pragma once
#include "GameObject.h"

#define _EMPTY_SPACE ' '

/* The empty space on the map.
   It is a valid tile type to move through.
   May consider using for 'secret passages' in the future.*/
class EmptySpace :
	public GameObject
{
public:
	// Need the current position of an object
	EmptySpace(int cRow, int cCol);
	// Default destructor since to 'complex' types
	~EmptySpace();
};

