#pragma once
#include "BaseDbReader.h"

class SQLiteReader : public BaseDbReader 
{
public:
	SQLiteReader();
	~SQLiteReader();

	virtual bool readStructure(const char* path, DatabaseStruct&);
	virtual bool readData(Table);
};

