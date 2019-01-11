#ifndef Base_Db_Writer_h
#define Base_Db_Writer_h
#include "DatabaseStruct.h"

class  BaseDbWriter
{
public:
	virtual bool writeStructure(DatabaseStruct &) = 0;
	virtual bool writeData(Table) = 0;
};


#endif