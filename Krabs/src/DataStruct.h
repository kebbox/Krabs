#pragma once
#include <vector>
#include <string>
#include <array>


struct atom
{
	//x y z coord 
	int atomNumber;
	std::vector <float> coord;

};

struct bond {
	int atomA;
	int atomB;
};

struct sanglePar {
	int vertexAtom;
	std::vector<int> bondAngleCombination;
};

struct steoAnglePar {
	float angle;
	float constant;
	int atom1;
	int atom2;
	int atom3;
};
struct svanDeerWaalsPar {
	int atom1;
	int atom2;
	float constant;
	float teoRadius;
};


struct sBondPar {
	float bondForce;
	float bondDist;
};


struct molecule
{
	int nOfAtom;
	int nOfBond;
	std::vector<std::string> atomName;
	std::vector <atom> atoms;
	
	std::vector <std::array<int, 3>> bondsCouple; //atom1 atom2 typeofbond
	std::vector <sBondPar> teoBondPar; //teoretical bond par

	//std::vector <sanglePar> anglesBendPar; //get vertex atom + array of all atom connected to it that forms angle
	std::vector < steoAnglePar> teoAngleBendPar; //teoretical parameter
	std::vector <svanDeerWaalsPar> teoNonBondedPar;
};

struct IR
{
	float bondDistance;
	float reductMass;
	float dissocationEnergy;
	float bondConstant;
};

struct vec3d {
	float x;
	float y;
	float z;
};

struct vec2d {
	float var1;
	float var2;
};

struct parameters {
	int n;
	int l;
	int ml;
	float bondForce;
	float bondDistance;
};
