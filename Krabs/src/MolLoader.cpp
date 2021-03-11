#include "MolLoader.h"
#include "DataStruct.h"
#include "Logging.h"
#include "Data.h"
#include "MyMath.h"

//LOOK AT AMBER FILE FOR THE PARAMETER 

void MolLoader::getAtomeBond() {
	int count = 0;
	std::string line;

	while (std::getline(file, line)) {
		count++;
		if (count == 4) break;
	}

	//getting number of atoms and bond
	std::string SnOfAtom;
	std::string SnOfBond;
	int delimiterCounter = 0;
	int typeCounter = 0;

	for (unsigned int i = 0; i < line.size(); i++) {
		if (line[i] == ' ')
			delimiterCounter++;

		if (delimiterCounter == 5) break;

		if (delimiterCounter <= 3)
			SnOfAtom += line[i];

		if (delimiterCounter > 3)
			SnOfBond += line[i];
	}

	nOfAtom = std::stoi(SnOfAtom);
	nOfBond = std::stoi(SnOfBond);

	uMolecule.nOfAtom = nOfAtom;
	uMolecule.nOfBond = nOfBond;

}


void MolLoader::getSpace() {
	int count = 0;
	std::string line;

	std::vector <std::string> coordLines;
	while (std::getline(file, line)) {
		count++;

		if (count <= nOfAtom)
			coordLines.push_back(line);

		if (count == nOfAtom)
			break;
	}

	for (int row = 0; row < nOfAtom; row++)
	{
		//iterate over each line and for each line over each word and
		//add them to a string if not blank
		// each string in the vector below rappresent the coordinate for each atom.
		std::string sCoord;
		std::vector <float> coord;
		std::string atomStr;
		int nOfcoord = 0;
		int nameCounter = 0;
		bool empty = true;
		for (unsigned int column = 0; column < coordLines[row].size(); column++) {
			empty = true;
			if (coordLines[row][column] != ' ' && nOfcoord != 3) {
				sCoord += coordLines[row][column];
				empty = false;
			}

			if (sCoord.size() >= 5 && nOfcoord != 3) {

				if (empty) {
					coord.push_back(stof(sCoord));
					sCoord = "";
					nOfcoord++;
				}
			
			}
			//this pice of code give us the name of each atom a little shit is this script
			//anyway prasing a file is always shit
			if (column >29) {
				
				if (coordLines[row][column] == ' ' ) {
					nameCounter++;
				}
				if (coordLines[row][column] != ' ' && nameCounter < 2)
					atomStr += coordLines[row][column];
				else if(nameCounter>2) 			
					break;
				
			}
		}
		tempAtomName.push_back(atomStr);
		uAtom.atomNumber = row + 1;
		
		uAtom.coord = { coord[0], coord[1], coord[2]  };
		uMolecule.atoms.push_back(uAtom);	}
}


void MolLoader::setAtomType()
{

	//indice i parte da 0
	//atom number da 1
	for(int i = 0; i< uMolecule.nOfAtom; i++)
	{ 
		
		//get number of bond per atom
		int bondPerAtom = 0;
		for (int j = 0; j < uMolecule.bondsCouple.size(); j++) {
			if (i + 1 == uMolecule.bondsCouple[j][1] || i + 1 == uMolecule.bondsCouple[j][2])
				bondPerAtom++;
		}

		//this could be a mess a series of if statment for filling the molecule
		// sp3 carbon

		if (tempAtomName[i] == "C" && bondPerAtom == 4) 
			uMolecule.atomName.push_back("CT");

		//aromathics carbon wrong for now
		else if (tempAtomName[i] == "C" && bondPerAtom == 3 && 
			getNumberOfAtomPerType(tempAtomName[i]) == 6 ) 
				uMolecule.atomName.push_back("CA");

		//sp2 with 1 hydrogen
		else if(tempAtomName[i] == "C" && bondPerAtom == 3 && 
			isBondedWith(tempAtomName[i], "H") == true)
			uMolecule.atomName.push_back("CT");
	
		//water oxigen
		else if(tempAtomName[i] == "O" && bondPerAtom == 2 &&
			isBondedWith(tempAtomName[i], "H") == true)
			uMolecule.atomName.push_back("HW");

		else if (tempAtomName[i] == "H" && bondPerAtom == 1 &&
			isBondedWith(tempAtomName[i], "C") == true)
			uMolecule.atomName.push_back("HC");

		else {
			KRABS_ERROR("error not found any atom type that corrispond"
				"\nnote this section is under development , new atom type"
				" may be added in the future"
			);

		}

	}
}


