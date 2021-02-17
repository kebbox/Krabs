#include "MyMath.h"
#include "Logging.h"

void MyMath::gradientCalculator(std::vector<float>& differential, float start, float end, float increment, parameters par, void(*func)(float&,const float&, const float&, const float&, parameters))
{
	//error checking:
	if (increment == 0);
		//Logging::errorLog("errror increment cannot be 0", Logging::nullObj());
	
	float xh = 0;
	float yh = 0;
	float zh = 0;

	float x = start;
	float y = start;
	float z = start;

	float diff = 0;
	float equationResult = 0;


	int nOfIteration = (end - start) / increment;
	std::cout << "number of iteration per each variable: " << nOfIteration << std::endl;
	//differential.reserve(nOfIteration * nOfIteration * nOfIteration);

	for (int i = 0; i <= nOfIteration; i++) {
		xh += (i / nOfIteration) + increment;
		
		for (int j = 0; j <= nOfIteration; j++) {
			yh += (j / nOfIteration) + increment;
			y += j / nOfIteration;

			for (int k = 0; k <= nOfIteration; k++) {
				zh += (k / nOfIteration) + increment;
				z += k / nOfIteration;


				func(diff, xh, yh, zh, par);
				func(equationResult, x, y, z, par);
				differential.emplace_back((diff - equationResult) / increment);

			}
		}
	}
}

void MyMath::Laplacian(std::vector<float>& differential, float start, float end , float increment, parameters par, void(*func)(float& ,float, float, float, parameters))
{
	//the laplacian is the sum of all'non mixed second order derivative

	if (increment == 0);
		//Logging::errorLog("errror increment cannot be 0", Logging::nullObj());

	float xhPos = 0, yhPos = 0, zhPos =   0 ;
	float xhNeg = 0, yhNeg = 0, zhNeg = 0;

	float x = start;
	float y = start;
	float z = start;

	float diffPos = 0;
	float diffNeg = 0;
	float equationResult = 0;

	int nOfIteration = (end - start)/increment;
	//std::cout << "number of iteration per each variable: " << nOfIteration << std::endl;
	//differential.reserve(nOfIteration * nOfIteration * nOfIteration);

	for (int i = 0; i <= nOfIteration; i++) {
		x += increment;
		xhPos = x + increment;
		xhNeg = x - increment;

		for (int j = 0; j <= nOfIteration; j++) {
			y += increment;
			yhPos = y + increment;
			yhNeg = y - increment;

			for (int k = 0; k <= nOfIteration; k++) {
				
				z += increment;
				zhPos = z + increment;
				zhNeg = z - increment;

				func(equationResult, xhPos, yhPos, zhPos, par);
				func(diffNeg, xhNeg,  yhNeg, zhNeg, par);
				func(equationResult, x, y, z, par);
			
				differential.push_back((diffPos - (2* equationResult) +diffNeg) / (increment*increment));
			
			}
		}
	}
}

void MyMath::secondDerivativeCalculator(const std::vector<float>& variable, std::vector <float>& outResult, parameters par, void(*func)(float&, const float&, parameters))
{
	float diffPos = 0.0f;
	float diffNeg = 0.0f;
	float equationResult = 0.0f;
	float increment = 0.0f;
	int max = variable.size();
	for (int i = 0; i < variable.size(); i++) {
		
		if (i == 0) {
		
			
			outResult.push_back(0);
			
		}
		else if (i == variable.size()-1) {
		
		
			outResult.push_back(0);
		}

		else {
			increment = variable[i] - variable[i + 1];
			func(equationResult, variable[i], par);
			func(diffNeg, variable[i-1], par);
			func(diffPos, variable[i+1], par);
	
			outResult.push_back((diffPos - (2.0f * equationResult) + diffNeg) / (increment * increment));
		}
	}

}

void MyMath::functionIterator(const std::vector<float>& variable, std::vector<float>& outResult, parameters par, void(*func)(float&, const float&, parameters))
{

	//	Logging::errorLog("errror increment cannot be 0", Logging::nullObj());
	float result = 0;
	for (auto i : variable) {
		func(result, i, par);
		outResult.push_back(result);
	}
	

}

void MyMath::functionIterator(const std::vector <vec2d> space, std::vector<float>& outResult, parameters par, void(*func)(float&, const vec2d&, parameters))
{
	float result = 0;
	float xvar = 0;
	vec2d variable = { 0, 0};
	for (int x = 0; x < space.size(); x++) {
		xvar = space[x].var1;
		for(int y = 0; y< space.size(); y++)
		{ 
			variable.var1 = xvar;
			variable.var2 = space[y].var2;
			func(result, variable, par);
			outResult.push_back(result);
		}
			
	}


}

void MyMath::normalizeFunction(std::vector<float>& space)
{
	float maxVal = absMax(space);

	for (int i = 0; i < space.size(); i++ ) {
		space[i] = abs(space[i]/ maxVal);
	}
}

