#pragma once
#include "Krpch.h"
#include "DataStruct.h"
//used for loading .mol file
class MolLoader
{
private:
	std::string fileName;
	std::ifstream  file;
	int nOfAtom;
	int nOfBond;
	molecule uMolecule;
	atom uAtom;

public:
	void getAtomeBond();

	void getSpace();

	void getBonds();

	std::string getAtomName();
	//this actually create a molecule structure 
	void loadData();

	molecule getData();

	//return filename
	
	//construct
	MolLoader(std::string mfileName);
};
