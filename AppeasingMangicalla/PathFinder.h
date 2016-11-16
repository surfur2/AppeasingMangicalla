#pragma once
#include <utility>
#define MAX_HEIGHT_ASTAR 100
#define MAX_WIDTH_ASTAR 100

struct Stack_int_pairs
{
	std::pair<int, int> list[MAX_HEIGHT_ASTAR * MAX_WIDTH_ASTAR];
	int top;
};

struct Astar_tile
{
	int fVal;
	int gVal;
	int hVal;
	std::pair<int, int> parent;
};

struct Astar
{
	//std::vector<std::vector<int*>> fVal;
	//std::vector<std::vector<int*>> gVal;
	//std::vector<std::vector<int*>> hVal;
	Astar_tile tiles[MAX_HEIGHT_ASTAR][MAX_WIDTH_ASTAR];
	Stack_int_pairs open;
	Stack_int_pairs closed;
	Stack_int_pairs path;
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

	Stack_int_pairs& FindPath();

private:
	void Add(Stack_int_pairs& stack, int x, int y);
	void Delete(Stack_int_pairs& stack, std::pair<int, int> pairToDelete);
	void AddInAstarOpen(int x, int y);
	std::pair<int, int> Pop(Stack_int_pairs& stack);
	bool FindInStack(Stack_int_pairs& stack, std::pair<int, int>& tile) const;
	void Sort(Stack_int_pairs& stack);
	void CalculatePath();
	int Calc_hval(int x, int y);
	int Calc_gval(int x, int y);
	int Calc_fval(int hVal, int gVal);
	void CalculateValuesforTile(int x, int y);
	void CheckCalculatedValues(int xBeingChecked, int yBeingChecked, std::pair<int, int> currentTilePos);
};

