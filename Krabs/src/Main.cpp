#include "MolLoader.h"
#include "MolecularCalculation.h"
#include "timer.h"
#include "Application.h"
#include "Logging.h"
#include "MyMath.h"
#include "Optimization.h"


//https://github.com/KhronosGroup/OpenCL-CLHPP

int main()
{
	Logging::OnInit(); // initialize KRABS logging 
	KRABS_WARN("At the moment torsion term are not implemented");
	Application* myApp = new Application; 
	myApp->run(); //user interface main loop here
	delete myApp;

	/*
	MolLoader molecule1("C:\\dev\\Krabs\\example_molecule\\methane.mol");

	Optimization model(molecule1.getData());
	{
		Timer time;
		model.stepestDescent();
	}


	//MolecularCalculation model(molecule1.getData());
	//{	
	//	float result = 0;
		//model.atomicStretch(result);
		//model.atomicBend(result);
		//model.electrostatic(result);
		//model.vanDerVaals(result);
	//}
	*/
	return 0;
}



