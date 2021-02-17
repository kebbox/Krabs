#include "MolLoader.h"
#include "SpectralCalculation.h"
#include "timer.h"
#include "Application.h"
#include "Logging.h"


//https://github.com/KhronosGroup/OpenCL-CLHPP

int main()
{


	//Oninit();
	Logging::OnInit();
	

	//Application *myApp = new Application;
	//myApp->run();
	//delete myApp;


	MolLoader molecule1("C:\\Users\\fceng\\Desktop\\CO2.mol");


	SpectralCalculation model(molecule1.getData());
	{
		Timer time;
		model.hydrogenLikeCalculation();
	}
	return 0;
}

















/*
SpectralCalculation test;


atom C1;
C1.atomNumber = 1;
C1.coord = { 0, 0, 0 };

atom O;
O.atomNumber = 2;
O.coord = { 130E-12f, 0, 0 };

atom C2;
C2.atomNumber = 3;
C2.coord = { 260E-12f, 0, 0 };

molecule CO2;
CO2.nOfBond = 2;

std::array<int, 2> l1 = { 1, 2 };
std::array<int, 2> l2 = { 2, 3 };

CO2.bondsCouple.push_back(l1);

CO2.bondsCouple.push_back(l2);


CO2.atoms = { C1, O, C2 };


test.vibrationalPotential(CO2, 100, 1);
*/
/*
SpectralCalculation HCl1;

IR HCl_data;


HCl_data.dissocationEnergy = dissocationEnergy1;
HCl_data.bondDistance = bondDistance;
HCl_data.reductMass = redMass;
HCl_data.bondConstant = bondConstant;
std::cout << HCl_data.dissocationEnergy ;
HCl1.irSpectra(HCl_data);
*/