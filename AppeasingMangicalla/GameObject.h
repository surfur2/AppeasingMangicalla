#pragma once

#define _CANNOT_MOVE_THROUGH false
#define _CAN_MOVE_THROUGH true

/* Enum for the types of objects in game.
   This is how the integer map in parameters.txt is turned into a real map.*/
struct GameObjects
{
	enum map {
		empty = 0,
		floor = 1,
		wall = 2,
		player = 3,
		mangicalla = 4,
		dustbunny = 5,
		spider = 6,
		ooze = 7,
		boss = 8
	};
};

/* Base class for every visable object.*/
class GameObject
{
public:
	GameObject(int cRow, int cCol);
	GameObject();
	// Do not want an instance of class, so make it pure virtual
	virtual ~GameObject() = 0;
	bool UpdatePos(int row, int col)
	{
		currentRow = row;
		currentCol = col;

		return true;
	}

	// Is GameObject of type enemy?
	bool IsEnemy()
	{
		return (type == GameObjects::dustbunny || type == GameObjects::boss || type == GameObjects::ooze || type == GameObjects::spider);
	}

	// Is GameObject of type player?
	bool IsPlayer() { return (type == GameObjects::player); }
	
	// Is GameObject of type interactable?
	bool IsInteractable() { return (type == GameObjects::mangicalla); };

	// Atrributes that all disable objects need
	char displayChar;
	bool canMoveThrough;
	bool canBeAttacked;
	bool playerCanSee;
	int currentRow;
	int currentCol;
	int type;
};
