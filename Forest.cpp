#include "Forest.h"
#include <unistd.h>
/*******************************/

/********************************** Inteface Implementation ******************************************/
Forest::Forest(Drone **drones, int numDrones, Point *targetP, int iterations) :
		field(new FieldSheet**[MAX_Y]), drones(drones), numDrones(numDrones), globalBest(
				*new Point()), targetFS(NULL), targetP(targetP), simulationTime(
				iterations), r1(0), r2(0) {
	int i, j;

	//Allocate memory for field
	for (i = 0; i < MAX_Y; i++) {
		field[i] = new FieldSheet*[MAX_X];
	}

	for (i = 0; i < MAX_Y; i++) {
		for (j = 0; j < MAX_X; j++) {
			field[i][j] = new FieldSheet(i, j);
		}
	}

	//Set each drone's current field sheet by their current location
	for (i = 0; i < numDrones; i++) {
		if( floor(drones[i]->getLocation().getY()) == MAX_Y && floor(drones[i]->getLocation().getX()) != MAX_X )	{
			drones[i]->setCurrentFS(field[(int) floor(drones[i]->getLocation().getY())-1][(int) floor(drones[i]->getLocation().getX())]);
			(*(field[(int) floor(drones[i]->getLocation().getY())-1][(int) floor(drones[i]->getLocation().getX())]))++; //increase number of drones in specific fieldsheet.
		}

		else if( floor(drones[i]->getLocation().getY()) != MAX_Y && floor(drones[i]->getLocation().getX()) == MAX_X ) 	{
			drones[i]->setCurrentFS(field[(int) floor(drones[i]->getLocation().getY())][(int) floor(drones[i]->getLocation().getX())-1]);
			(*(field[(int) floor(drones[i]->getLocation().getY())][(int) floor(drones[i]->getLocation().getX())-1]))++; //increase number of drones in specific fieldsheet.
		}

		else if( floor(drones[i]->getLocation().getY()) == MAX_Y && floor(drones[i]->getLocation().getX()) == MAX_X )	{
			drones[i]->setCurrentFS(field[(int) floor(drones[i]->getLocation().getY())-1][(int) floor(drones[i]->getLocation().getX())-1]);
			(*(field[(int) floor(drones[i]->getLocation().getY())-1][(int) floor(drones[i]->getLocation().getX())-1]))++; //increase number of drones in specific fieldsheet.
		}

		else	{
			drones[i]->setCurrentFS(field[(int) floor(drones[i]->getLocation().getY())][(int) floor(drones[i]->getLocation().getX())]);
			(*(field[(int) floor(drones[i]->getLocation().getY())][(int) floor(drones[i]->getLocation().getX())]))++; //increase number of drones in specific fieldsheet.
		}
	}

	// initialize self's target from targetP location range
	if (floor(targetP->getY()) == MAX_Y && floor(targetP->getX()) != MAX_X)
		targetFS = field[(int) floor(targetP->getY()) - 1][(int) floor(
				targetP->getX())];
	else if (floor(targetP->getY()) != MAX_Y && floor(targetP->getX()) == MAX_X)
		targetFS = field[(int) floor(targetP->getY())][(int) floor(
				targetP->getX()) - 1];
	else if (floor(targetP->getY()) == MAX_Y && floor(targetP->getX()) == MAX_X)
		targetFS = field[(int) floor(targetP->getY()) - 1][(int) floor(
				targetP->getX()) - 1];
	else
		targetFS = field[(int) floor(targetP->getY())][(int) floor(
				targetP->getX())];

	// set current best with closest to target from starting time.
	setGlobalBest();
}
/*******************************/
Forest::~Forest() {

	for (int i = 0; i < MAX_Y; i++) {
		delete[] field[i];
	}

	for (int i = 0; i < numDrones; i++) {
		delete drones[i];
	}

	delete targetP;
}
/*******************************/
Forest::Forest(Forest *other) :
		field(other->field), drones(other->drones), numDrones(other->numDrones), globalBest(
				other->globalBest), targetFS(other->targetFS), targetP(
				other->targetP), simulationTime(other->simulationTime), r1(
				other->r1), r2(other->r2) {
}
/*******************************/
Forest* Forest::operator=(Forest *other) {

	field = other->field;
	drones = other->drones;
	globalBest = other->globalBest;
	targetFS = other->targetFS;
	targetP = other->targetP;
	simulationTime = other->simulationTime;
	r1 = other->r1;
	r2 = other->r2;

	return this;
}
/*******************************/
int Forest::operator()(int row, int column) {
	return field[column][row]->numberOfDrones;
}
/*******************************/
Drone* Forest::operator()(int ID) {
	return drones[ID];
}
/*******************************/
string* Forest::start() {	// SIMULATION CORE. returns simulation results.

	int i = 0;

	while (i < simulationTime) {

		/**** Check if global best has reached the target ****/

		if (globalBest.getY() + 1 == MAX_Y && globalBest.getX() + 1 != MAX_X
				&& globalBest.getX() == targetP->getX()
				&& globalBest.getY() + 1 == targetP->getY()) // target is at forest bottom and a drone was found there
			break;
		if (globalBest.getY() + 1 != MAX_Y && globalBest.getX() + 1 == MAX_X
				&& globalBest.getX() + 1 == targetP->getX()
				&& globalBest.getY() == targetP->getY()) // target is at forest right edge and a drone was found there
			break;
		if (globalBest.getY() + 1 == MAX_Y && globalBest.getX() + 1 == MAX_X
				&& globalBest.getX() + 1 == targetP->getX()
				&& globalBest.getY() + 1 == targetP->getY()) // target is at forest bottom right edge and a drone was found there
			break;

		if (globalBest == *targetFS) // target is at forest inner area and a drone was found there
			break;

		// move drones to new positions and Update each drone's personal best
		for (int j = 0; j < numDrones; j++) {
			randomize(); // randomize r1,r2 variables
			moveDrone(drones[j]->getID());
		}

		//Update global best
		setGlobalBest();
		i++;
	}

	/******* Return results to main simulation method ******/
	string *results = new string[numDrones + 1];
	string numberConvert;
	stringstream parser;
	string droneInfo = "";
	float f_value;
	int i_value;

	//number of iterations preformed
	if (i + 1 > simulationTime) // for outputing correct number of iterations
		parser << i;
	else
		parser << i + 1;

	parser >> numberConvert;
	results[0] = numberConvert;
	parser.clear();

	for (int j = 0; j < numDrones; j++) {

		droneInfo = "";
		if (drones[j]->getLocation().getX() == MAX_X - 1)	{// fixing increasement (decreasing used for exceeding forest range handling)
			i_value = drones[j]->getLocation().getX()*100;
			f_value = i_value;
			f_value /= 100;
			parser << f_value;
		}
		else	{
			i_value = drones[j]->getLocation().getX()*100;
			f_value = i_value;
			f_value /= 100;
			parser << f_value;
		}
		parser >> numberConvert;
		droneInfo += numberConvert;
		droneInfo += " ";
		parser.clear();

		if (drones[j]->getLocation().getY() == MAX_Y - 1)	{// fixing increasement (decreasing used for exceeding forest range handling)
			i_value = (drones[j]->getLocation().getY() + 1)*100;
			f_value = i_value;
			f_value /= 100;
			parser << f_value;
		}
		else	{
			i_value = drones[j]->getLocation().getY()*100;
			f_value = i_value;
			f_value /= 100;
			parser << f_value;
		}
		parser >> numberConvert;
		droneInfo += numberConvert;
		parser.clear();

		results[j + 1] = droneInfo;
	}

	return results;
}
/*******************************/
int Forest::getTime() { //returns number of simulation's iterations
	return simulationTime;
}
/*******************************/
Point& Forest::getGlobalBest() const {
	return globalBest;
}
/*******************************/
void Forest::setGlobalBest() { // updates global best from drones array

	for (int i = 0; i < numDrones; i++) {
		if (distanceFromTarget(drones[i]->getLocation()) < distanceFromTarget(globalBest))
			globalBest = drones[i]->getLocation();
	}
}
/*******************************/
Drone** Forest::getDrones() {
	return drones;
}
/*******************************/
int Forest::getNumDrones() {

	return numDrones;
}
/*******************************/
void Forest::moveDrone(int ID) { //physical equation mentioned within instructionsS

	// save personal best an location at time t for calculating velocity at time t+1
	Point prevLoc = drones[ID - 1]->getLocation();
	Point prevRec = drones[ID - 1]->getRecord();

	/**** decrease number of drones in previous field sheet ****/
	if(prevLoc.getX() == MAX_X && prevLoc.getY() != MAX_Y )
		(*(field[(int) floor(prevLoc.getY())][(int) floor(prevLoc.getX())-1]))--;
	else if( prevLoc.getX() != MAX_X && prevLoc.getY() == MAX_Y )
		(*(field[(int) floor(prevLoc.getY())-1][(int) floor(prevLoc.getX())]))--;
	else if( prevLoc.getX() == MAX_X && prevLoc.getY() == MAX_Y )
		(*(field[(int) floor(prevLoc.getY())-1][(int) floor(prevLoc.getX())-1]))--;
	else
		(*(field[(int) floor(prevLoc.getY())][(int) floor(prevLoc.getX())]))--;

	/**** move drone to new location ****/
	drones[ID - 1]->setLocation(prevLoc + drones[ID - 1]->getVelocity());

	/**** update personal best ****/
	drones[ID - 1]->setRecord(drones[ID - 1]->getLocation(), *targetP);

	/**** increase number of drones in new field sheet ****/
	if( floor(drones[ID - 1]->getLocation().getY()) != MAX_Y && floor(drones[ID - 1]->getLocation().getX()) == MAX_X )
		(*(field[(int) floor(drones[ID - 1]->getLocation().getY())][(int) floor(drones[ID - 1]->getLocation().getX())-1]))++;
	else if( floor(drones[ID - 1]->getLocation().getY()) == MAX_Y && floor(drones[ID - 1]->getLocation().getX()) != MAX_X )
		(*(field[(int) floor(drones[ID - 1]->getLocation().getY())-1][(int) floor(drones[ID - 1]->getLocation().getX())]))++;
	else if( floor(drones[ID - 1]->getLocation().getY()) == MAX_Y && floor(drones[ID - 1]->getLocation().getX()) == MAX_X )
		(*(field[(int) floor(drones[ID - 1]->getLocation().getY())-1][(int) floor(drones[ID - 1]->getLocation().getX())-1]))++;
	else
		(*(field[(int) floor(drones[ID - 1]->getLocation().getY())][(int) floor(drones[ID - 1]->getLocation().getX())]))++;

	/**** update new velocity by formula ****/
	Point newVel = drones[ID - 1]->getVelocity() * 0.25;
	newVel += (prevRec - prevLoc) * r1;
	newVel += (globalBest - prevLoc) * r2;

	drones[ID - 1]->setVelocity(newVel);
}
/*******************************/
void Forest::randomize() { //randomizes r1 and r2 between 0-1
	r1 = (double) rand() / RAND_MAX;
	r2 = (double) rand() / RAND_MAX;
}
/*******************************/
double Forest::distanceFromTarget(Point &p) { //Calculates the distance of a given drone from target Point (contained in target fieldsheet).

	// Distance calculation by formula
	return sqrt(
			pow(p.getX() - targetP->getX(), 2)
					+ pow(p.getY() - targetP->getY(), 2));
}
/*******************************/
string Forest::toString() { //prints out forest at current simulation time (number of drones per field sheet and target as X)

	string dronesInside;
	string drones_display = "";

	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			dronesInside = "";
			if (field[i][j] == targetFS) {
				drones_display += 'X';
				drones_display += '\t';
				continue;
			}
			if (field[i][j]->numberOfDrones > 0)
				dronesInside = field[i][j]->numberOfDrones + '0';
			else
				dronesInside = " ";
			drones_display += dronesInside;
			drones_display += '\t';
		}
		drones_display += '\n';
	}

	return drones_display;

}
/*******************************/
