#include "Point.h"
#include "FieldSheet.h"
#include "Forest.h"
/*******************************/
Point::Point():x(0),y(0){}
/*******************************/
Point::Point(float x, float y):x(x),y(y){}
/*******************************/
Point::~Point(){}
/*******************************/
Point::Point(const Point& other):x(other.x),y(other.y)	{}
/*******************************/
Point& Point::operator=(const Point& other)	{
	x = other.x;
	y = other.y;

	return *this;
}
/*******************************/
bool Point::operator==(FieldSheet& other)	{

	if( floor(x) == other.getColumn() && floor(y) == other.getRow())
		return true;

	return false;
}
/*******************************/
Point& Point::operator+(const Point& other)	{ //Points summarizing restricted by dirichlet's conditions

	Point& p = *new Point();

	p.x = x + other.x;
	p.y = y + other.y;

	return p;
}
/*******************************/
Point& Point::operator+=(const Point& other)	{ //Points summarizing restricted by dirichlet's conditions

	*this = *this + other;
	return *this;

}
/*******************************/
Point& Point::operator-(const Point& other)	{

	Point& p = *new Point();
	p.x = x - other.x;
	p.y = y - other.y;

	return p;

}
/*******************************/
Point& Point::operator*(const float scalar)	{

	x *= scalar;
	y *= scalar;

	return *this;
}
/*******************************/
float Point::getX()	{

		return x;
}
/*******************************/
float Point::getY()	{

		return y;
}
/*******************************/
void Point::setX(float newX)	{
	x = newX;
}
/*******************************/
void Point::setY(float newY)	{
	y = newY;
}
/*******************************/
float Point::distance(Point& p1, Point& p2)	{

	return sqrt(pow(p1.x - p2.x,2) + pow(p1.y-p2.y,2));
}
