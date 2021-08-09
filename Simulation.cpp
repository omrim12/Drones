#include "Simulation.h"
/**************************************/

/**************************************/
Simulation::Simulation(const string& file1,const string& file2,const string& file3)		{

	if( !validSimulation(file1,file2) )	{
		cerr << "Error; invalid input" << endl;
		exit(-1);
	}

	int numDrones;
	Point *targetPoint = new Point();
	long int iterations;

	Drone **drones = parseData(numDrones, targetPoint, iterations, file1, file2 );

	this->iterations = iterations;
	forest = new Forest(drones,numDrones,targetPoint,iterations);
}
/**************************************/
Simulation::~Simulation()	{
	delete forest;
}
/**************************************/
Simulation::Simulation(Simulation *other)	{

	forest = other->forest;
	iterations = other->iterations;
}
/**************************************/
void Simulation::runSimulation(const string& final_dat)	{

	string *simulation_results = forest->start();

	// Simulation ended. output stats to final.dat
	ofstream results(final_dat.c_str());

	for(int i = 0; i < forest->getNumDrones()+1; i++)	{
		results << simulation_results[i] << endl;
	}

	results.close();
	delete this; //END OF PROGRAM
}
/**************************************/
bool Simulation::validSimulation(const string& file1,const string& file2)	{ // tests data files by requirements.

	ifstream config_dat(file1.c_str());
	ifstream init_dat(file2.c_str());

	if(!config_dat || !init_dat )
		return false;


	string buffer;
	stringstream ss;
	double testD1;
	double testD2;
	long int testI;
	char testC;


	/************* TESTING DATA FROM CONFIG.DAT *****************/
	// Test target coordinates validation
	getline(config_dat,buffer);
	ss.str(buffer);

	ss >> testD1;
	if( ss.fail() )	{ //x coordinate of target input
		config_dat.close();
		init_dat.close();
		return false;
	}

	ss >> testD2;
	if( ss.fail() )	{ //y coordinate of target input
		config_dat.close();
		init_dat.close();
		return false;
	}

	if( ss.fail() || testD1 > MAX_X || testD1 < 0 || testD2 > MAX_Y || testD2 < 0 )	{ //if one of invalid input conditions occured
		config_dat.close();
		init_dat.close();
		return false;
	}

	ss >> testC;

	if( !ss.fail() )	{// if theres still tokens to read (invalid)
		config_dat.close();
		init_dat.close();
		return false;
	}

	// Test number of iterations validation
	getline(config_dat,buffer);
	ss.clear();
	ss.str(buffer);

	ss >> testD1;

	if( ss.fail() || testD1 < 0 || testD1 > MAX_ITERATIONS || testD1 - floor(testD1) > 0 )	{ //if one of invalid input conditions occured
		config_dat.close();
		init_dat.close();
		return false;
	}

	ss >> testC; // if theres still tokens to read (invalid)


	if( !ss.fail() )	{
		config_dat.close();
		init_dat.close();
		return false;
	}

	config_dat.close();

	/************* TESTING DATA FROM INIT.DAT *****************/
	// Test drone numbers validation
	getline(init_dat,buffer);
	ss.clear();
	ss.str(buffer);

	ss >> testI;

	if( ss.fail() || testI <= MIN_DRONES || testI - floor(testI) > 0 )	{
		init_dat.close();
		return false;
	}

	ss >> testC; // try reading another element

	if( !ss.fail() )	{// if theres still tokens to read (invalid)
		init_dat.close();
		return false;
	}

	// Test drone data validation
	while( getline(init_dat,buffer) )	{

		ss.clear();
		ss.str(buffer);

		for(int i = 1; i < 6; i++)	{

			if( i == 5 )	{ //if theres still tokens to read (invalid)
				ss >> testC;
				if( !ss.fail() )	{
					init_dat.close();
					return false;
				}
				break;
			}

			if( i == 1 )	{ //about to recieve x coordinate of drone i
				ss >> testD1;
				if( ss.fail() || testD1 < 0 || testD1 > MAX_X )	{
					init_dat.close();
					return false;
				}
			}

			else if( i == 2 )	{ //about to recieve y coordinate of drone i
				ss >> testD1;
				if( ss.fail() || testD1 < 0 || testD1 > MAX_Y )	{
					init_dat.close();
					return false;
				}
			}

			else	{ //about to recieve velocity component
				ss >> testD1;
				if( ss.fail() )	{
					init_dat.close();
					return false;
				}
			}
		}

		testI--;
	}

	if( testI != 0 )	{ // Encountered a problem during file drones data scanning
		init_dat.close();
		return false;
	}
	/************************************************************/

	init_dat.close();
	return true; // Passed all tests successfully. ready for parsing data
}
/**************************************/
Drone **Simulation::parseData(int& numDrones,Point *targetP, long int& iterations, const string& config,const string& init )	{

	ifstream config_dat(config.c_str());
	ifstream init_dat(init.c_str());

	string buffer;
	stringstream ss;
	float x;
	float y;
	float v_X;
	float v_Y;
	int i;

	// READING DATA FROM CONFIG.DAT
	getline(config_dat,buffer);

	ss.str(buffer);
	ss >> x;
	ss >> y;

	targetP->setX(x);
	targetP->setY(y);

	getline(config_dat,buffer);

	ss.clear();
	ss.str(buffer);
	ss >> iterations;

	config_dat.close();

	// READING DATA FROM INIT.DAT
	getline(init_dat,buffer);

	ss.clear();
	ss.str(buffer);
	ss >> numDrones;

	Drone **drones = new Drone*[numDrones];
	i = 0;
	Point& p = *new Point();
	Point& v = *new Point();

	while(i < numDrones)	{
		ss.clear();
		getline(init_dat,buffer);
		ss.str(buffer);
		ss >> x;
		ss >> y;
		ss >> v_X;
		ss >> v_Y;
		p.setX(x);
		p.setY(y);
		v.setX(v_X);
		v.setY(v_Y);
		drones[i] = new Drone(p,v,i+1); // @suppress("Ambiguous problem")
		i++;
	}

	return drones;

}
/**************************************/