float MyMath::oneDimentionIntegral(const std::vector<float>& variable, float start, float end, float iteration, parameters par, void(*func)(float&, float, parameters))
{
	//for integration sum of all area of a infinitesimal dx step
	float result = 0;
	float stepResult0 = 0;
	float stepResult1 = 0;
	float position0 = 0;
	float position1 = 0;
	float increment = (end - start) / iteration;
	for (int i = 0; i < iteration; i++)
	{
		position0 += increment;
		position1 = position0 +increment;
		//how do i calculate the area??
		func(stepResult0, position0, par);
		func(stepResult1, position1, par);
		result += (position1 - position0) * ((stepResult0 + stepResult1) * 0.5);
	}
	KRABS_ERROR("OK NOW");
	return result;
}



void MyMath::sumBeteenVector(std::vector<float>& result, const std::vector <float>& sumBy)
{
	if (result.size() == sumBy.size()) {
		for (int i = 0; i < result.size(); i++) {
			result[i] += sumBy[i];
		}
	}
	else {
		KRABS_ERROR("the size of vector do not corrispond.");
	}
}

void MyMath::diffBeteenVector(std::vector<float>& result, const std::vector <float>& sumBy)
{
	for (int i = 0; i < result.size(); i++) {
		result[i] -= sumBy[i];
	}
}

void MyMath::createVector(std::vector<float>& vec, float start, float end, int dimention)
{
	float increment = (start - end)/static_cast<float>(dimention);
	float value = 0;
	for (int i = 0; i < dimention; i++) {
		value += increment;
		vec.push_back(value);
		
	}
}

void MyMath::createVector3d(std::vector<vec3d>& vec, float start, float end, int dimention)
{
	float increment = (end - start) / static_cast<float>(dimention);
	
	vec3d val = { 0, 0, 0 };
	float value = 0;
	for (int x = 0; x < dimention; x++) {
		val.x += increment;
		for (int y = 0; y < dimention; y++) {
			val.y += increment;
			for (int z = 0; z < dimention; z++) {
				val.z += increment;
				vec.emplace_back(val);
			}
		}
	}
}



float MyMath::vectorSum(std::vector<float>& vec, int dimention)
{
	float sum = 0;

	for (int i = 0; i < dimention; i++) {
		sum += vec[i];
	}
	return sum;
}

float MyMath::minValue(const std::vector<float>& vec)
{

	float minVal = vec[0];
	
	for (auto i : vec) {
		if (i <= minVal) {
			minVal = i;
		}
	}
	return minVal;
}

float MyMath::maxValue(const std::vector<float>& vec)
{
	float  maxVal = vec[0];
	for (auto i : vec) {

		if (i >= maxVal) {
			maxVal = i;
		}
	}
	return maxVal;
}

float MyMath::absMax(const std::vector<float>& vec)
{
	float  maxVal = vec[0];
	
	float absValue = 0;
	for (auto i : vec) {
		absValue = abs(i);
	
		if (absValue >= maxVal) {
			maxVal = absValue;
		}
	}

	return maxVal;
}

void MyMath::fromSpatialToSpherical(std::vector<vec3d>& space)
{
	//returned by reference (r, theta, phi)
	for (int i = 0; i < space.size(); i++)
	{
		space[i].x = (sqrt(pow(space[i].x, 2) + pow(space[i].y, 2) + pow(space[i].z, 2))); //r
		space[i].y = 1 / (sin(space[i].z / space[i].x)); // theta
		space[i].z = 1 / (tan(space[i].y / space[i].x)); // phi
	}
}

void MyMath::vectorByScalar(std::vector<float> &vec, float scalar)
{
	// do auto iterate by reference or by copy ? of vector
	for (int i = 0; i < vec.size(); i++) {
		vec[i] *= scalar ;
	}
	
}



void MyMath::vectorByVector(std::vector<float>& result, const std::vector <float>& mul)
{
	//only one dimention
	if (result.size() == mul.size()) {
		for (int i = 0; i < result.size(); i++) {
			result[i] *= mul[i];
		
		}
	}

		//Logging::errorLog("dimention do not corrispond.", Logging::nullObj());
}

void MyMath::OneDimMatrixProduct(std::vector<float>& result, const std::vector<float>& mat2)
{
	//for now this is 1dimention
	//could use a struct toh 
	if (result.size() != mat2.size()) 
		KRABS_ERROR("incompatible matrix size for matrix multiplication");

	else {
		for (int i = 0; i < result.size(); i++) {
			result[i] *= mat2[i];
		}
	}
}


float MyMath::exponentialSum(float base, std::vector<float>& exp)
{
	float result = 1;

	for (auto i : exp) {
		result *= pow(base, i);
	}
	return result;
}

float MyMath::factorial(int base)
{
	float result = 0;
	if (base == 0)
		return 1;
	else {
		for (int i = 0; i <= base; i++) {
			result += (base * (base - i));
		}

		return result;
	}
}