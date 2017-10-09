#include "Bezier.h"
using namespace bezier_curves;
#include <math.h>

Bezier::Bezier(int n, System::Collections::Generic::List<GPoint^>^ p)
{
	this->p = p;
	this->n = n;
}

float bezier_curves::Bezier::factorial(float k)
{
	if (k < 0)
		return 0;
	if (k == 0)
		return 1;
	else
		return k * factorial(k - 1);
}

PointF^ bezier_curves::Bezier::de_casteljau(System::Collections::Generic::List<GPoint^>^ p, float t) {
	float *pointsQ = new float[n * 2];
	for (int j = 0; j < n; j++) {
		pointsQ[j * 2 + 0] = p[j]->getPoint()->X;
		pointsQ[j * 2 + 1] = p[j]->getPoint()->Y;
	}
	for (int k = 1; k < n; k++) {
		for (int j = 0; j < n - k; j++) {
			pointsQ[j * 2 + 0] = (1 - t) * pointsQ[j * 2 + 0] + t * pointsQ[(j + 1) * 2 + 0];
			pointsQ[j * 2 + 1] = (1 - t) * pointsQ[j * 2 + 1] + t * pointsQ[(j + 1) * 2 + 1];
		}
	}
	return gcnew PointF(pointsQ[0], pointsQ[1]);
}

PointF^ bezier_curves::Bezier::get_third(float t, int index)
{
	float x = pow((1 - t), 3) * p[index - 4]->getPoint()->X + 3 * t * pow((1 - t), 2) * p[index - 3]->getPoint()->X + 3 * t * t * (1 - t) * p[index - 2]->getPoint()->X + t * t * t * p[index - 1]->getPoint()->X;
	float y = pow((1 - t), 3) * p[index - 4]->getPoint()->Y + 3 * t * pow((1 - t), 2) * p[index - 3]->getPoint()->Y + 3 * t * t * (1 - t) * p[index - 2]->getPoint()->Y + t * t * t * p[index - 1]->getPoint()->Y;
	return gcnew PointF(x, y);
}

System::Void bezier_curves::Bezier::draw_arbitrary_order(Graphics^ im)
{
	for (float t = 0; t <= 1; t += 0.0005f)
	{
		float x = 0;
		float y = 0;
		for (int i = 0; i < n; i++)
		{
			float temporary = factorial(n - 1) / (factorial(i) * factorial(n - 1 - i)) * pow(t, i) * pow((1 - t), (n - 1 - i));
			x += p[i]->getPoint()->X * temporary;
			y += p[i]->getPoint()->Y * temporary;
		}
		im->FillRectangle(gcnew SolidBrush(Color::Black), x, y, 2.0f, 2.0f);
	}
	im->FillRectangle(gcnew SolidBrush(Color::Black), p[n - 1]->getPoint()->X, p[n - 1]->getPoint()->Y, 1.0f, 1.0f);
}

System::Void bezier_curves::Bezier::draw_third_order(Graphics^ im)
{
	for (int i = 4; i <= p->Count; i += 3)
	{
		for (float cur_t = 0; cur_t < 1; cur_t += 0.005f)
		{
			PointF^ point = get_third(cur_t, i);
			im->DrawRectangle(gcnew Pen(Color::Black), point->X, point->Y, 1.0f, 1.0f);
		}
	}
}

System::Void bezier_curves::Bezier::draw_de_casteljau(Graphics ^ im)
{
	for (int i = 4; i <= p->Count; i += 3)
	{
		for (float cur_t = 0; cur_t < 1; cur_t += 0.0005f)
		{
			PointF^ point = de_casteljau(p, cur_t);
			im->DrawRectangle(gcnew Pen(Color::Brown), point->X, point->Y, 1.0f, 1.0f);
		}
	}
}


