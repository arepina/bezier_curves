#pragma once
#include "GPoint.h"
using namespace System::Drawing;
using namespace System::Collections::Generic;
namespace bezier_curves {
	ref class Bezier
	{
	private:
		int n;
		Point b;
		System::Collections::Generic::List<GPoint^>^ p;
	public:
		Bezier(Point b, int n, System::Collections::Generic::List<GPoint^>^ p);
		int factorial(int n);
		float bernstein(int i, int t);
		float *deCasteljau(float **points, int degree, float t);
		float get_x_arbitrary(int t);
		float get_y_arbitrary(int t);
		float get_x_third(int t);
		float get_y_third(int t);
		void draw_arbitrary_order(Graphics^ im);
		void draw_third_order(Graphics^ im);
	};
}
