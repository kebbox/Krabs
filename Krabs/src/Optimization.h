#pragma once

#include "Krpch.h"
#include "MolecularCalculation.h"


class Optimization : public MolecularCalculation{
private:
	molecule mMolecule;
public:
	void stepestDescent();

	Optimization(molecule&  uMolecule);
};


