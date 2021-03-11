#pragma once
#include "Krpch.h"
#include "DataStruct.h"
#include "MolecularCalculation.h"
//user input handler not developed yet

class Application : MolecularCalculation
{
private:
	bool loaded = false;
	MolecularCalculation molecule0;
	
public:

	void run();
	bool stringComparison(const std::string& userInput, std::string comp);
	void onHelp(const std::string& userInput);
	void hydrogenoid(const std::string &userInput);

	void loadModel(const std::string& userInput);


	parameters tokenize(const std::string userInput, const std::string& keyword);
};

