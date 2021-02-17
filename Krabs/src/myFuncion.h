#pragma once

#include "MyMath.h"
#include "Logging.h"
//just a bunch of matematical  function
namespace myFuncion {
	void Laguerre(float& result, const float& r, parameters p);
	void legendrePolynomial(float& result, float x, parameters p);
	using namespace MyMath;
	void gaussianOrbital(float& result,const float &x, const float &y, const float &z, parameters p)
	{
		float alpha = 2.0f;
		float coeffi = 2.0f;
		float coeffj = 1.0f;
		float coeffk = 1.0f;
		std::vector <float> coeff = { coeffi, coeffj, coeffk };

		float firstEquation = pow((2 * alpha / pi), 0.75f) ;

		float secondEquation = (exponentialSum(alpha * 8.0f, coeff))*
								factorial(int(coeffi))*factorial(int(coeffj))*factorial(int(coeffk));  // alpha^(a+b+c)

		float thirdEquation = (factorial(int(2.0f * coeffi)) * factorial(int(2.0f * coeffj)) * factorial(int(2.0f * coeffk)));

		vectorByScalar(coeff, alpha);
		float fourthEquation = pow(x, coeffi) * pow(y, coeffj) * pow(z, coeffk) * exponentialSum(neper, coeff);

		float finalEquation = firstEquation * (pow((secondEquation / thirdEquation), 0.5f)) * fourthEquation;
	}

	void monoatomicElectron(float& result, float r, parameters p)
	{
		float n = 1.0f;
		float spaceEnd = 1E-12f;
		result = (sin(r * pi * n));
	}

	void potentialEnergyElectron(float& result, const float &r, parameters p) {
		result = (pow(protonCharge, 2.0f)) / ( r);	
	}

	void hydrogenLikePotential(float& result, const float& r, parameters p) {
		float l = 1;
		float laguerre = 0;
		Laguerre(laguerre, r, p);
		
		result = ((pow(protonCharge, 2.0f)) / (r* 4*pi *epsilon0)) + (1 / (8 * pow(pi, 2) * electronMass)) * (pow(plankConst, 2) * l * (l + 1)) * (1 / pow(r, 2)) *laguerre;
	}

	void Laguerre(float& result,const float& r, parameters p) {
		//note the r *Laguerre
		result = r*(- r + 1);
	}

	void sphericalArmonical(float& result, const vec2d &angles, parameters p)
	{
		float legendre = 0;
		legendrePolynomial(legendre, angles.var1, p);
		
		result = sqrt(((2 * p.l + 1)*factorial(p.l-p.ml))/((4*pi) *factorial(p.l+p.ml))) *legendre *exp(p.ml *angles.var2);

	}

	void legendrePolynomial(float &result , float x, parameters p)
	{
		switch (p.l)
		{
		case 0 :
			result = 1;
			break;
		case 1 :
			result = pow(x, p.ml);
			break;
		case 2:
			result = pow(0.5f * (3.0f * pow(x, 2.0f) - 1), p.ml);
			break;
		case 3:
			result = pow(0.5f * (5.0f * pow(x, 3.0f) - 3.0f * x), p.ml);
			break;
		case 4:
			result = pow(0.125f * (35.0f * pow(x, 4.0f) - 30.0f * pow(x, 2.0f) + 3.0f), p.ml);
			break;
		default:
			KRABS_ERROR("sorry polynomial number to high");
			break;
		}
		
	}
}

