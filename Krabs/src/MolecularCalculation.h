#pragma once
#include "DataStruct.h"
#include "Krpch.h"



class MolecularCalculation {
private:
	molecule mMolecule;
	const float lightspeed = 299792458.0f;
	const float plankConst = 6.62607E-34f;

	const float pi = 3.1415926535f;
	const float epsilon0 = 8.85419E-12f;
	const float protonCharge = 1.602176634E-19f;
	const float electronMass = 9.1093837015E-31f;
public:

	//NON QUANTISTIC CALCULATION
	void atomicStretch(float & result);
	void atomicBend(float& result);
	void atomicTorsion(float& result);
	void outOfPlane(float& result);
	void vanDerVaals(float& result);
	void electrostatic(float& result);

	static	void hydrogenLikeCalculation(parameters par);

	void setModel(molecule uMolecule);
	MolecularCalculation() = default;
	MolecularCalculation(molecule uMolecule);
	~MolecularCalculation();
};

