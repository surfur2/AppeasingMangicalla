#pragma once
#include "DustBunny.h"
class DustBunnySmart :
	public DustBunny
{
public:
	DustBunnySmart(int cRow, int cCol);
	~DustBunnySmart();

	// Attempt a move
	bool AttemptMove();
	// Actually move
	void MovePiece(const int& playerPosY, const int& playerPosX);
};

