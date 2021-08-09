#ifndef FOREST_H_
#define FOREST_H_

#include "Drone.h"

class Forest	{

public:
	/*constructors*/
	Forest(Drone **drones,int numDrones, Point *target, int iterations);

	/*BIG THREE*/
	~Forest();
	Forest(Forest *other);
	Forest *operator=(Forest *other);

	/*Methods*/
	string *start(); // Simulation core. returns simulation results.
	int operator()(int row, int column);
	Drone *operator()(int ID);
	int getTime();
	Point&  getGlobalBest() const ;
	Drone **getDrones();
	int getNumDrones();
	string toString(); //returns visualization of simulation at current time



private:
	void setGlobalBest();
	void moveDrone(int ID); //physical equation mentioned within instructions
	void randomize(); //randomizes r1 and r2
	double distanceFromTarget(Point& p);
	FieldSheet ***field;
	Drone **drones;
	int numDrones;
	Point& globalBest;
	FieldSheet *targetFS;
	Point *targetP;
	int simulationTime;
	double r1;
	double r2;




};

#endif
