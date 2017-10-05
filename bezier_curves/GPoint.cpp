#include "GPoint.h"

using namespace bezier_curves;

GPoint::GPoint(int x, int y, Color c, PointType type)
{
	p = gcnew Point(x, y);
	this->c = c;
	this->type = type;
}

PointType bezier_curves::GPoint::getType()
{
	return type;
}

Point^ bezier_curves::GPoint::getPoint()
{
	return p;
}

void bezier_curves::GPoint::setPoint(int x, int y)
{
	p = gcnew Point(x, y);
}

Color bezier_curves::GPoint::getColor()
{
	return c;
}
