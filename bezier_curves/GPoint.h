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
		Point^ p;
		Color c;
		PointType type;
	public:
		GPoint(int x, int y, Color c, PointType type);
		PointType getType();
		Point^ getPoint();
		void setPoint(int x, int y);
		Color getColor();
	};
}
