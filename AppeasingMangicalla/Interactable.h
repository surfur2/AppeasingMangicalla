#pragma once
#include "GameObject.h"

/* Pure virtual function that defines base behavior for an object to be interactable.*/
class Interactable :
	public GameObject
{
public:
	Interactable(int cRow, int cCol);
	~Interactable();
	virtual int Interact() = 0;
};

