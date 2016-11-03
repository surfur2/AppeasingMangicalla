#pragma once
#include <utility>
#define MAX_HEIGHT_ASTAR 100
#define MAX_WIDTH_ASTAR 100

struct Stack_int_pairs
{
	std::pair<int, int> list[MAX_HEIGHT_ASTAR * MAX_WIDTH_ASTAR];
	int top;
};

struct Astar
{
	//std::vector<std::vector<int*>> fVal;
	//std::vector<std::vector<int*>> gVal;
	//std::vector<std::vector<int*>> hVal;
	int fVal[MAX_WIDTH_ASTAR][MAX_HEIGHT_ASTAR] = { 0 };
	int gVal[MAX_WIDTH_ASTAR][MAX_HEIGHT_ASTAR] = { 0 };
	int hVal[MAX_WIDTH_ASTAR][MAX_HEIGHT_ASTAR] = { 0 };
	Stack_int_pairs open;
	Stack_int_pairs closed;
};

class PathFinder
{
public:
	Astar ast;
	int startX;
	int startY;
	int endX;
	int endY;

	PathFinder(int x1, int y1, int x2, int y2);
	~PathFinder();

private:
	void Add(Stack_int_pairs stack, int x, int y);
	void AddInAstarOpen(Astar ast, int x, int y);
};

