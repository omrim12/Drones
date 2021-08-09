#include "Drone.h"
#include "Point.h"
/*******************************/
Drone::Drone(Point& location, Point& velocity, const int ID):
location(location),
velocity(velocity),
personalBest(location),
currentFS(NULL),
serialID(ID)
{}
/*******************************/
Drone::~Drone()	{}
/*******************************/
Drone::Drone(Drone *other):
location(other->location),
velocity(other->velocity),
personalBest(other->personalBest),
currentFS(other->currentFS),
serialID(other->serialID) {}
/*******************************/
Drone *Drone::operator=(const Drone *other)	{

	location = other->location;
	velocity = other->velocity;
	personalBest = other->personalBest;
	currentFS = other->currentFS;
	serialID = other->serialID;

	return this;
}
/*******************************/
bool Drone::operator==(const Drone *other)	{  // in same fieldsheet

	if( currentFS == other->currentFS )
		return true;
	return false;
}
/*******************************/
bool Drone::operator==(const FieldSheet *other)	{ // inside fieldsheet	{

	if( currentFS == other )
		return true;
	return false;
}
/*******************************/
Point& Drone::getLocation()	{
	return location;
}
/*******************************/
void Drone::setLocation(Point& newLoc)	{

	bool exceed = false; // to check if new location about to exceed forest borders

	if( newLoc.getX() >= MAX_X )	{
		exceed = true;
		location.setX(MAX_X - 1);
	}

	if( newLoc.getX() <= MIN_X )	{
		exceed = true;
		location.setX(MIN_X);
	}

	if( newLoc.getY() >= MAX_Y )	{
		exceed = true;
		location.setY(MAX_Y - 1);
	}


	if( newLoc.getY() <= MIN_Y )	{
		exceed = true;
		location.setY(MIN_Y);
	}

	if( !exceed )
		location = newLoc;
}
/*******************************/
int Drone::getID()	{
	return serialID;
}
/*******************************/
FieldSheet *Drone::getCurrentFS()	{
	return currentFS;
}
/*******************************/
void Drone::setCurrentFS(FieldSheet *newFS)	{

	currentFS = newFS;

}
/*******************************/
Point& Drone::getRecord()	{
	return personalBest;
}
/*******************************/
void Drone::setRecord(Point& record,Point& target)	{

	Point p;

	//update personal best in case of need
	if( p.distance(record,target) < p.distance(personalBest,target))
		personalBest = record;
}
/*******************************/
Point& Drone::getVelocity()	{
	return velocity;
}
/*******************************/
void Drone::setVelocity(Point& newVel)	{

	velocity = newVel;

}
