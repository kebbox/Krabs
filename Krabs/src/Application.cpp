#include "Application.h"
#include "Krpch.h"

void Application::run()
{
	while (true);
}

/*
void core::Oninit()
{
	std::string version = "1.0v";
	
	std::cout << "loading krabs version: "<< version << std::endl;
	std::cout << "----------------------WELLCOME TO KRABS-----------------\n\n" << std::endl;
	
	print("type '-help' for more information of how to use the program", nullObj());

	bool run = true;
	std::string userInput;
	while(getline(std::cin, userInput)) {
		// fix this , try to use char instead of string o something

		if (core::stringComparison(userInput, "-help"))
			core::OnHelp(userInput);
	}
	
}

enum {
	
};

bool core::stringComparison(std::string &userInput, std::string comp)
{

	int length = userInput.length();
	if (userInput.length() < comp.length()) {
		errorLog("input error,  type '-help' for view the commands", nullObj());
		debug("length of user input: ", &length);
	}
	
	for (int i = 0; i < comp.length(); i++) {
		if (userInput[i] == comp[i]);
		else if (userInput[i] != comp[i]) {
			return false;
		}
			
	}
	return true;
}

void core::OnHelp(std::string& userInput)
{
	if (stringComparison(userInput, "-help"))
	{
		print("Help informaton about krebs , pres -help <keyword> for more information.\n"
			"\t", nullObj());
	}
	if (stringComparison(userInput, "-help HartreeFock"))
	{
		print("The Hartree-Fock aproximation allow a good ab-initio calculation.\n"
			  "\talso use the autoconsistent field method wich its basiclly an auto adjusting calculation", nullObj());
	}
}

void Application::run()
{
}
*/