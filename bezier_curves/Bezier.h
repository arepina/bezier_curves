#pragma once
using namespace System::Drawing;
namespace bezier_curves {
	ref class Bezier
	{
	public:
		Bezier();
		int factorial(int n);
		float bernstein(int i, int n, float t);
		float *deCasteljau(float **points, int degree, float t);
	};
}
