#include "stdafx.h"
#include "SQLiteReader.h"


SQLiteReader::SQLiteReader()
{
}


SQLiteReader::~SQLiteReader()
{
}

bool SQLiteReader::readStructure(DatabaseStruct &)
{
	return false;
}

bool SQLiteReader::readData(Table)
{
	return false;
}