#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>

using namespace std;

enum	{
	MAX_X = 72,
	MAX_Y = 42,
	MIN_X = 0,
	MIN_Y = 0,
	MAX_ITERATIONS = 1000000,
	MIN_DRONES = 2
};

class FieldSheet;
class Forest;

class Point	{

	public:
		/*Constructor*/
		Point(); //an empty point
		Point(float x, float y);

		/*BIG THREE*/
		~Point();
		Point(const Point& other);
		Point& operator=(const Point& other);


		/*Methods*/
		float getX();
		float getY();
		void setX(float newX);
		void setY(float newY);
		bool operator==(FieldSheet& other);
		Point& operator+(const Point& other);
		Point& operator+=(const Point& other);
		Point& operator-(const Point& other);
		Point& operator*(const float scalar);
		float distance(Point& p1, Point& p2);

	private:
		float x;
		float y;

};

#endif