void MolLoader::getBonds() {

	int count = 0;
	std::string line;
	std::vector <std::string> bondLines;

	while (std::getline(file, line)) {
		if (line == "M  END") break;
		bondLines.push_back(line);
		count++;
	}

	//if i will need the type of bond (triple double bond ettc) i can just adjut 
	//the struct in the spectralcalculation.h
	for (int row = 0; row < count; row++) {
		std::string sBond;
		std::vector <int> bond;
		//i to 9 becoase is the number of char that i need to get all the data
		for (int i = 0; i <= 10; i++) {

			if (bondLines[row][i] != ' ') {
				sBond = bondLines[row][i];
				bond.push_back(std::stoi(sBond));
			}
		}
		
		//atom 1 atom 2 bond type
		std::array<int, 3> ligand = { bond[0], bond[1], bond[2] };
		uMolecule.bondsCouple.push_back(ligand);
	}
}


void MolLoader::getStandardBondsForceeDist()
{
	std::string bondType ;
	sBondPar bondPar{};
	//for making a map string i need to iterate over the bonds atom number 
	//and refer to the actual atom name of each cuple( a bit complicated)
	for (unsigned int i = 0; i < uMolecule.bondsCouple.size(); i++) {
		//indice iniziale == 2 minimo!
		std::string atom1;
		std::string atom2;

		int str1 = uMolecule.bondsCouple[i][0] - 1;
		atom1 = uMolecule.atomName[str1];

		int str2 = uMolecule.bondsCouple[i][1] - 1;
		atom2 = uMolecule.atomName[str2];

		bondType = std::to_string(uMolecule.bondsCouple[i][2]);

		//all order combination of the atom name
		std::vector<std::string> vibAtoms1 = { atom1, atom2 };
		std::vector<std::string> vibAtoms2 = { atom2, atom1 };
		
		if(mapBondVibrationParameter.find(vibAtoms1) != mapBondVibrationParameter.end())
		 {
			bondPar.bondDist = mapBondVibrationParameter.at(vibAtoms1)[0];
			bondPar.bondForce = mapBondVibrationParameter.at(vibAtoms1)[1];
			uMolecule.teoBondPar.push_back(bondPar);
		
			
		}

		 else if (mapBondVibrationParameter.find(vibAtoms2) != mapBondVibrationParameter.end())
		{

			bondPar.bondDist = mapBondVibrationParameter.at(vibAtoms2)[0];
			bondPar.bondForce = mapBondVibrationParameter.at(vibAtoms2)[1];
			uMolecule.teoBondPar.push_back(bondPar);
		}
		else {
			KRABS_ERROR("bond parameter not found");
		}
	}	
}


//this function is  hard coded could be an issue with complex molecule
void MolLoader::getBondsAngle()
{
	sanglePar angleParameters;
	steoAnglePar teoAnglePar;
	if (uMolecule.nOfBond == 0 || uMolecule.nOfBond ==1 )
		KRABS_INFO("no angle bend parameter,biatomic molecule");
		
	else {
		std::vector<int> atomList;
		std::vector<int> multypleBondedAtom;

		for (int i = 0; i < uMolecule.nOfBond; i++) {

			atomList.push_back(uMolecule.bondsCouple[i][0]);
			atomList.push_back(uMolecule.bondsCouple[i][1]);
		}

		//calcolo gli atomi con più di 1 legame
		for (unsigned int i = 0; i < atomList.size(); i++) {
			int doubleCounter = 0;
			for (unsigned int j = 0; j < atomList.size(); j++) {
				if (atomList[i] == atomList[j] && j != i) {
					doubleCounter++;
				}
			}
			if (doubleCounter != 0)
				multypleBondedAtom.push_back(atomList[i]);
		}

		std::vector<int>::iterator it;
		std::sort(multypleBondedAtom.begin(), multypleBondedAtom.end());

		it = std::unique(multypleBondedAtom.begin(), multypleBondedAtom.end());
		multypleBondedAtom.resize(std::distance(multypleBondedAtom.begin(), it));
		int index = 0;

		for (it = multypleBondedAtom.begin(); it != multypleBondedAtom.end(); ++it) {
			multypleBondedAtom[index] = *it;
			index++;
		}

		//setto un array di atomi con più di un legame collegati dallo stesso atomo
	
		float angle = 0;
		for (unsigned int i = 0; i < multypleBondedAtom.size(); i++) {
			std::vector <int> angleCupleArr;
			std::vector <int> atomAngleArr;

			for (int j = 0; j < uMolecule.nOfBond; j++) {
				if (uMolecule.bondsCouple[j][0] == multypleBondedAtom[i]) 
					angleCupleArr.push_back(uMolecule.bondsCouple[j][1]);

				else if (uMolecule.bondsCouple[j][1] == multypleBondedAtom[i]) 
					angleCupleArr.push_back(uMolecule.bondsCouple[j][0]);
				
			}
			
			MyMath::getCombination(angleCupleArr, atomAngleArr, angleCupleArr.size(), 2);
			

			//here we itereate over the vector of cuple of the angle and we know the vertex becose it is in
			//the previous loop 

			//qua è un po un casino itero a step di 2 j per ottenere ogni coppia di atomi( j, j+1) e in oltre considero
			//atomAngleArr[j]-1 per una questione di indice di array(che comincia da 0 non 1)

			for (unsigned int j = 0; j < atomAngleArr.size() - 1; j += 2) {

				teoAnglePar.atom1 = atomAngleArr[j];//first atom
				teoAnglePar.atom2 = multypleBondedAtom[i];//second (vertex atom)
				teoAnglePar.atom3 = atomAngleArr[1 + j];//third atom
				uMolecule.teoAngleBendPar.push_back(teoAnglePar);
			}
		}
	}
}


