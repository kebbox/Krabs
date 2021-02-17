#include "myFuncion.h"
#include "SpectralCalculation.h"
#include "Logging.h"

//a class of all the calculation method 

void SpectralCalculation::linearPotential(int iteration) {

	//hardcode number of proton per atom:
	float chargeC = 6 * protonCharge;
	float chargeO = 8 * protonCharge;
	
	float dX_step = 1E-12f; //1 picometer per tick
	//for each atom
	float k = 481.1f;
	//for each ligand i pick x1 and x2 as the array position of the atom
	std::cout << mMolecule.nOfBond << std::endl;

	for (int i = 0; i < mMolecule.nOfBond; i++) {
	
		int x1 = mMolecule.bondsCouple[i][0] - 1;
		int x2 = mMolecule.bondsCouple[i][1] - 1;

		float potential = 9999;

		float dist = mMolecule.atoms[x2].coord[0] - mMolecule.atoms[x1].coord[0];
		
		std::cout << "elaborating the " << i << " bond ..." << std::endl;
		for (int step = 0; step <= iteration; step++) {
			// POTENTIAL SQUARE DIST
			float iPotentialA =  (chargeC * chargeO) / ((dist) * epsilon0) ;
			float ipotentialB = -(k * (dist * dist) * 0.5f);
			float iPotential = abs(ipotentialB + iPotentialA);
		
			//this is wrong 
			if (iPotential <= potential) {
				potential = iPotential;
				dist += dX_step;
			}

			else {
				dist -= dX_step;
			}
		}
		//Logging::print<float>("the bond lenght of the atom cuple is: ", &dist);
	}
}




void SpectralCalculation::hydrogenLikeCalculation() {
	//autoconsistedfield
	//SPIN NOT YET CONSIDERED
	//add lagrangian function
	//psy = radial *angular

	float start = 1E-13f;
	float end = 6E-11f;

	float dimention = 100;
	float cineticConst = (1 / (8 * pow(pi, 2) * electronMass) * pow(plankConst, 2));
	//https://en.wikipedia.org/wiki/Hydrogen-like_atom

	//initialize the needed space vector
	//std::vector<vec3d> cinEnergy;
	std::vector<float> ray;
	MyMath::createVector(ray, start, end, dimention);
	std::vector<float> theta;
	MyMath::createVector(theta, 0, 180, dimention);
	std::vector<float> phi;
	MyMath::createVector(phi, 0, 360, dimention);

	std::vector<float> radialCineticResult;
	std::vector<float> radialPotentialResult;
	std::vector<float> angularEnergy;
	parameters par;
	par.l = 0;
	par.n = 1;
	par.ml = 0;

	
	// radial part
	MyMath::secondDerivativeCalculator(ray, radialCineticResult,par, myFuncion::Laguerre);



	MyMath::vectorByScalar(radialCineticResult, cineticConst);
	
	KRABS_TRACE("SIZE OF cin :{0}", radialCineticResult.size());
	//potential
	MyMath::functionIterator(ray, radialPotentialResult, par, myFuncion::hydrogenLikePotential);
	KRABS_TRACE("SIZE OF POT :{0}", radialPotentialResult.size());

	MyMath::sumBeteenVector(radialCineticResult, radialPotentialResult);

	//angular part
	//create a 2dvec of angles
	std::vector<vec2d> angles;
	vec2d single;

	for (int i = 0; i < theta.size(); i++) {
		single.var1 = theta[i];
		single.var2 = phi[i];
		angles.push_back(single);
	}

	MyMath::functionIterator(angles,angularEnergy, par, myFuncion::sphericalArmonical );

	std::vector<float> finalEnergy;

	float product = 0;
	for (int i = 0; i < radialCineticResult.size(); i++) {
		for (int j = 0; j< angularEnergy.size(); j++) {
			
			product = radialCineticResult[i] * angularEnergy[j];
			finalEnergy.push_back(product);
		}
	}
	KRABS_TRACE("ENERGY :{0}", finalEnergy[30000]);
}




void SpectralCalculation::hartreeFockMonoAtomic()
{
	//mono atomic multielectronic hartreeFock 
	//function thath return the number of electron of an atom
	//for each electron
	std::vector <float> cineticEnergy;
	std::vector <float> potentialEnergy;
	std::vector <float> result;
	int nOfElectron = 2;
	float increment = 1E-14f;
	
	// radius of the calculation
	float start = 1E-15f;
	float end = 1E-12f;

	for(int electron = 0; electron < nOfElectron; electron++) {
		//calculation of cinetic and potential electron energy
		
	}
}

SpectralCalculation::SpectralCalculation(molecule uMolecule) {
	
		mMolecule = uMolecule;
		//std::cout << mMolecule.nOfBond << std::endl;
		//std::cout << uMolecule.nOfBond << std::endl;
		//std::cout << "correctly loaded the model..." << std::endl;

}