#include "PathFinder.h"
#include <vector>
#include <cmath>
#include "BoardManager.h"



PathFinder::PathFinder(int x1, int y1, int x2, int y2) : startX(x1), startY(y1), endX(x2), endY(y2)
{
	ast.open.top = -1;
	ast.closed.top = -1;
	ast.path.top = -1;
	AddInAstarOpen(x1, y1);
	CalculateValuesforTile(x1, y1);
}

PathFinder::~PathFinder()
{
}

const std::pair<int, int>& PathFinder::FindPath()
{
	ast.tiles[startX][startY].parent = make_pair(-1, -1);
	CalculatePath();

	std::pair<int, int> tilePos = make_pair(endX, endY);

	Add(ast.path, tilePos.first, tilePos.second);

	while (FindInStack(ast.closed, ast.tiles[tilePos.first][tilePos.second].parent))
	{
		tilePos = ast.tiles[tilePos.first][tilePos.second].parent;
		Add(ast.path, tilePos.first, tilePos.second);
	}
	//Pop the current position which in in stack
	Pop(ast.path);

	return ast.path.list[ast.path.top];
}

void PathFinder::Add(Stack_int_pairs& stack, int x, int y)
{
	stack.top++;
	stack.list[stack.top] = std::make_pair(x, y);
}

void PathFinder::Delete(Stack_int_pairs & stack, std::pair<int, int> pairToDelete)
{
	int i = 0;
	for (i = 0; i <= stack.top; i++)
	{
		if (stack.list[i] == pairToDelete)
		{
			break;
		}
	}

	if (i == stack.top)
	{
		return;
	}

	while (i < stack.top)
	{
		stack.list[i] = stack.list[i + 1];
	}
	stack.list[stack.top] = make_pair(0, 0);
	stack.top--;
}

void PathFinder::AddInAstarOpen(int x, int y)
{
	Add(ast.open, x, y);
	
	if (ast.open.top == 0)
		return;
	//sort in order of F value priority
	Sort(ast.open);
	//for (int i = 0; i <= ast.open.top; i++) 
	//{
	//	for (int j = 0; j <= ast.open.top - 1; j++)
	//	{
	//		if (ast.tiles[ast.open.list[j].first][ast.open.list[j].second].fVal < ast.tiles[ast.open.list[j+1].first][ast.open.list[j+1].second].fVal)
	//		{
	//			std::pair<int, int> temp = ast.open.list[j];
	//			ast.open.list[j] = ast.open.list[j+1];
	//			ast.open.list[j + 1] = temp;
	//		}
	//	}
	//}
}

std::pair<int, int> PathFinder::Pop(Stack_int_pairs& stack)
{
	std::pair<int, int> temp = stack.list[stack.top];
	stack.list[stack.top] = std::make_pair(0, 0);
	stack.top--;
	return temp;
}

bool PathFinder::FindInStack(Stack_int_pairs& stack, std::pair<int, int>& tile) const
{
	for (int i = 0; i <= stack.top; i++)
	{
		if (stack.list[i] == tile)
			return true;
	}

	return false;
}


void PathFinder::Sort(Stack_int_pairs& stack)
{
	for (int i = 0; i <= stack.top; i++)
	{
		for (int j = 0; j <= stack.top - i; j++)
		{
			if (CompareSwapValues<int>()(ast.tiles[stack.list[j].first][stack.list[j].second].fVal, ast.tiles[stack.list[j + 1].first][stack.list[j + 1].second].fVal))
			{
				std::pair<int, int> temp = stack.list[j];
				stack.list[j] = stack.list[j + 1];
				stack.list[j + 1] = temp;
			}
		}
	}
}


