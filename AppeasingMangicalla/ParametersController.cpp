#include "ParametersController.h"

using namespace std;

ParametersController* ParametersController::fileReader = nullptr;

ParametersController::ParametersController(string newFileName)
{
	fileName = newFileName;
}


ParametersController::~ParametersController() {	}

void ParametersController::InitializeParameterReader(string fileName)
{
	if (fileReader == nullptr)
		fileReader = new ParametersController(fileName);
	else
	{
		DestroyParameterReader();
		fileReader = new ParametersController(fileName);
	}
}

void ParametersController::DestroyParameterReader() 
{
	delete ParametersController::fileReader;
	ParametersController::fileReader == nullptr;
}

void ParametersController::ReadParameters()
{
	int height = 0;
	int width = 0;
	vector<vector<int>> map;
	

	// Read parameters from file
	string parameter;
	ifstream myfile(fileReader->fileName);
	bool playing = true;
	int i = 0;
	if (myfile)
	{
		while (std::getline(myfile, parameter))
		{

			if (i == 0)
			{
				int pos = parameter.find('-');
				string params = parameter.substr(pos + 1, parameter.length() - pos);
				pos = params.find('/');
				Globals::rows = stoi(params.substr(0, pos), nullptr);
				Globals::cols = stoi(params.substr(pos + 1, params.length() - pos), nullptr);
			}
			else if (i == 1)
			{
				int pos1 = parameter.find('-');
				string params = parameter.substr(pos1 + 1, parameter.length() - pos1);

				pos1 = params.find('/');
				Globals::playerDisplayChar = params[0];

				int pos2 = params.find('/', pos1 + 1);
				Globals::playerGoldVal = stoi(params.substr(pos1 + 1, pos2), nullptr);

				pos1 = params.find('/', pos2 + 1);
				Globals::playerHealth = stoi(params.substr(pos2 + 1, pos1), nullptr);

				pos2 = params.find('/', pos1 + 1);
				Globals::playerMinDamage = stoi(params.substr(pos1 + 1, pos2), nullptr);

				pos1 = params.find('/', pos2 + 1);
				Globals::playerMaxDamage = stoi(params.substr(pos2 + 1, pos1), nullptr);
			}
			else if (i == 2)
			{
				int pos1 = parameter.find('-');
				string params = parameter.substr(pos1 + 1, parameter.length() - pos1);

				pos1 = params.find('/');
				Globals::dustBunnyDisplayChar = params[0];

				int pos2 = params.find('/', pos1 + 1);
				Globals::dustBunnyGoldVal = stoi(params.substr(pos1 + 1, pos2), nullptr);

				pos1 = params.find('/', pos2 + 1);
				Globals::dustBunnyHealth = stoi(params.substr(pos2 + 1, pos1), nullptr);

				pos2 = params.find('/', pos1 + 1);
				Globals::dustBunnyMinDamage = stoi(params.substr(pos1 + 1, pos2), nullptr);

				pos1 = params.find('/', pos2 + 1);
				Globals::dustBunnyMaxDamage = stoi(params.substr(pos2 + 1, pos1), nullptr);
			}
			else if (i == 3)
			{
				int pos1 = parameter.find('-');
				string params = parameter.substr(pos1 + 1, parameter.length() - pos1);

				pos1 = params.find('/');
				Globals::mangicallaDisplayChar = params[0];

				int pos2 = params.find('/', pos1 + 1);
				Globals::mangicallaGoldVal = stoi(params.substr(pos1 + 1, pos2), nullptr);

				pos1 = params.find('/', pos2 + 1);
				Globals::mangicallaHealth = stoi(params.substr(pos2 + 1, pos1), nullptr);

				pos2 = params.find('/', pos1 + 1);
				Globals::mangicallaMinDamage = stoi(params.substr(pos1 + 1, pos2), nullptr);

				pos1 = params.find('/', pos2 + 1);
				Globals::mangicallaMaxDamage = stoi(params.substr(pos2 + 1, pos1), nullptr);
			}
			else
			{
				vector<int> temp;
				for (int k = 0; k < (int)parameter.length(); k++)
					temp.push_back(parameter[k] - '0');
				Globals::map.push_back(temp);
			}
			i++;
		}
		myfile.close();
	}
}

void ParametersController::ReadIntroduction()
{
	string line;
	ifstream myfile(fileReader->fileName);

	while (myfile)
	{
		while (std::getline(myfile, line))
		{
			cout << line << endl;
		}

		myfile.close();
	}

	system("PAUSE");
}


	
