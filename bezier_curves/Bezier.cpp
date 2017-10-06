#include "Bezier.h"
using namespace bezier_curves;
#include <math.h>

Bezier::Bezier(Point b, int n, System::Collections::Generic::List<GPoint^>^ p)
{
	this->b = b;
	this->p = p;
	this->n = n;
}

int bezier_curves::Bezier::factorial(int n) {
	int r = 1;
	for (int i = n; i > 0; i--) {
		r *= i;
	}
	return r;
}

float bezier_curves::Bezier::bernstein(int i, int t) {
	float r = factorial(n) / (factorial(i) * factorial(n - i));
	r *= pow(t, i);
	r *= pow(1 - t, n - i);
	return r;
}

float *bezier_curves::Bezier::deCasteljau(float **points, int degree, float t) {
	float *pointsQ = new float[(degree + 1) * 3]; // same as pointsQ[numPoints + 1][3]
	for (int j = 0; j <= degree; j++) {
		pointsQ[j*3 + 0] = points[j][0];
		pointsQ[j*3 + 1] = points[j][1];
		pointsQ[j*3 + 2] = points[j][2];
	}
	for (int k = 1; k <= degree; k++) {
		for (int j = 0; j <= degree - k; j++) {
			pointsQ[j*3 + 0] = (1 - t) * pointsQ[j*3 + 0] + t * pointsQ[(j + 1)*3 + 0];
			pointsQ[j*3 + 1] = (1 - t) * pointsQ[j*3 + 1] + t * pointsQ[(j + 1)*3 + 1];
			pointsQ[j*3 + 2] = (1 - t) * pointsQ[j*3 + 2] + t * pointsQ[(j + 1)*3 + 2];
		}
	}
	float *result = new float[3];
	result[0] = pointsQ[0];
	result[1] = pointsQ[1];
	result[2] = pointsQ[2];
	delete[] pointsQ;
	return result;
}

float C(int m, int k)
{
	int v;
	float r = 1;
	v = (m - k)<k ? m - k : k;
	for (int i = 0; i<v; i++) r *= ((m - i) / (v - i));
	return r;
}

float bezier_curves::Bezier::get_x_arbitrary(int t)
{
	float x = 0;
	for (int i = 0; i < n; i++)
	{
		x += p[i]->getPoint()->X * factorial(n) / (factorial(i) * factorial(n - i)) * pow(t, i) * pow((1 - t), (n - i));
	}
	return x;
}

float bezier_curves::Bezier::get_y_arbitrary(int t)
{
	float y = 0;
	for (int i = 0; i < n; i++)
	{
		y += p[i]->getPoint()->Y * factorial(n) / (factorial(i) * factorial(n - i)) * pow(t, i) * pow((1 - t), (n - i));
	}
	return y;
}

float bezier_curves::Bezier::get_x_third(int t)
{
	return pow((1 - t), 3) * p[0]->getPoint()->X + 3 * t * pow((1 - t), 2) * p[1]->getPoint()->X + 3 * t * t * (1 - t) * p[2]->getPoint()->X + t * t * t * p[3]->getPoint()->X;
}

float bezier_curves::Bezier::get_y_third(int t)
{
	return pow((1 - t), 3) * p[0]->getPoint()->Y + 3 * t * pow((1 - t), 2) * p[1]->getPoint()->Y + 3 * t * t * (1 - t) * p[2]->getPoint()->Y + t * t * t * p[3]->getPoint()->Y;
}

System::Void bezier_curves::Bezier::draw_arbitrary_order(Graphics^ im)
{
	for (float cur_t = 0; cur_t <= 1; cur_t += 0.05)
	{
		im->DrawRectangle(gcnew Pen(Color::Black), get_x_arbitrary(cur_t), get_y_arbitrary(cur_t), 1.0f, 1.0f);
	}
}

System::Void bezier_curves::Bezier::draw_third_order(Graphics^ im)
{
	for (float cur_t = 0; cur_t <= 1; cur_t += 0.05)
	{
		im->DrawRectangle(gcnew Pen(Color::Black), get_x_third(cur_t), get_y_third(cur_t), 1.0f, 1.0f);
	}
}
