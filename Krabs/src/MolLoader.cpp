#include "MolLoader.h"
#include "DataStruct.h"
#include "Logging.h"



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

	for (int i = 0; i < line.size(); i++) {
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
		int nOfcoord = 0;
		int nameCounter = 0;
		float bondLenghtconst = 1E-12;
		for (int column = 0; column < coordLines[row].size(); column++) {

			if (coordLines[row][column] != ' ' && nOfcoord != 3)
				sCoord += coordLines[row][column];

			if (sCoord.size() >= 5 && nOfcoord != 3) {

				if (sCoord[0] == '-' && sCoord.size() == 7) {
					coord.push_back(stof(sCoord));
					sCoord = "";
					nOfcoord++;
			
				}

				if (sCoord[0] != '-' && sCoord.size() == 6) {
					coord.push_back(stof(sCoord));
					sCoord = "";
					nOfcoord++;
					
				}
			}
			//this pice of code give us the name of each atom a little shit is this script
			//anyway prasing a file is always shit
			if (column >29) {
				
				if (coordLines[row][column] == ' ' ) {
					//std::cout << "namecounter " << nameCounter;
					nameCounter++;
				}
				if (coordLines[row][column] != ' ' && nameCounter < 2)
					uMolecule.atomName += coordLines[row][column];
				else if(nameCounter>2) {
					uMolecule.atomName += ' ';
					
					break;
				}
			}
		}

		uAtom.atomNumber = row + 1;
		//conversion from cm to nm 
		
	
		uAtom.coord = { coord[0]* bondLenghtconst, coord[1]* bondLenghtconst, coord[2] * bondLenghtconst };
		uMolecule.atoms.push_back(uAtom);
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
		
		std::array<int, 3> ligand = { bond[0], bond[1], bond[2] };
		uMolecule.bondsCouple.push_back(ligand);
	}
}

std::string MolLoader::getAtomName()
{
	return uMolecule.atomName;
}


void MolLoader::loadData() {
	getAtomeBond();
	getSpace();
	getBonds();
	KRABS_INFO("Model loaded successfully");

}

molecule MolLoader::getData() {
	return uMolecule;
}

MolLoader::MolLoader(std::string mfileName) {
	std::string a = "";
	fileName = mfileName;
	file = std::ifstream(fileName);
	if (file.fail()) {
		KRABS_ERROR("File cannot be loaded.");
	}

	loadData();	
}