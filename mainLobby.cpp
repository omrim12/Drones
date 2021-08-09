#include <iostream>
#include "Simulation.h"

using namespace std;

int main(int argc, char **argv) {


	if( argc != 4 )		{
		cerr << "Error; invalid input" << endl;
		exit(-1);

	}

	srand(time(NULL));

	Simulation *test = new Simulation(argv[1],argv[2],argv[3]);
	test->runSimulation(argv[3]);

	return 0;
}
