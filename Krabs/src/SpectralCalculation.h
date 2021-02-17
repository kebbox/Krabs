#pragma once
#include "DataStruct.h"
#include "Krpch.h"



class SpectralCalculation {
private:
	molecule mMolecule;
	const float lightspeed = 299792458.0f;
	const float plankConst = 6.62607E-34f;

	const float pi = 3.1415926535f;
	const float epsilon0 = 8.85419E-12f;
	const float protonCharge = 1.602176634E-19f;
	const float electronMass = 9.1093837015E-31f;
public:


	void linearPotential(int iteration = 10000);	
	void hydrogenLikeCalculation();
	void hartreeFockMonoAtomic();

	SpectralCalculation(molecule uMolecule);
	SpectralCalculation() = default;
};

