#pragma once
#include "DustBunny.h"
class DustBunnySmart :
	public DustBunny
{
public:
	DustBunnySmart(int cRow, int cCol);
	~DustBunnySmart();

	// Attempt a move
	bool AttemptMove(const int& playerPosY, const int& playerPosX);
	// Actually move
	void MovePiece();

private:
	std::pair<int, int>& currentMoveTile;
};

