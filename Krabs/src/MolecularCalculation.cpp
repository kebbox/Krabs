#include "myFuncion.h"
#include "MolecularCalculation.h"
#include "Logging.h"

//a class of all the calculation method 

void MolecularCalculation::atomicStretch(float& result) {

	float initialRayDist = 0;
	parameters par;
	int atomA = 0;
	int atomB = 0;
	float partialResult = 0;

	if (mMolecule.nOfBond == 0)
		result = 0;
	else if (mMolecule.nOfBond == 1)
	{
		par.bondDistance = mMolecule.teoBondPar[0].bondDist;

		par.bondForce = mMolecule.teoBondPar[0].bondForce;
		initialRayDist = MyMath::vecDist(mMolecule.atoms[0].coord, mMolecule.atoms[1].coord);

		myFuncion::stretchFunction(result, initialRayDist, par);
	}

	else
	{	
		for (int i = 0; i < mMolecule.nOfBond; i++) {
			
			par.bondDistance = mMolecule.teoBondPar[i].bondDist;
			par.bondForce = mMolecule.teoBondPar[i].bondForce;
			
			atomA = mMolecule.bondsCouple[i][0];
			atomB = mMolecule.bondsCouple[i][1];
			initialRayDist = MyMath::vecDist(mMolecule.atoms[atomA-1].coord, mMolecule.atoms[atomB-1].coord);
			
			myFuncion::stretchFunction(partialResult, initialRayDist, par);
			result += partialResult;
		}
	}
}

void MolecularCalculation::atomicBend(float& result)
{
	//here i need to use the coord from molecule model to calculate the angle bend value

	if (mMolecule.nOfBond == 0 || mMolecule.nOfBond == 1)
		KRABS_INFO("bend energy:      0 J/mol\n");

	else {
	
		parameters par;

		int atomA = 0;
		int atomB = 0;
		float angle = 0;
		float partialResult = 0;
		
		for (int i = 0; i < mMolecule.teoAngleBendPar.size(); i++) {

			angle = MyMath::calculateAngle(mMolecule.atoms[mMolecule.teoAngleBendPar[i].atom1-1].coord,
											mMolecule.atoms[mMolecule.teoAngleBendPar[i].atom2-1].coord,
											mMolecule.atoms[mMolecule.teoAngleBendPar[i].atom3-1].coord);
		
			partialResult = (mMolecule.teoAngleBendPar[i].constant *
							pow((mMolecule.teoAngleBendPar[i].angle - angle), 2));
		
			result += partialResult;
			
		}
	}
}

void MolecularCalculation::atomicTorsion(float& result)
{
}

void MolecularCalculation::outOfPlane(float& result)
{
}

void MolecularCalculation::vanDerVaals(float& result)
{
	//set this
	
	float calculatedRay = 0;
	for(int i = 0; i< mMolecule.teoNonBondedPar.size(); i++){
		// -1 because numeration start from 1 but index start from 0
		calculatedRay = MyMath::vecDist(mMolecule.atoms[mMolecule.teoNonBondedPar[i].atom1 - 1].coord,
						mMolecule.atoms[mMolecule.teoNonBondedPar[i].atom2 - 1].coord);

		result += mMolecule.teoNonBondedPar[i].constant *
			(pow((calculatedRay/mMolecule.teoNonBondedPar[i].teoRadius), 12) -
				2 * pow((calculatedRay/mMolecule.teoNonBondedPar[i].teoRadius), 6));
		}
}


void MolecularCalculation::electrostatic(float& result)
{

	
	float partialResult = 0;
	float distance = 0;

	for (int i = 0; i < mMolecule.nOfAtom; i++) {
		for (int j = 0; j < mMolecule.nOfAtom; j++) {
			if (i != j) {
				distance = MyMath::vecDist(mMolecule.atoms[i].coord, mMolecule.atoms[j].coord);
				myFuncion::electrostaticEnergy(partialResult, distance);
				partialResult *= (MyMath::avogadroConst * 1E+10f * 0.238846f / 1000.0f);
				result += partialResult;
			}
		}
	}
	//convertion in Kj/mol
	
}


void MolecularCalculation::hydrogenLikeCalculation(parameters par) {


	float start = 1E-13f;
	float end = 6E-11f;

	int  dimention = 100;
	float cineticConst = (1 / (8 * pow(MyMath::pi, 2) * MyMath::electronMass) * pow(MyMath::plankConst, 2));
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

	par.l = 0;
	par.n = 1;
	par.ml = 0;

	
	// radial part
	MyMath::secondDerivativeCalculator(ray, radialCineticResult,par, myFuncion::Laguerre);



	MyMath::vectorByConst(radialCineticResult, cineticConst);
	
	KRABS_TRACE("SIZE OF cin :{0}", radialCineticResult.size());
	//potential
	MyMath::functionIterator(ray, radialPotentialResult, par, myFuncion::hydrogenLikePotential);
	KRABS_TRACE("SIZE OF POT :{0}", radialPotentialResult.size());

	MyMath::sumBeteenVector(radialCineticResult, radialPotentialResult);

	//angular part
	//create a 2dvec of angles
	std::vector<vec2d> angles;
	vec2d single;

	for (unsigned int i = 0; i < theta.size(); i++) {
		single.var1 = theta[i];
		single.var2 = phi[i];
		angles.push_back(single);
	}

	MyMath::functionIterator(angles,angularEnergy, par, myFuncion::sphericalArmonical );

	std::vector<float> finalEnergy;

	float product = 0;
	for (unsigned int i = 0; i < radialCineticResult.size(); i++) {
		for (unsigned int j = 0; j< angularEnergy.size(); j++) {
			
			product = radialCineticResult[i] * angularEnergy[j];
			finalEnergy.push_back(product);
		}
	}
	KRABS_TRACE("ENERGY :{0}", finalEnergy[30000]);
	KRABS_INFO("Calculation Completed");
}

void MolecularCalculation::setModel(molecule uMolecule)
{
	mMolecule = uMolecule;
}


MolecularCalculation::MolecularCalculation(molecule uMolecule) {
		mMolecule = uMolecule;
}

MolecularCalculation::~MolecularCalculation()
{
	
}
