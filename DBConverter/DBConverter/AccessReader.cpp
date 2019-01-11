#include "stdafx.h"
#include "AccessReader.h"


AccessReader::AccessReader()
{
}


AccessReader::~AccessReader()
{
}


bool AccessReader::readStructure(DatabaseStruct &)
{
	return false;
}

bool AccessReader::readData(Table)
{
	return false;
}