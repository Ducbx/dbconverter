#ifndef Base_Db_Reader_h
#define Base_Db_Reader_h
#include "DatabaseStruct.h"

class  BaseDbReader
{
public:
	virtual ~BaseDbReader(){}
	virtual bool readStructure(DatabaseStruct*) = 0;
	virtual bool readData(Table) = 0;
};


#endif