// Calculate the best path
void PathFinder::CalculatePath()
{
	while (ast.open.top != -1)
	{
		// get the tile with minimum fVal and store its position
		std::pair<int, int> currentTilePos = Pop(ast.open);
		int col = currentTilePos.first;
		int row = currentTilePos.second;

		//Put the tile we got above into the closed stack
		if (FindInStack(ast.closed, currentTilePos))
		{
			Delete(ast.closed, currentTilePos);
		}
		
		Add(ast.closed, currentTilePos.first, currentTilePos.second);

		if (FindInStack(ast.closed, make_pair(endX, endY)))
		{
			break;
		}

		
		// Add adjacent tiles to open list
		// Check tile bellow current tile
		int yBeingChecked = row + 1;
		int xBeingChecked = col;
		
		CheckCalculatedValues(xBeingChecked, yBeingChecked, currentTilePos);

		// Check tile above current tile
		yBeingChecked = row - 1;
		xBeingChecked = col;

		CheckCalculatedValues(xBeingChecked, yBeingChecked, currentTilePos);

		// Check tile left current tile
		yBeingChecked = row;
		xBeingChecked = col - 1;

		CheckCalculatedValues(xBeingChecked, yBeingChecked, currentTilePos);

		// Check tile right current tile
		yBeingChecked = row;
		xBeingChecked = col + 1;

		CheckCalculatedValues(xBeingChecked, yBeingChecked, currentTilePos);
	}
}

void PathFinder::CheckCalculatedValues(int xBeingChecked, int yBeingChecked, std::pair<int, int> currentTilePos)
{
	if (BoardManager::Instance()->CanMove(yBeingChecked, xBeingChecked) || BoardManager::Instance()->IsPlayerTile(yBeingChecked, xBeingChecked))
	{
		if (!FindInStack(ast.open, make_pair(xBeingChecked, yBeingChecked)) && !FindInStack(ast.closed, make_pair(xBeingChecked, yBeingChecked)))
		{
			CalculateValuesforTile(xBeingChecked, yBeingChecked);
			ast.tiles[xBeingChecked][yBeingChecked].parent = currentTilePos;
			AddInAstarOpen(xBeingChecked, yBeingChecked);
		}
		else if (FindInStack(ast.open, make_pair(xBeingChecked, yBeingChecked)))
		{
			if (ast.tiles[xBeingChecked][yBeingChecked].fVal > Calc_fval(Calc_hval(xBeingChecked, yBeingChecked), Calc_gval(xBeingChecked, yBeingChecked)))
			{
				CalculateValuesforTile(xBeingChecked, yBeingChecked);
				ast.tiles[xBeingChecked][yBeingChecked].parent = currentTilePos;
				Sort(ast.open);
			}
		}
		//else if (FindInStack(ast.closed, make_pair(xBeingChecked, yBeingChecked)))
		//{
		//	if (ast.tiles[xBeingChecked][yBeingChecked].fVal > Calc_fval(Calc_hval(xBeingChecked, yBeingChecked), Calc_gval(xBeingChecked, yBeingChecked)))
		//	{
		//		CalculateValuesforTile(xBeingChecked, yBeingChecked);
		//		ast.tiles[xBeingChecked][yBeingChecked].parent = currentTilePos;
		//	}
		//}
	}
}

int PathFinder::Calc_hval(int x, int y)
{
	//ast.tiles[x][y].hVal = abs(endX - x) + abs(endY - y);
	return abs(endX - x) + abs(endY - y);
}

int PathFinder::Calc_gval(int x, int y)
{
	if (x == startX && y == startY)
	{
		//ast.tiles[x][y].gVal = 0;
		return 0;
	}
	float distance = sqrt(pow((x - ast.tiles[x][y].parent.first), 2) + pow((y - ast.tiles[x][y].parent.second), 2));
	if (distance == 1)
	{
		//ast.tiles[x][y].gVal = 10;
		return 10;
	}
	else
	{
		//ast.tiles[x][y].gVal = 14;
		return 14;
	}
}

int PathFinder::Calc_fval(int hVal, int gVal)
{
	return hVal + gVal;
}

// Calculate F, G and H values for tile x,y
void PathFinder::CalculateValuesforTile(int x, int y)
{
	ast.tiles[x][y].hVal = Calc_hval(x, y);
	ast.tiles[x][y].gVal = Calc_gval(x, y);
	ast.tiles[x][y].fVal = Calc_fval(ast.tiles[x][y].hVal, ast.tiles[x][y].gVal);
}





