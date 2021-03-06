#include "Globals.h"

using namespace std;

int Globals::rows = 0;
int Globals::cols = 0;
vector<vector<int>> Globals::map;

char Globals::playerDisplayChar;
int Globals::playerGoldVal;
int Globals::playerHealth;
int Globals::playerMinDamage;
int Globals::playerMaxDamage;
int Globals::playerFov;

char Globals::dustBunnyDisplayChar;
int Globals::dustBunnyGoldVal;
int Globals::dustBunnyHealth;
int Globals::dustBunnyMinDamage;
int Globals::dustBunnyMaxDamage;
int Globals::dustBunnyFov;

char Globals::spiderDisplayChar;
int Globals::spiderGoldVal;
int Globals::spiderHealth;
int Globals::spiderMinDamage;
int Globals::spiderMaxDamage;
int Globals::spiderFov;

char Globals::mangicallaDisplayChar;
int Globals::mangicallaGoldVal;
int Globals::mangicallaHealth;
int Globals::mangicallaMinDamage;
int Globals::mangicallaMaxDamage;


void Globals::DestroyGlobals()
{
	for (int i = 0; i < map.size(); i++)
		map[i].clear();
}

