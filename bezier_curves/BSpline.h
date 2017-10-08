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
		float get_x_third(float t, int index);
		float get_y_third(float t, int index);
		void draw_third_order(Graphics^ im);
	};
}

