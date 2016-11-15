#include "Mover.h"
#include "BoardManager.h"
#include "Wall.h"
#include <math.h>

Mover::Mover(int cRow, int cCol) : GameObject(cRow, cCol)
{
	hasMoved = false;
	canMoveThrough = false;
}

/* Modified from: http://www.roguebasin.com/index.php?title=LOS_by_Odd */
void Mover::CalculateFov()
{
	int x, y;

	for (double f = 0; f < 3.14 * 4; f += 0.05) {
		x = int(radiusFov*cos(f)) + currentCol;
		y = int(radiusFov*sin(f)) + currentRow;
		drawline_mod(currentCol, currentRow, x, y);
	}
}

void Mover::drawline_mod(int x, int y, int x2, int y2) {
	int dx = abs(x - x2);
	int dy = abs(y - y2);
	double s = double(.10 / (dx>dy ? dx : dy));
	double t = 0.0;
	while (t < 1.000000) {
		dx = int((1.000000 - t)*x + t*x2);
		dy = int((1.000000 - t)*y + t*y2);
		if (BoardManager::Instance()->GetTile(dy, dx)->displayChar != _WALL_CHAR) {
			BoardManager::Instance()->UpdatePlayerVision(dy, dx);
		}
		else {
			BoardManager::Instance()->UpdatePlayerVision(dy, dx);
			return;
		}
		t += s;
	}
}

Mover::Mover()
{

}


Mover::~Mover()
{
}
