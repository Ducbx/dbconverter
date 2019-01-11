#pragma once
#include "BaseDbReader.h"

class SQLiteReader : public BaseDbReader 
{
public:
	SQLiteReader();
	~SQLiteReader();

	virtual bool readStructure(DatabaseStruct &);
	virtual bool readData(Table);
};

