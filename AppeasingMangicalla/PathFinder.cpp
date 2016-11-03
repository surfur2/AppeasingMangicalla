#include "PathFinder.h"
//#include <vector>



PathFinder::PathFinder(int x1, int y1, int x2, int y2) : startX(x1), startY(y1), endX(x2), endY(y2)
{
	ast.open.top = -1;
	ast.closed.top = -1;
	AddInAstarOpen(ast, x1, y1);
}

PathFinder::~PathFinder()
{
}

void PathFinder::Add(Stack_int_pairs stack, int x, int y)
{
	stack.top++;
	stack.list[stack.top] = std::make_pair(x, y);
}

void PathFinder::AddInAstarOpen(Astar ast, int x, int y)
{
	Add(ast.open, x, y);
	
	if (ast.open.top == 0)
		return;
	//sort in order of F value priority
	for (int i = 0; i <= ast.open.top; i++) 
	{
		for (int j = 0; j <= ast.open.top - 1; j++)
		{
			if (ast.fVal[ast.open.list[j].first, ast.open.list[j].second] > ast.fVal[ast.open.list[j+1].first, ast.open.list[j+1].second])
			{
				std::pair<int, int> temp = ast.open.list[j];
				ast.open.list[j] = ast.open.list[j+1];
				ast.open.list[j + 1] = temp;
			}
		}
	}
}



