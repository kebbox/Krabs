#pragma once
#include "Krpch.h"
#include "DataStruct.h"
//used for loading .mol file
class MolLoader
{
private:
	std::string fileName;
	std::ifstream  file;
	std::vector<std::string> tempAtomName;
	int nOfAtom;
	int nOfBond;
	molecule uMolecule;
	atom uAtom;
	bool loaded = false;


public:
	void getAtomeBond();

	void getSpace();

	void setAtomType();

	void getBonds();

	void getStandardBondsForceeDist();

	void getBondsAngle();

	void getStandardBondAnglePar();

	void getNonBondedAtom();

	//return nof bond of the atom
	int getNofBondPerAtom(const std::string atom);
	int getNumberOfAtomPerType(const std::string atom);
	bool isBondedWith(const std::string atom, const std::string ligand);
   
	//this actually create a molecule structure 
	void loadData();
	bool isLoaded();

	molecule getData();

	//return filename
	
	//construct
	MolLoader(std::string mfileName);
};
