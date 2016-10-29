#ifndef PARAMETERSCONTROLLER
#define PARAMETERSCONTROLLER

#pragma once
#include "Includes.h"

/* File reading class*/
class ParametersController
{
public:
	static void InitializeParameterReader(string fileName);
	static void DestroyParameterReader();
	static void ReadParameters();
	static void ReadIntroduction();
private:
	ParametersController(string fileName);
	~ParametersController();
	static ParametersController* fileReader;
	string fileName;
};
#endif // !PARAMETERSCONTROLLER