void MolLoader::getStandardBondAnglePar()
{
	steoAnglePar teoBendPar;

	//int str is the index of the atom name
	//then i set the atom name to string atom1, atom2, atom3
	for (int i = 0; i < uMolecule.teoAngleBendPar.size(); i++) {
		std::string atom1;
		std::string atom2;
		std::string atom3;

		int str1 = uMolecule.teoAngleBendPar[i].atom1 - 1;
		int str2 = uMolecule.teoAngleBendPar[i].atom2 - 1;
		int str3 = uMolecule.teoAngleBendPar[i].atom3 - 1;

		atom1 = uMolecule.atomName[str1];
		atom2 = uMolecule.atomName[str2];
		atom3 = uMolecule.atomName[str3];

		//all order combination of the atom name 
		//a bit ugly for check all possible combination 

		std::vector<std::string> bendAtoms1 = { atom1, atom2, atom3};
		std::vector<std::string> bendAtoms2 = { atom1, atom3, atom2 };
		std::vector<std::string> bendAtoms3 = { atom3, atom2, atom1 };
		std::vector<std::string> bendAtoms4 = { atom3, atom1, atom2 };
		std::vector<std::string> bendAtoms5 = { atom2, atom3, atom1 };
		std::vector<std::string> bendAtoms6 = { atom2, atom1, atom3 };

		//using truebendatom make thing short
		std::vector<std::string> trueBendAtom = { " " };
	
		if (mapAngleBendPar.find(bendAtoms1) != mapAngleBendPar.end())
			trueBendAtom = bendAtoms1;

		if (mapAngleBendPar.find(bendAtoms2) != mapAngleBendPar.end())
			trueBendAtom = bendAtoms2;

		if (mapAngleBendPar.find(bendAtoms3) != mapAngleBendPar.end())
			trueBendAtom = bendAtoms3;

		if (mapAngleBendPar.find(bendAtoms4) != mapAngleBendPar.end())
			trueBendAtom = bendAtoms4;

		if (mapAngleBendPar.find(bendAtoms5) != mapAngleBendPar.end())
			trueBendAtom = bendAtoms5;

		if (mapAngleBendPar.find(bendAtoms6) != mapAngleBendPar.end())
			trueBendAtom = bendAtoms6;
			
		if (trueBendAtom[0] == " ") {
			KRABS_ERROR("bend angle parameter not found");
		}

		uMolecule.teoAngleBendPar[i].angle = mapAngleBendPar.at(bendAtoms1)[1];
		uMolecule.teoAngleBendPar[i].constant = mapAngleBendPar.at(bendAtoms1)[0];

	}
}

