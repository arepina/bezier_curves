#include "BSpline.h"
#include <math.h>

using namespace bezier_curves;

BSpline::BSpline(int n, System::Collections::Generic::List<GPoint^>^ p)
{
	this->p = p;
	this->n = n;
}

PointF^ bezier_curves::BSpline::get_third(float t, int index)
{
	float x = ((pow((1 - t), 3) * p[index - 4]->getPoint()->X + (3 * t*t*t - 6 * t*t + 4) * p[index - 3]->getPoint()->X + (-3 * t*t*t + 3 * t*t + 3 * t + 1) * p[index - 2]->getPoint()->X + t*t*t*p[index - 1]->getPoint()->X)) / 6;
	float y = ((pow((1 - t), 3) * p[index - 4]->getPoint()->Y + (3 * t*t*t - 6 * t*t + 4) * p[index - 3]->getPoint()->Y + (-3 * t*t*t + 3 * t*t + 3 * t + 1) * p[index - 2]->getPoint()->Y + t*t*t*p[index - 1]->getPoint()->Y)) / 6;
	return gcnew PointF(x, y);
}

PointF bezier_curves::BSpline::de_boor(int k, int degree, int i, float x, float* knots, System::Collections::Generic::List<PointF>^ ctrlPoints) {
	if (k == 0)
		return ctrlPoints[i];
	else
	{
		float alpha = (x - knots[i]) / (knots[i + degree + 1 - k] - knots[i]);
		int x = de_boor(k - 1, degree, i - 1, x, knots, ctrlPoints).X * (1 - alpha) + de_boor(k - 1, degree, i, x, knots, ctrlPoints).X * alpha;
		int y = de_boor(k - 1, degree, i - 1, x, knots, ctrlPoints).Y * (1 - alpha) + de_boor(k - 1, degree, i, x, knots, ctrlPoints).Y * alpha;
		return PointF(x, y);
	}
}

void bezier_curves::BSpline::draw_third_order(Graphics ^ im)
{
	for (int i = 4; i <= p->Count; i += 1)
	{
		for (float cur_t = 0; cur_t <= 1; cur_t += 0.005f)
		{
			PointF^ point = get_third(cur_t, i);
			im->DrawRectangle(gcnew Pen(Color::Black), point->X, point->Y, 1.0f, 1.0f);
		}
	}
}

/*
float CoxDeBoor(float u, int i, int k, const float* Knots) {
	if (k == 1)
	{
		if (Knots[i] <= u && u <= Knots[i + 1]) {
			return 1.0f;
		}
		return 0.0f;
	}
	float Den1 = Knots[i + k - 1] - Knots[i];
	float Den2 = Knots[i + k] - Knots[i + 1];
	float Eq1 = 0, Eq2 = 0;
	if (Den1>0) {
		Eq1 = ((u - Knots[i]) / Den1) * CoxDeBoor(u, i, k - 1, Knots);
	}
	if (Den2>0) {
		Eq2 = (Knots[i + k] - u) / Den2 * CoxDeBoor(u, i + 1, k - 1, Knots);
	}
	return Eq1 + Eq2;
}
*/

void bezier_curves::BSpline::draw_de_boor(Graphics ^ im)
{
	for (int i = 4; i <= p->Count; i += 1)
	{
		for (float cur_t = 0; cur_t <= 1; cur_t += 0.005f)
		{
			/*PointF^ point = de_boor(p, cur_t);
			im->DrawRectangle(gcnew Pen(Color::Black), point->X, point->Y, 1.0f, 1.0f);*/
		}
	}
}
