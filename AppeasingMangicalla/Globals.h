#ifndef GLOBALS
#define GLOBALS

#pragma once
#include <vector>

using namespace std;

/* Global values that are read once from file and then used throughout the program.
   ParametersController is defined as a friend so that it has write access to Globals.
   No other class should have write access.*/
class Globals
{
	friend class ParametersController;
private:
	// BoardManager constants
	static int rows;
	static int cols;
	static vector<vector<int>> map;

	// Player constants
	static char playerDisplayChar;
	static int playerGoldVal;
	static int playerHealth;
	static int playerMinDamage;
	static int playerMaxDamage;

	// DustBunny constants
	static char dustBunnyDisplayChar;
	static int dustBunnyGoldVal;
	static int dustBunnyHealth;
	static int dustBunnyMinDamage;
	static int dustBunnyMaxDamage;

	// mangicalla constants
	static char mangicallaDisplayChar;
	static int mangicallaGoldVal;
	static int mangicallaHealth;
	static int mangicallaMinDamage;
	static int mangicallaMaxDamage;
public:
	static void DestroyGlobals();

	// BoardManager Get constants
	static int GetRows() { return rows; };
	static int GetCols() { return cols; };
	static vector<vector<int>> GetMap() { return map; };

	// Player Get constants
	static char GetPlayerDisplayChar() { return playerDisplayChar; };
	static int GetPlayerGoldVal() { return playerGoldVal; };
	static int GetPlayerHealth() { return playerHealth; };
	static int GetPlayerMinDamage() { return playerMinDamage; };
	static int GetPlayerMaxDamage() { return playerMaxDamage;};

	// DustBunny Get constants
	static char GetDustBunnyDisplayChar() { return dustBunnyDisplayChar; };
	static int GetDustBunnyGoldVal() { return dustBunnyGoldVal; };
	static int GetDustBunnyHealth() { return dustBunnyHealth; };
	static int GetDustBunnyMinDamage() { return dustBunnyMinDamage; };
	static int GetDustBunnyMaxDamage() { return dustBunnyMaxDamage; };

	// DustBunny Get constants
	static char GetMangicallaDisplayChar() { return mangicallaDisplayChar; };
	static int GetMangicallaGoldVal() { return mangicallaGoldVal; };
	static int GetMangicallaHealth() { return mangicallaHealth; };
	static int GetMangicallaMinDamage() { return mangicallaMinDamage; };
	static int GetMangicallaMaxDamage() { return mangicallaMaxDamage; };
};
#endif // !GLOBALS


