#include "FieldSheet.h"
/*******************************/
FieldSheet::FieldSheet(int row,int column):
row(row),
column(column),
numberOfDrones(0){}
/*******************************/
FieldSheet::~FieldSheet()	{}
/*******************************/
FieldSheet::FieldSheet(FieldSheet *other):
row(other->row),
column(other->column),
numberOfDrones(other->numberOfDrones) {}
/*******************************/
FieldSheet* FieldSheet::operator=(FieldSheet *other)	{

	row = other->row;
	column = other->column;
	numberOfDrones = other->numberOfDrones;

	return this;

}
/*******************************/
bool FieldSheet::operator==(FieldSheet *other)	{
	if( row == other->row && column == other->column )
		return true;
	return false;
}
/*******************************/
FieldSheet* FieldSheet::operator++()	{//increase number of drones (prefix)

	numberOfDrones++;
	return this;
}
/*******************************/
FieldSheet FieldSheet::operator++(int)	{//increase number of drones (postfix)

	FieldSheet temp = *this;
	numberOfDrones++;

	return temp;
}
/*******************************/
FieldSheet* FieldSheet::operator--()	{//decrease number of drones (prefix)

	numberOfDrones--;
	return this;
}
/*******************************/
FieldSheet FieldSheet::operator--(int)	{//decrease number of drones (postfix)

	FieldSheet temp = *this;
	numberOfDrones--;

	return temp;
}
/*******************************/
int FieldSheet::getRow()	{

	return row;
}
/*******************************/
int FieldSheet::getColumn()	{
	return column;
}

