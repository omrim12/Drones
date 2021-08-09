#ifndef FIELDSHEET_H_
#define FIELDSHEET_H_

#include "Point.h"

class FieldSheet	{

public:
	/*Constructor*/
	FieldSheet(int row,int column);

	/*BIG THREE*/
	~FieldSheet();
	FieldSheet(FieldSheet *other);
	FieldSheet *operator=(FieldSheet *other);

	/*Methods*/
	bool operator==(FieldSheet *other);
	FieldSheet* operator++(); //increase number of drones (prefix)
	FieldSheet operator++(int); //increase number of drones (postfix)
	FieldSheet* operator--();//decrease number of drones (prefix)
	FieldSheet operator--(int);//decrease number of drones (postfix)
	friend class Forest;
	int getRow();
	int getColumn();

private:
	int row;
	int column;
	int numberOfDrones;




};

#endif
