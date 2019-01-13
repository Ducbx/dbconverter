#include "stdafx.h"
#include "AccessReader.h"


AccessReader::AccessReader()
{
}


AccessReader::~AccessReader()
{
}

//Get all table and form of table
bool AccessReader::readStructure(DatabaseStruct &)
{
	return false;
}


//Get record information 
bool AccessReader::readData(Table)
{
	return false;
}