void MolLoader::getNonBondedAtom()
{

	//how this work
	//pass each atom and chech the bonded atom
	//then compare the bonded atom with all atom to get the non bonded atom
	//finally get radius and constant from van der waals map and mediate over them 
	svanDeerWaalsPar WaalsPar;
	std::vector<int> excludeList{};
	for (int i = 0; i < uMolecule.nOfAtom; i++) {
		std::vector<int> bondedAtom;
		
		std::vector<int> nonBonded;
		for (int j = 0; j < uMolecule.nOfBond; j++) {
			if (uMolecule.atoms[i].atomNumber == uMolecule.bondsCouple[j][0])
				bondedAtom.push_back(uMolecule.bondsCouple[j][1]);
			if (uMolecule.atoms[i].atomNumber == uMolecule.bondsCouple[j][1])
				bondedAtom.push_back(uMolecule.bondsCouple[j][0]);
		}

		if (bondedAtom.size() == 0) {
			for (int at = 0; at < uMolecule.nOfAtom; at++)
				nonBonded.push_back(uMolecule.atoms[at].atomNumber);
		}
		//for avoid repetition:
		
	
		for (int atomIndex = 0; atomIndex < uMolecule.nOfAtom; atomIndex++){
			bool compare = true;
			for (int bonded = 0; bonded < bondedAtom.size(); bonded++) {
				
				//se l'atomo non è presente nella lista di quelli legati e non è l'atomo in questione
				//allora è un atomo non legato
				if (bondedAtom[bonded] == uMolecule.atoms[atomIndex].atomNumber || 
					uMolecule.atoms[atomIndex].atomNumber == uMolecule.atoms[i].atomNumber) {
					compare = false;
					break;

				}
			}

			//for repetition
			for (int excluded = 0; excluded < excludeList.size(); excluded++) 
				if (excludeList[excluded] == uMolecule.atoms[atomIndex].atomNumber) {
					compare = false;
					break;
				}
			

			if (compare ) 
				nonBonded.push_back(uMolecule.atoms[atomIndex].atomNumber);
		}
		excludeList.push_back(uMolecule.atoms[i].atomNumber);
	
		for (int j = 0; j < nonBonded.size(); j++) {
			
			float waalsConst = sqrt(mapVanDerWaalsPar.at(uMolecule.atomName[i])[1] * mapVanDerWaalsPar.at(uMolecule.atomName[nonBonded[j]-1])[1]);
			float radius = 0.5f *(mapVanDerWaalsPar.at(uMolecule.atomName[i])[0] + mapVanDerWaalsPar.at(uMolecule.atomName[nonBonded[j]-1])[0]);
			
			WaalsPar.atom1 = uMolecule.atoms[i].atomNumber;
			WaalsPar.atom2 = nonBonded[j];
			WaalsPar.constant = waalsConst;
			WaalsPar.teoRadius = radius;
			uMolecule.teoNonBondedPar.push_back(WaalsPar);
		
		}
	}

}

int MolLoader::getNofBondPerAtom(const std::string atom)
{
	return 0;
}


int MolLoader::getNumberOfAtomPerType(const std::string atom)
{
	int result = 0; 
	
	for (int i = 0; i < uMolecule.nOfAtom; i++) {
		if (tempAtomName[i] == atom)
			result++;
	}

	return result;
}


bool MolLoader::isBondedWith(const std::string atom, const std::string ligand)
{
	//iterate over atom name for find the right number
	//find the bonded atom with the string atom input
	std::vector <int> number;
	std::vector<std::string > compare;

	for (int i = 0; i < uMolecule.nOfAtom; i++) {

		if (atom == tempAtomName[i]) {
			for (int j = 0; j < uMolecule.bondsCouple.size(); j++) {
				if (uMolecule.bondsCouple[j][0] == i + 1)
					number.push_back(uMolecule.bondsCouple[j][1]);
				else if(uMolecule.bondsCouple[j][1] == i + 1)
					number.push_back(uMolecule.bondsCouple[j][0]);
			}
		}
	}
	
	for (int i = 0; i < number.size(); i++) {
		if (tempAtomName[number[i]-1] == ligand)
			return true;
	}

	return false;
}


void MolLoader::loadData() {

	getAtomeBond();
	getSpace();
	getBonds();
	setAtomType();
	getStandardBondsForceeDist();
	getBondsAngle();
	getStandardBondAnglePar();
	getNonBondedAtom();

	KRABS_INFO("Model loaded successfully\n");
}

bool MolLoader::isLoaded()
{
	if (loaded)
		return true;
	else
		return false;
}


molecule MolLoader::getData() {

	return uMolecule;
}


MolLoader::MolLoader(std::string mfileName) {
	std::string a = "";
	fileName = mfileName;
	file = std::ifstream(fileName);

	if (file.fail()) {
		KRABS_ERROR("Error: file path not found");
		loaded = false;
	}
	else {
		loaded = true;
		loadData();
	}
}