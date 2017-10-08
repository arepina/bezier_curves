#pragma once
#include "GPoint.h"
using namespace System::Drawing;
using namespace System::Collections::Generic;
namespace bezier_curves {
	ref class Bezier
	{
	private:
		int n;
		PointF b;
		System::Collections::Generic::List<GPoint^>^ p;
	public:
		Bezier(PointF b, int n, System::Collections::Generic::List<GPoint^>^ p);
		int factorial(int n);
		float *deCasteljau(float **points, float t);
		float get_x_arbitrary(float t);
		float get_y_arbitrary(float t);
		float get_x_third(float t, int index);
		float get_y_third(float t, int index);
		void draw_arbitrary_order(Graphics^ im);
		void draw_third_order(Graphics^ im);
	};
}
