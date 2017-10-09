#pragma once
#include "GPoint.h"
using namespace System::Drawing;
using namespace System::Collections::Generic;
namespace bezier_curves {
	ref class Bezier
	{
	private:
		int n;
		System::Collections::Generic::List<GPoint^>^ p;
	public:
		Bezier(int n, System::Collections::Generic::List<GPoint^>^ p);
		float factorial(float n);
		PointF^ de_casteljau(System::Collections::Generic::List<GPoint^>^ p, float t);
		PointF^ get_third(float t, int index);
		void draw_arbitrary_order(Graphics^ im);
		void draw_third_order(Graphics^ im);
		void draw_de_casteljau(Graphics^ im);
	};
}
