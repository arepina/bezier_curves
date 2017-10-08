#pragma once
#include "GPoint.h"
using namespace System::Drawing;
using namespace System::Collections::Generic;
namespace bezier_curves {
	ref class BSpline
	{
	private:
		int n;
		static System::Collections::Generic::List<GPoint^>^ p;
	public:
		BSpline(int n, System::Collections::Generic::List<GPoint^>^ p);
		PointF^ get_third(float t, int index);
		PointF de_boor(int k, int degree, int i, float x, float* knots, System::Collections::Generic::List<PointF>^ ctrlPoints);
		void draw_third_order(Graphics^ im);
		void draw_de_boor(Graphics^ im);
	};
}

