#include "BSpline.h"
#include <math.h>

using namespace bezier_curves;

BSpline::BSpline(PointF b, int n, System::Collections::Generic::List<GPoint^>^ p)
{
	this->b = b;
	this->p = p;
	this->n = n;
}

float bezier_curves::BSpline::get_x_third(float t, int index)
{
	return 1 / 6 * (pow((1 - t), 3) * p[index - 4]->getPoint()->X + (3 * t*t*t - 6 * t*t + 4) * p[index - 3]->getPoint()->X + (-3 * t*t*t + 3 * t*t + 3 * t + 1) * p[index - 2]->getPoint()->X + t*t*t*p[index - 1]->getPoint()->X);
}

float bezier_curves::BSpline::get_y_third(float t, int index)
{
	return 1 / 6 * (pow((1 - t), 3) * p[index - 4]->getPoint()->Y + (3 * t*t*t - 6 * t*t + 4) * p[index - 3]->getPoint()->Y + (-3 * t*t*t + 3 * t*t + 3 * t + 1) * p[index - 2]->getPoint()->Y + t*t*t*p[index - 1]->getPoint()->Y);
}

void bezier_curves::BSpline::draw_third_order(Graphics ^ im)
{
	for (int i = 4; i <= p->Count; i += 3)
	{
		b = PointF(p[i - 1]->getPoint()->X, p[i - 1]->getPoint()->Y);
		for (float cur_t = 0; cur_t < 1; cur_t += 0.005f)
		{
			float x = get_x_third(cur_t, i);
			float y = get_y_third(cur_t, i);
			im->DrawRectangle(gcnew Pen(Color::Black), x, y, 1.0f, 1.0f);
		}
	}
}
