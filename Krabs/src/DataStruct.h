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


struct molecule
{
	int nOfAtom;
	std::string atomName;
	int nOfBond;
	std::vector <atom> atoms;
	std::vector <std::array<int, 3>> bondsCouple;

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
};
