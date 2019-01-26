#ifndef Base_Db_Writer_h
#define Base_Db_Writer_h
#include "DatabaseStruct.h"
#include "OutputStatement.h"

class  BaseDbWriter
{
public:
	virtual bool writeStructure(DatabaseStruct* &databaseStruct, OutputStatement* &outputStatement) = 0;
	virtual bool writeData(Table) = 0;
};


#endif