#ifndef SIMULATION_H_
#define SIMULATION_H_
#include "Forest.h"

class Simulation	{

public:
	Simulation(const string& file1,const string& ,const string& file3);
	~Simulation();
	Simulation(Simulation *other);
	Simulation *operator=(const Simulation *other);
	Drone **parseData(int& numDrones,Point *targetP, long int& iterations,const string& config,const string& init ); // input parser
	bool validSimulation(const string& file1,const string& file2); // input validator
	void runSimulation(const string& final_dat);

private:
	Forest *forest;
	long int iterations;
};

#endif
