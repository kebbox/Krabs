#include "Optimization.h"
#include <random>


void Optimization::stepestDescent()
{
	//first calculation with initial coord
	float vibEnergy = 0;
	float bendEnergy = 0;
	float waalsEnergy = 0;
	float electrostaticEnergy = 0;
	int iteration = 100;
	//arbitrary inital step for gradient descent
	float gamma = 0.01;

	std::cout << "gamma:  " << gamma;
	atomicStretch(vibEnergy);
	atomicBend(bendEnergy);
	vanDerVaals(waalsEnergy);
	electrostatic(electrostaticEnergy);
	
	for (int i = 0; i < iteration; i++) {
		for (int j = 0; j < mMolecule.atoms.size(); j++) {
			
		}
	}
}

Optimization::Optimization(molecule& uMolecule)
{
	mMolecule = uMolecule;
}
