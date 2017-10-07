#include "GPoint.h"

using namespace bezier_curves;

GPoint::GPoint(float x, float y, Color c, PointType type)
{
	p = gcnew PointF(x, y);
	this->c = c;
	this->type = type;
}

PointType bezier_curves::GPoint::getType()
{
	return type;
}

PointF^ bezier_curves::GPoint::getPoint()
{
	return p;
}

void bezier_curves::GPoint::setPoint(float x, float y)
{
	p = gcnew PointF(x, y);
}

Color bezier_curves::GPoint::getColor()
{
	return c;
}
