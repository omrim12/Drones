#ifndef DRONE_H_
#define DRONE_H_

#include "FieldSheet.h"

class Point;

class Drone	{


public:
	/*Constructors*/
	Drone(Point& location, Point& velocity,const int serialID);

	/*BIG THREE*/
	~Drone();
	Drone(Drone *other);
	Drone *operator=(const Drone *other);

	/*Methods*/
	bool operator==(const Drone *other); // in same fieldsheet
	bool operator==(const FieldSheet *other); // inside fieldsheet
	Point& getLocation();
	void setLocation(Point& newLoc);
	int getID();
	FieldSheet *getCurrentFS();
	void setCurrentFS(FieldSheet *newFS);
	Point& getRecord();
	void setRecord(Point& record, Point& target);
	Point& getVelocity();
	void setVelocity(Point& newVel);

private:
	Point location;
	Point velocity;
	Point personalBest;
	FieldSheet *currentFS;
	int serialID;









};


#endif
