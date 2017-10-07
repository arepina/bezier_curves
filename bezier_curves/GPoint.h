#pragma once
using namespace System::Drawing;
namespace bezier_curves {

	enum class PointType {
		Usual,
		Moving
	};

	ref class GPoint
	{
	private:
		PointF^ p;
		Color c;
		PointType type;
	public:
		GPoint(float x, float y, Color c, PointType type);
		PointType getType();
		PointF^ getPoint();
		void setPoint(float x, float y);
		Color getColor();
	};
}
