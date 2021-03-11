#pragma once
#include "Krpch.h"
#include "DataStruct.h"

//matematical utility;

namespace MyMath {
	const float lightspeed = 299792458.0f;
	const float plankConst = 6.62607E-34f;

	const float neper = 2.718281828f;
	const float pi = 3.1415926535f;
	const float epsilon0 = 8.85419E-12f;
	const float protonCharge = 1.602176634E-19f;
	const float electronMass = 9.1093837015E-31f;
	const float bohrRay = 5.291777721092E-11f;
	const float avogadroConst = 6.022E23f;

	void combinationUtil(std::vector<int> arr, std::vector <int>& result,  int n, int r, int index, std::vector<int> data, int i);
	void getCombination(std::vector<int> arr, std::vector <int>& result, int n, int r);
	void gradientCalculator(std::vector <float>& differential, float start, float end, float increment, parameters par, void(*func)(float& , const float&, const float&, const float&, parameters));
	void Laplacian(std::vector <float>& variable, float start, float end, float increment, parameters par, void(*func)(float&, float, float, float, parameters)); // func(x, y, z)
	void secondDerivativeCalculator(const std::vector <float>& variable, std::vector <float>& outResult, parameters par,  void(*func)(float& , const float&, parameters)); //func(r)
	void functionIterator(const std::vector <float>& space, std::vector <float>& outResult, parameters par, void(*func)(float& , const float&, parameters));
	void functionIterator(const std::vector <vec2d> space, std::vector <float>& outResult, parameters par, void(*func)(float&, const vec2d&, parameters));
	void normalizeFunction(std::vector<float>& space);
	float oneDimentionIntegral(const std::vector<float>& variable, float start, float end, float iteration, parameters par, void(*func)(float&, float, parameters));


	void sumBeteenVector(std::vector <float>& result, const std::vector <float>&  sumBy);
	void diffBeteenVector(std::vector <float>& result, const std::vector <float>& sumBy);
	void createVector(std::vector<float>& vec, float start, float end, int dimention);
	void createVector3d(std::vector<vec3d>& vec, float start, float end, int dimention);

	void vectorByConst(std::vector<float>& vec, float scalar);
	void vectorByVector(std::vector <float>& result, const std::vector <float>& mul);
	void OneDimMatrixProduct(std::vector <float>& result, const std::vector <float>& mat2);


	float vecDist(const std::vector<float>& pt1, const std::vector<float>& pt2);
	float vectorSum(std::vector <float>& vec, int dimention);
	float minValue(const std::vector<float>& vec);
	float maxValue(const std::vector <float>& vec);
	float absMax(const std::vector <float>& vec);
	float calculateAngle(const std::vector<float>& vertex1, const std::vector<float>& vertex2, const std::vector<float>& vertexAngle);
	float vectorNorm(const std::vector<float>& vec);
	float scalarProduct(const std::vector<float>& vec1, const std::vector<float>& vec2);
	
	void fromSpatialToSpherical(std::vector<vec3d> &space);

	float exponentialSum(float base, std::vector<float>& exp);
	float factorial(int base);

}

