#include "Application.h"
#include "Logging.h"
#include "MolLoader.h"
#include <sstream>



void Application::run()
{
	std::string version = "1.0v";
	std::cout << "loading krabs version: " << version << std::endl;

	

	
	std::cout << "----------------------WELLCOME TO KRABS-----------------\n\n" << std::endl;

	KRABS_INFO("type 'help' for the command list");

	bool panna = true ;
	
	std::string userInput;
	while (getline(std::cin, userInput) ) {
		float result = 0;
		// fix this , try to use char instead of string o something
	
		if (stringComparison(userInput, "quit"))
			break;

		else if (stringComparison(userInput, "load"))
			loadModel(userInput);

		else if (stringComparison(userInput, "help"))
			onHelp(userInput);

		else if (stringComparison(userInput, "hydrogenoid"))
			hydrogenoid(userInput);

		//check the object i need to pass 
		//it compile but the object instance is not passed molecule0 its empty
		else if (stringComparison(userInput, "bond energy") && loaded) {
			molecule0.atomicStretch(result);
			KRABS_INFO("Bond energy:   {0} Kcal/mol", result);
		}

		else if (stringComparison(userInput, "angle energy") && loaded) {
			molecule0.atomicBend(result);
			KRABS_INFO("angle bend energy:   {0} Kcal/mol", result);
		}

		else if (stringComparison(userInput, "van der waals energy") && loaded) {
			molecule0.vanDerVaals(result);
			KRABS_INFO("Bond energy:   {0} Kcal/mol", result);
		}


		else if (stringComparison(userInput, "electrostatic energy") && loaded) {
			molecule0.electrostatic(result);
			KRABS_INFO("electrostatic energy:   {0} Kcal/mol", result);
		}


		else if (stringComparison(userInput, "total energy") && loaded) {
			float totalEnergy = 0;

			molecule0.atomicStretch(result);
			KRABS_INFO("Bond energy:   {0} Kcal/mol", result);
			totalEnergy += result;
			result = 0;

			molecule0.atomicBend(result);
			KRABS_INFO("angle bend energy:   {0} Kcal/mol", result);
			totalEnergy += result;
			result = 0;

			molecule0.vanDerVaals(result);
			KRABS_INFO("Bond energy:   {0} Kcal/mol", result);
			totalEnergy += result;
			result = 0;

			molecule0.electrostatic(result);
			totalEnergy += result;
			KRABS_INFO("electrostatic energy:   {0} Kcal/mol", result);
			result = 0;
			KRABS_INFO("total energy:   {0} Kcal/mol", totalEnergy);
		}

		else if (stringComparison(userInput, "total energy") || stringComparison(userInput, "electrostatic energy") ||
				stringComparison(userInput, "angle energy") || stringComparison(userInput, "bond energy") ||
				stringComparison(userInput, "van der waals energy") && !loaded)
			KRABS_WARN("Warning cannot compute this calculation if the model is not loaded");

		else
		{
			KRABS_ERROR("invalid input");
		}
	}
	KRABS_INFO("Good bye...");
}



bool Application::stringComparison(const std::string &userInput, std::string comp)
{

	for (unsigned int i = 0; i < comp.length(); i++) {
		if (userInput[i] == comp[i]);
		else if (userInput[i] != comp[i]) {
		
			return false;
		}
	}
	return true;
}

void Application::onHelp(const std::string& userInput)
{
	if (userInput == "help")
		KRABS_INFO("Krabs its a molecular dynamic program "
			"used for computing different type of dynamics.\n"
			"	use 'load <filepath>' for load a .mol file\n\n"
			"   A list of all possible calculation:\n"
			"	'hydrogenoid -p <parameter>' used for calculate hydrogenoid waveFunction\n\n"
			"   for the next calculation is necessary to have a model loaded: \n"
			"	'bond energy' \n"
			"	'angle energy' \n"
			"	'van der waals energy' \n"
			"	'electrostatic energy' \n"
			"	'total energy' used for calculate the sum of all energy term of a molecule \n\n"
			"	example: > load krabsDirPath.../example_molecule/methane.mol \n"
			"	         > total enrgy \n"


			"   pres - help <keyword> for more information about the calculation.\n");
			

	else if (userInput == "help hydrogenoid" || userInput == "hydrogenoid -help")
	{
		KRABS_INFO("The hydrogenoid atom is the only system that can be resolved perfectly.\n"
			"\t for use this calculation type: \n"
			"> Hydrogenoid -p <n quatnic number> <l quatnic number> <ml quatnic number>");
	}

	else
	{
		KRABS_INFO("no information about: '{0}', pres - help <keyword> for more information.\n", userInput);
	}
}


void Application::hydrogenoid(const std::string &userInput) {
	// hydrogenoid -p ...
	if (userInput == "hydrogenoid") {
		KRABS_INFO("no parameter inserted assuming n = 1; l = 0; ml = 0");
		parameters par{ 0, 0, 0 };
		MolecularCalculation::hydrogenLikeCalculation(par);
	}
	else { 
		parameters par =  tokenize(userInput, "hydrogenoid");
		if (par.n == NULL) {

		}

		else
			MolecularCalculation::hydrogenLikeCalculation(par);
	}
}


void Application::loadModel(const std::string& userInput)
{
	int index = 0;
	int counter = 0;
	std::vector <std::string> tokens;
	std::string tokenized;
	std::stringstream check1(userInput);

	while (std::getline(check1, tokenized, ' '))
	{
		tokens.push_back(tokenized);
		counter++;
	}
	MolLoader moleculepar(tokens[1]);
	if (moleculepar.isLoaded()) {
		molecule0.setModel(moleculepar.getData());
		loaded = true;
	}
	else 
		loaded = false;
	
}


parameters Application::tokenize(const std::string userInput, const std::string& keyword)
{
	parameters par{ 0, 0, 0 };
	std::vector<int> parVec;
	std:: vector <std::string> tokens;

	// stringstream class check1 
	std::stringstream check1(userInput);

	std::string intermediate;

	// Tokenizing w.r.t. space ' ' 
	int index = 0;
	int counter = 0;
	while (std::getline(check1, intermediate, ' '))
	{
		tokens.push_back(intermediate);
		counter ++;
		if (intermediate == "-p")
			index = counter;

	}

	for (int i = index; i < tokens.size(); i++) {
		std::cout << tokens[i] << std::endl;
		
		if (tokens[i] != "-p") {
			if (!stoi(tokens[i])) {
				KRABS_ERROR("Error invalid parameter(NON numerical)");
				par.n = NULL;
				return par;
			}
			else {
				parVec.push_back(std::stoi(tokens[i]));
			}
		}
	}

	//i really don't like this, i hop is just a temporary solution.
	if (parVec.size() == 3) {
		par.n = parVec[0];
		par.l = parVec[1];
		par.ml = parVec[2];
	}
	else if(parVec.size() == 2) {
		par.n = parVec[0];
		par.l = parVec[1];
	
	}

	else if (parVec.size() == 1) {
		par.n = parVec[0];

	}

	return par;
}
