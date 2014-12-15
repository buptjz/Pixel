#ifndef POSITION_H
#define POSITION_H
#include "point2d.h"
class Position
{
public:
	Position(){};
	Position(Point2D p1, Point2D p2){
		leftTop = p1;
		rightBottom = p2;
	}
	void setLeftTop(Point2D p1){ leftTop = p1; }
	void setRightBottom(Point2D p2){ rightBottom = p2; }
	Point2D getLeftTop() const{ return leftTop; }
	Point2D getRightBottom() const{ return rightBottom; }
private:
	Point2D leftTop;
	Point2D rightBottom;

};

#endif